#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "file_io.h"
#include "command.h"

void run_shell(const char *csv_path) {
    ShellContext ctx;
    ctx.head = NULL;
    ctx.csv_path = csv_path;

    int load_result = load_students_from_csv(csv_path, &ctx.head);
    if (load_result == -2) {
        printf("Error: invalid header.\n");
    } else if (load_result != 0) {
        printf("Error: invalid CSV.\n");
    }
    #ifdef ADMIN_MODE
        printf("[Admin Program]\n");
    #else
        printf("[Client Program]\n");
    #endif

        printf("Loaded %d students from %s.\n\n",
            load_result >= 0 ? load_result : 0,
            csv_path);

    char line[256];
    while (1) {
        print_prompt();
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
        ShellResult result = execute_command(line, &ctx);
        if (result == SHELL_EXIT) {
            break;
        }
    }
    free_students(ctx.head);
}

void run_command_file(const char *cmd_file, const char *csv_path) {
    FILE *fp = fopen(cmd_file, "r");
    if (fp == NULL) {
        printf("Error: cannot open command file.\n");
        return;
    }

    ShellContext ctx;
    ctx.head = NULL;
    ctx.csv_path = csv_path;

    int load_result = load_students_from_csv(csv_path, &ctx.head);
    if (load_result == -2) {
        printf("Error: invalid header.\n");
    } else if (load_result != 0) {
        printf("Error: invalid CSV.\n");
    }
    #ifdef ADMIN_MODE
        printf("[Admin Program]\n");
    #else
        printf("[Client Program]\n");
    #endif

    printf("Loaded %d students from %s.\n\n",
        load_result >= 0 ? load_result : 0,
        csv_path);

    char line[256];
    int line_no = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        line_no++;
        line[strcspn(line, "\n")] = '\0';
        /* 빈 줄 무시 */
        if (line[0] == '\0') {
            continue;
        }
        /* # 주석 무시 */
        if (line[0] == '#') {
            continue;
        }
        printf("[%d] %s\n", line_no, line);
        ShellResult result = execute_command(line, &ctx);
        if (result == SHELL_EXIT) {
            break;
        }
    }
    fclose(fp);
    free_students(ctx.head);
}

int main(int argc, char *argv[]) {
    const char *csv_path  = NULL;
    const char *cmd_file  = NULL;

    if (argc < 2) {
        printf("Usage:\n");
        printf("./admin_shell <csv_file> [-f command_file]\n");
        printf("./client_shell <csv_file> [-f command_file]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            cmd_file = argv[++i];
        } else {
            csv_path = argv[i];
        }
    }

#ifdef ADMIN_MODE
    /* Admin shell: supports add, delete, update, save, load, sort, list, find, help, exit */
    if (cmd_file) {
        run_command_file(cmd_file, csv_path);
    } else {
        run_shell(csv_path);
    }

#elif defined(CLIENT_MODE)
    /* Client shell: supports find, list, help, exit  (read-only) */
    if (cmd_file) {
        run_command_file(cmd_file, csv_path);
    } else {
        run_shell(csv_path);
    }

#else
#error "Define either -DADMIN_MODE or -DCLIENT_MODE when compiling."
#endif

    return 0;
}
