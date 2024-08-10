#ifndef CODE_CONTAINER_H
#define CODE_CONTAINER_H


/* offsets for command structure */
#define OPCODE_OFFSET 11
#define SRC_OFFSET 7
#define DST_OFFSET 3

/* offsets for SRC and DST lines*/
#define DATA_OFFSET 3
#define REG_DST_OFFSET 3
#define REG_SRC_OFFSET 6


/* A.R.E enum offsets */
typedef enum {
    EXTERNAL = 0,
    RELOCATABLE = 1,
    ABSOLUTE = 2
} ARE;

typedef struct code_cont {
    unsigned short bin_rep;
    int code_line;
    char *label; /* not in use for data*/
} code_cont;

#include "../include/utils.h"
#include "../include/command.h"
#include "../include/symbol_table.h"

int write_data(code_cont **container, unsigned short data, int *counter);

int write_data_label(code_cont **container, unsigned short data, int *counter, char *label);

int add_data(code_cont **data, unsigned short val, int *dc);

int expend_memory(code_cont **container, int counter);

int add_command(code_cont **code, cmd_struct *cmd, int *ic);

unsigned short create_method_line(cmd_struct *cmd, int method, char *value, int is_src);

code_cont *create_container();

int update_line(code_cont *code, Symbol *symbol);

int save_object_file(char *filename, code_cont *code, code_cont *data, int ic, int dc);

unsigned int to_octal(unsigned short number);

void free_container(code_cont *container, int size);

#endif
