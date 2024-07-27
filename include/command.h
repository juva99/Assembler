#ifndef OPENU_PROJECT_COMMAND_H
#define OPENU_PROJECT_COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cmd_struct {
    char *label;
    int opcode;
    char *src;
    char *dst;
} cmd_struct;


cmd_struct *build_command(char *line);

int check_command_args(cmd_struct *cmd);

int dup_argument(char **dest, char *str);

#endif //OPENU_PROJECT_COMMAND_H
