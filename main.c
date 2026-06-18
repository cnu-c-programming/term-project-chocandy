/*
 * main.c  –  Mini Student Shell
 *
 * TODO: Implement admin_shell and client_shell.
 *
 * Build:
 *   make admin   →  admin_shell  (compiled with -DADMIN_MODE)
 *   make client  →  client_shell (compiled with -DCLIENT_MODE)
 *
 * Usage:
 *   ./admin_shell [students.csv]
 *   ./admin_shell -f commands.txt [students.csv]
 *   ./client_shell [students.csv]
 *   ./client_shell -f commands.txt [students.csv]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TODO: Add your own header includes here */
/* #include "student.h"  */
/* #include "file_io.h"  */
/* #include "command.h"  */
#include "student.h"
#include "file_io.h"
#include "command.h"

void run_shell(const char *csv_path) {
    ShellContext ctx;
    ctx.head = NULL;
    ctx.csv_path = csv_path;

    load_students_from_csv(csv_path, &ctx.head);

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

/* ---------------------------------------------------------------
 * TODO: Implement batch mode – read commands from a file.
 *   - Open cmd_file for reading.
 *   - Execute each line as a command (same logic as run_shell).
 *   - Close the file when done.
 * --------------------------------------------------------------- */
void run_command_file(const char *cmd_file, const char *csv_path) {
    FILE *fp = fopen(cmd_file, "r");
    if (fp == NULL) {
        printf("Error: cannot open command file.\n");
        return;
    }

    ShellContext ctx;
    ctx.head = NULL;
    ctx.csv_path = csv_path;

    load_students_from_csv(csv_path, &ctx.head);

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
    const char *csv_path  = "students.csv"; /* default CSV file */
    const char *cmd_file  = NULL;           /* -f <file> argument */

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
