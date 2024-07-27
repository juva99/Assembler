#ifndef OPENU_PROJECT_UTILS_H
#define OPENU_PROJECT_UTILS_H

#include <string.h>
#include <ctype.h>
#include "../include/consts.h"

typedef struct opcode {
    char *name; /* name of opcode */
    int args; /* amount of args of opcode */
    int add_methods_src[MAX_ADDRESS_METHODS]; /* valid address methods for src */
    int add_methods_dst[MAX_ADDRESS_METHODS]; /* valid address methods for dst */
} opcode;

int extract_next(char *src, char *next, char delimiter);

int starts_with(const char *str, const char *pre);

int what_instrct(char *token);

int what_opcode(char *token);

int what_regs(char *token);

int data_instruction(char *line);

int is_extern(char *line);

int is_entry(char *line);

int extract_symbol(char *line, char *sym_name, char delimeter);

int extract_opcode(char *line, char *opcode_name);

#endif //OPENU_PROJECT_UTILS_H

