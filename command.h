// command 타입, command table, handler 선언
#ifndef COMMAND_H
#define COMMAND_H

#include "student.h"

typedef enum {
    SHELL_OK = 0,
    SHELL_EXIT,
    SHELL_ERR_COMMAND_FAILED,
    SHELL_ERR_UNKNOWN_COMMAND,
    SHELL_ERR_INVALID_ARGUMENT,
    SHELL_ERR_MISSING_ARGUMENT,
    SHELL_ERR_FILE,
    SHELL_ERR_STUDENT_NOT_FOUND,
    SHELL_ERR_DUPLICATE_STUDENT
} ShellResult;

typedef struct ShellContext {
    Student* head;
    const char* csv_path;
} ShellContext;

typedef ShellResult (*CommandHandler)(char* args, ShellContext* ctx);

typedef struct {
    const char* name;
    CommandHandler handler;
    const char* usage;
    const char* description;
} Command;

ShellResult execute_command(char* line, ShellContext* ctx);
void print_prompt(void);

#endif
