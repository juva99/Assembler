#ifndef OPENU_PROJECT_COMMAND_H
#define OPENU_PROJECT_COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/consts.h"

typedef struct cmd_struct {
    char *label; /* label of command */
    int opcode; /* opcode number of command */
    char *src; /* source address of command */
    char *dst; /* dest address of command */
    int src_method; /* src address method id */
    int dst_method; /* dst address method id */
    int length; /* command line length */
} cmd_struct;

typedef struct opcode {
    char *name; /* name of opcode */
    int args; /* amount of args of opcode */
    int add_methods_src[MAX_ADDRESS_METHODS]; /* valid address methods for src */
    int add_methods_dst[MAX_ADDRESS_METHODS]; /* valid address methods for dst */
} opcode;

void free_command(cmd_struct *cmd);

cmd_struct *build_command(char *line);

int check_command_args(cmd_struct *cmd);

int dup_argument(char **dest, char *str);

int what_opcode(char *token);

int get_opcode_args(int opcode);

int check_address_type_0(char *str);

int check_address_type_1(char *str);

int check_address_type_2(char *str);

int check_address_type_3(char *str);

int get_src_add_method(int opcode, char *src);

int get_dst_add_method(int opcode, char *dst);


#endif
