#ifndef CODE_CONTAINER_H
#define CODE_CONTAINER_H

typedef struct code_cont {
    unsigned short bin_rep;
    int code_line;
    char *label; /* not in use for data*/
} code_cont;

#include "../include/utils.h"
#include "../include/command.h"

int write_data(code_cont **container, unsigned short data, int *counter);

int write_data_label(code_cont **container, unsigned short data, int *counter, char *label);

int add_data(code_cont **data, unsigned short val, int *dc);

int expend_memory(code_cont **container, int counter);

int add_command(code_cont **code, cmd_struct *cmd, int *ic);

unsigned short create_method_line(cmd_struct *cmd, int method, char *value, int is_src);

code_cont *create_container();

#endif //CODE_CONTAINER_H
