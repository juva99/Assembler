#ifndef OPENU_PROJECT_COMMAND_H
#define OPENU_PROJECT_COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cmd_struct {
    char *label; /* label of command */
    int opcode; /* opcode number of command */
    char *src; /* source address of command */
    char *dst; /* dest address of command */
    int src_method; /* src address method id */
    int dst_method; /* dst address method id */
    int length; /* command line length */
} cmd_struct;


cmd_struct *build_command(char *line);

int check_command_args(cmd_struct *cmd);

int dup_argument(char **dest, char *str);

#endif //OPENU_PROJECT_COMMAND_H
