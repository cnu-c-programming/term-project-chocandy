// 명령어 파싱과 handler 구현
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "student.h"
#include "file_io.h"

/* 공통 명령어 handler */
static ShellResult handle_list(char* args, ShellContext* ctx);
static ShellResult handle_find(char* args, ShellContext* ctx);
static ShellResult handle_stats(char* args, ShellContext* ctx);
static ShellResult handle_help(char* args, ShellContext* ctx);
static ShellResult handle_clear(char* args, ShellContext* ctx);
static ShellResult handle_exit(char* args, ShellContext* ctx);
static ShellResult handle_reload(char* args, ShellContext* ctx);
static ShellResult handle_sort(char* args, ShellContext* ctx);

/* Admin 전용 handler */
#ifdef ADMIN_MODE
static ShellResult handle_save(char* args, ShellContext* ctx);
static ShellResult handle_add(char* args, ShellContext* ctx);
static ShellResult handle_delete(char* args, ShellContext* ctx);
static ShellResult handle_update(char* args, ShellContext* ctx);
#endif

#ifdef ADMIN_MODE
static Command commands[] = {
    {"save", handle_save, "save", "Save students to CSV"},
    {"reload", handle_reload, "reload", "Reload students from CSV"},
    {"add", handle_add, "add <id> <name> <score>", "Add a student"},
    {"delete", handle_delete, "delete <id>", "Delete a student"},
    {"update", handle_update, "update <id> <score>", "Update student score"},
    {"find", handle_find, "find <id>", "Find student by ID"},
    {"list", handle_list, "list", "List all students"},
    {"stats", handle_stats, "stats", "Show statistics"},
    {"sort", handle_sort, "sort <name|score>", "Sort students"},
    {"help", handle_help, "help", "Show help"},
    {"clear", handle_clear, "clear", "Clear screen"},
    {"exit", handle_exit, "exit", "Exit shell"}
};
#endif

#ifdef CLIENT_MODE
static Command commands[] = {
    {"reload", handle_reload, "reload", "Reload students from CSV"},
    {"find", handle_find, "find <id>", "Find student by ID"},
    {"list", handle_list, "list", "List all students"},
    {"stats", handle_stats, "stats", "Show statistics"},
    {"sort", handle_sort, "sort <name|score>", "Sort students"},
    {"help", handle_help, "help", "Show help"},
    {"clear", handle_clear, "clear", "Clear screen"},
    {"exit", handle_exit, "exit", "Exit shell"}
};
#endif

static int command_count(void) {
    return sizeof(commands) / sizeof(commands[0]);
}

void print_prompt(void) {
#ifdef ADMIN_MODE
    printf("admin> ");
#else
    printf("client> ");
#endif
}


ShellResult execute_command(char* line, ShellContext* ctx) {
    line[strcspn(line, "\n")] = '\0';

    if (line[0] == '\0') {
        return SHELL_OK;
    }

    char* command_name = strtok(line, " \t");
    if (command_name == NULL) {
        return SHELL_OK;
    }

    char* args = strtok(NULL, "");
    for (int i = 0; i < command_count(); i++) {
        if (strcmp(command_name, commands[i].name) == 0) {
            return commands[i].handler(args, ctx);
        }
    }
    printf("Unknown command or permission denied.\n");
    return SHELL_ERR_COMMAND_FAILED;
}

/* ---------------- 공통 명령어 구현부 ---------------- */

static ShellResult handle_list(char* args, ShellContext* ctx) {
    (void)args;
    print_students(ctx->head);

    return SHELL_OK;
}

static ShellResult handle_find(char* args, ShellContext* ctx) {
    int id;
    if (args == NULL || sscanf(args, "%d", &id) != 1) {
        printf("Error: invalid id.\n");
        return SHELL_ERR_COMMAND_FAILED;
    }

    if (id <= 0) {
        printf("Error: invalid id.\n");
        return SHELL_ERR_COMMAND_FAILED;
    }

    Student* student = find_student(ctx->head, id);
    if (student == NULL) {
        printf("Error: student not found.\n");
        return SHELL_ERR_COMMAND_FAILED;
    }
    printf("ID: %d\n", student->id);
    printf("Name: %s\n", student->name);
    printf("Score: %d\n", student->score);

    return SHELL_OK;
}

static ShellResult handle_stats(char* args, ShellContext* ctx) {
    (void)args;
    print_stats(ctx->head);
    return SHELL_OK;
}

static ShellResult handle_help(char* args, ShellContext* ctx) {
    (void)args;
    (void)ctx;
    for (int i = 0; i < command_count(); i++) {
        printf("%s - %s\n", commands[i].usage, commands[i].description);
    }

    return SHELL_OK;
}

static ShellResult handle_clear(char* args, ShellContext* ctx) {
    (void)args;
    (void)ctx;
    printf("\033[2J\033[H");
    return SHELL_OK;
}

static ShellResult handle_exit(char* args, ShellContext* ctx) {
    (void)args;
    (void)ctx;

    printf("Goodbye.\n");
    return SHELL_EXIT;
}

static ShellResult handle_reload(char* args, ShellContext* ctx) {
    (void)args;
    int result = load_students_from_csv(ctx->csv_path, &ctx->head);

    if (result >= 0) {
        printf("Reloaded %d students from %s.\n",
            result,
            ctx->csv_path);
    }else if (result == -2) {
        printf("Error: invalid header.\n");
        return SHELL_ERR_COMMAND_FAILED;
    } else {
        printf("Error: invalid CSV.\n");
        return SHELL_ERR_COMMAND_FAILED;
    }
    return SHELL_OK;
}

static ShellResult handle_sort(char* args, ShellContext* ctx) {
    if (args == NULL) {
        printf("Error: missing argument.\n");
        return SHELL_ERR_COMMAND_FAILED;
    }

    if (strcmp(args, "name") != 0 && strcmp(args, "score") != 0) {
        printf("Error: invalid sort key.\n");
        return SHELL_ERR_COMMAND_FAILED;
    }

    if (sort_students(&ctx->head, args) != 0) {
        printf("Error: invalid sort key.\n");
        return SHELL_ERR_COMMAND_FAILED;
    } else {
        printf("Students sorted by %s.\n", args);
    }

    return SHELL_OK;
}

/* ---------------- Admin 전용 명령어 구현부 ---------------- */

#ifdef ADMIN_MODE

static ShellResult handle_save(char* args, ShellContext* ctx) {
    (void)args;

    if (save_students_to_csv(ctx->csv_path, ctx->head) == 0) {
        printf("Saved %d students to %s.\n",
            count_students(ctx->head),
            ctx->csv_path);
    } else {
        printf("Error: save failed.\n");
        return SHELL_ERR_COMMAND_FAILED;
    }

    return SHELL_OK;
}

static ShellResult handle_add(char* args, ShellContext* ctx) {
    int id, score;
    char name[100];

    if (args == NULL ||
        sscanf(args, "%d %99s %d", &id, name, &score) != 3) {
        printf("Error: missing argument.\n");
        return SHELL_ERR_COMMAND_FAILED;
    }

    if (id <= 0) {
        printf("Error: invalid id.\n");
        return SHELL_ERR_COMMAND_FAILED;
    }

    if (score < 0 || score > 100) {
        printf("Error: invalid score.\n");
        return SHELL_ERR_COMMAND_FAILED;
    }

    int result = add_student(&ctx->head, id, name, score);

    if (result == -1) {
        printf("Error: duplicate id.\n");
        return SHELL_ERR_COMMAND_FAILED;
    } else if (result == -2) {
        printf("Error: memory allocation failed.\n");
        return SHELL_ERR_COMMAND_FAILED;
    } else {
        printf("Student added.\n");
    }

    return SHELL_OK;
}

static ShellResult handle_delete(char* args, ShellContext* ctx) {
    int id;

    if (args == NULL || sscanf(args, "%d", &id) != 1) {
        printf("Error: missing argument.\n");
        return SHELL_ERR_COMMAND_FAILED;
    }

    if (id <= 0) {
        printf("Error: invalid id.\n");
        return SHELL_ERR_COMMAND_FAILED;
    }

    if (delete_student(&ctx->head, id) != 0) {
        printf("Error: student not found.\n");
        return SHELL_ERR_COMMAND_FAILED;
    } else {
        printf("Student deleted.\n");
    }

    return SHELL_OK;
}

static ShellResult handle_update(char* args, ShellContext* ctx) {
    int id, score;

    if (args == NULL ||
        sscanf(args, "%d %d", &id, &score) != 2) {
        printf("Error: missing argument.\n");
        return SHELL_ERR_COMMAND_FAILED;
    }

    if (id <= 0) {
        printf("Error: invalid id.\n");
        return SHELL_ERR_COMMAND_FAILED;
    }

    if (score < 0 || score > 100) {
        printf("Error: invalid score.\n");
        return SHELL_ERR_COMMAND_FAILED;
    }

    if (update_student(ctx->head, id, score) != 0) {
        printf("Error: student not found.\n");
        return SHELL_ERR_COMMAND_FAILED;
    } else {
        printf("Student updated.\n");
    }

    return SHELL_OK;
}

#endif
