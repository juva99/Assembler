#ifndef OPENU_PROJECT_UTILS_H
#define OPENU_PROJECT_UTILS_H

#include <string.h>
#include <ctype.h>
#include "../include/consts.h"

int extract_next(char *src, char *next, char delimiter);

int starts_with(const char *str, const char *pre);

int what_instrct(char *token);

int what_opcode(char *token);

int what_regs(char *token);

int is_symbol(char *line, char **sym_name);

int data_instruction(char *line);

#endif //OPENU_PROJECT_UTILS_H

