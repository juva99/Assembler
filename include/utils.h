#ifndef OPENU_PROJECT_UTILS_H
#define OPENU_PROJECT_UTILS_H

#include <string.h>
#include <ctype.h>
#include "../include/consts.h"
#include "../include/code_container.h"

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

int encode_data(char *line, int data_type, code_cont **data, int *dc);

unsigned short dec_to_bin(int decimalNum);


#endif //OPENU_PROJECT_UTILS_H

