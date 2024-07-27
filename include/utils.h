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

int check_symbol_name(char *first_token);

int extract_opcode(char *line);

int get_opcode_args(int opcode);

int check_address_type_0(char *str);

int check_address_type_1(char *str);

int check_address_type_2(char *str);

int check_address_type_3(char *str);

int check_opcode_address(int opcode, char *src, char *dst);

#endif //OPENU_PROJECT_UTILS_H

