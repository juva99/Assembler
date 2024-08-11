#ifndef OPENU_PROJECT_UTILS_H
#define OPENU_PROJECT_UTILS_H

#include "../include/consts.h"
#include "../include/symbol_table.h"
#include "../include/code_container.h"
#include <string.h>
#include <ctype.h>

typedef enum {
    NOT_DATA,
    DATA,
    STRING
} DataType;

typedef enum {
    ENTRY,
    EXTERN
} ListType;


int extract_next(char *src, char *next, char delimiter);

int starts_with(const char *str, const char *pre);

int what_instrct(char *token);

int what_regs(char *token);

DataType data_instruction(char *line);

int is_extern(char *line);

int is_entry(char *line);

int extract_symbol(char *line, char *sym_name, char delimeter);

int check_symbol_name(char *first_token);

int extract_opcode(char *line);

int encode_string(char *line, code_cont **data, int *dc);

int encode_data(char *line, DataType data_type, code_cont **data, int *dc);

int encode_numeric_data(char *line, code_cont **data, int *dc);

unsigned short conv_to_ushort(int dec_num);

char *strduplic(const char *s);

char *add_file_extension(char *filename, char *extension);

#endif

