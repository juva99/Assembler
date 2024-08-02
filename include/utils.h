#ifndef OPENU_PROJECT_UTILS_H
#define OPENU_PROJECT_UTILS_H

#include "../include/consts.h"

typedef enum {
    NOT_DATA,
    DATA,
    STRING
} DataType;


typedef struct opcode {
    char *name; /* name of opcode */
    int args; /* amount of args of opcode */
    int add_methods_src[MAX_ADDRESS_METHODS]; /* valid address methods for src */
    int add_methods_dst[MAX_ADDRESS_METHODS]; /* valid address methods for dst */
} opcode;


#include "../include/code_container.h"

#include <string.h>
#include <ctype.h>


int extract_next(char *src, char *next, char delimiter);

int starts_with(const char *str, const char *pre);

int what_instrct(char *token);

int what_opcode(char *token);

int what_regs(char *token);

DataType data_instruction(char *line);

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

int get_src_add_method(int opcode, char *src);

int get_dst_add_method(int opcode, char *dst);

int encode_string(char *line, code_cont **data, int *dc);

int encode_data(char *line, DataType data_type, code_cont **data, int *dc);

int encode_numeric_data(char *line, code_cont **data, int *dc);

unsigned short conv_to_ushort(int dec_num);

char *strduplic(const char *s);


#endif //OPENU_PROJECT_UTILS_H

