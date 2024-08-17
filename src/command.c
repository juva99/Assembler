#include "../include/command.h"

#include "../include/file_manager.h"

#include "../include/utils.h"

opcode opcodes[] = {
    {"mov", 2, {0, 1, 2, 3}, {1, 2, 3, -1}},
    {"cmp", 2, {0, 1, 2, 3}, {0, 1, 2, 3}},
    {"add", 2, {0, 1, 2, 3}, {1, 2, 3, -1}},
    {"sub", 2, {0, 1, 2, 3}, {1, 2, 3, -1}},
    {"lea", 2, {1, -1, -1, -1}, {1, 2, 3, -1}},
    {"clr", 1, {-1, -1, -1, -1}, {1, 2, 3, -1}},
    {"not", 1, {-1, -1, -1, -1}, {1, 2, 3, -1}},
    {"inc", 1, {-1, -1, -1, -1}, {1, 2, 3, -1}},
    {"dec", 1, {-1, -1, -1, -1}, {1, 2, 3, -1}},
    {"jmp", 1, {-1, -1, -1, -1}, {1, 2, -1, -1}},
    {"bne", 1, {-1, -1, -1, -1}, {1, 2, -1, -1}},
    {"red", 1, {-1, -1, -1, -1}, {1, 2, 3, -1}},
    {"prn", 1, {-1, -1, -1, -1}, {0, 1, 2, 3}},
    {"jsr", 1, {-1, -1, -1, -1}, {1, 2, -1, -1}},
    {"rts", 0, {-1, -1, -1, -1}, {-1, -1, -1, -1}},
    {"stop", 0, {-1, -1, -1, -1}, {-1, -1, -1, -1}},
};

int (*check_address_functions[])(char *str) = {
    check_address_type_0,
    check_address_type_1,
    check_address_type_2,
    check_address_type_3,
};

void free_command(cmd_struct *cmd) {
    if (cmd->src != NULL)
        free(cmd->src);
    if (cmd->dst != NULL)
        free(cmd->dst);
    free(cmd);
}

int build_command(char *line, cmd_struct **command) {
    int args, num;
    char arg[MAX_LABEL_LENGTH + 1];
    cmd_struct *cmd = malloc(sizeof(cmd_struct));

    if (cmd == NULL) {
        handle_dynamic_alloc_error();
    }
    /* init command */
    cmd->opcode = -1;
    cmd->src = NULL;
    cmd->dst = NULL;
    cmd->src_method = -1;
    cmd->dst_method = -1;
    cmd->length = 0;

    /* get command opcode */
    cmd->opcode = extract_opcode(line);

    if (cmd->opcode < 0) {
        /* error - invalid opcode */
        free_command(cmd);
        return ERROR_ID_21;
    }

    /* parse arguments */
    args = get_opcode_args(cmd->opcode);
    switch (args) {
        case 0: {
            if (strcmp(line, "") != 0) {
                /* error -  command extra text */
                free_command(cmd);
                return ERROR_ID_22;
            }
            cmd->length = 1;
            *command = cmd;
            break;
        }
        case 1: {
            extract_next(line, arg, ' ');
            if (strcmp(line, "") != 0) {
                /* error - command extra text */
                free_command(cmd);
                return ERROR_ID_22;
            }

            dup_argument(&(cmd->dst), arg);
            cmd->length = 2;
            cmd->dst_method = get_dst_add_method(cmd->opcode, cmd->dst);
            if (cmd->dst_method < 0) {
                /* error - dst not valid */
                free_command(cmd);
                return ERROR_ID_23;
            }
            *command = cmd;
            break;
        }
        case 2: {
            extract_next(line, arg, ',');
            dup_argument(&(cmd->src), arg);
            extract_next(line, arg, ' ');
            if (strcmp(line, "") != 0) {
                /* error  - command extra text */
                free_command(cmd);
                return ERROR_ID_22;
            }

            dup_argument(&(cmd->dst), arg);

            cmd->src_method = get_src_add_method(cmd->opcode, cmd->src);
            cmd->dst_method = get_dst_add_method(cmd->opcode, cmd->dst);
            if (cmd->src_method < 0 || cmd->dst_method < 0) {
                /* error - src or dst method not legal */
                free_command(cmd);
                return ERROR_ID_24;
            }
            cmd->length = 3;
            /* check if both of the methods are registers to calc command length */
            if ((cmd->src_method == 3 || cmd->src_method == 2) &&
                (cmd->dst_method == 3 || cmd->dst_method == 2)) {
                cmd->length = 2;
            }
            *command = cmd;
            break;
        }
        default: {
            /* error - invalid args count */
            free_command(cmd);
            return ERROR_ID_25;
        }
    }
    if (cmd->dst_method == 0) {
        num = read_num_arg(cmd->dst);
        if (num < MIN_COMMAND_NUM_VALUE || num > MAX_COMMAND_NUM_VALUE) {
            free_command(cmd);
            return ERROR_ID_31;
        }
    }
    if (cmd->src_method == 0) {
        num = read_num_arg(cmd->src);
        if (num < MIN_COMMAND_NUM_VALUE || num > MAX_COMMAND_NUM_VALUE) {
            free_command(cmd);
            return ERROR_ID_31;
        }
    }
    return ERROR_ID_0;
}

void dup_argument(char **dest, char *str) {
    *(dest) = malloc(strlen(str) + 1);
    if (*(dest) == NULL) {
        handle_dynamic_alloc_error();
    }
    strcpy(*(dest), str);
}

int what_opcode(char *token) {
    int i;

    if (token == NULL)
        return -1;

    for (i = 0; i < OPCODES_COUNT; i++) {
        if (strcmp(token, opcodes[i].name) == 0)
            return i; /* returns the index in instructions array */
    }
    return -1; /* returns -1 if token isn't instruction */
}

int get_opcode_args(int opcode) {
    if (opcode < 0 || opcode >= OPCODES_COUNT)
        return -1;
    return opcodes[opcode].args;
}

/* check if string is valid type 0 address */
int check_address_type_0(char *str) {
    /* Check if the first character is '#' */
    if (*str != '#') {
        return 0;
    }
    /* Move to the next character */
    str++;
    /* Check if the next character is a '-' (optional) */
    if (*str == '-') {
        str++;
    }
    /* Check if the next character(s) form a whole decimal number */
    if (!isdigit(*str)) {
        return 0;
    }
    while (*str != '\0') {
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    /* If we reached here, the string starts with '#' followed by a whole decimal number (possibly negative) */
    return 1;
}

/* check if string is valid type 1 address */
int check_address_type_1(char *str) {
    return check_symbol_name(str);
}

/* check if string is valid type 2 address */
int check_address_type_2(char *str) {
    /* Check if the first character is '#' */
    if (*str != '*') {
        return 0;
    }
    return check_address_type_3(++str);
}

/* check if string is valid type 3 address */
int check_address_type_3(char *str) {
    return what_regs(str) >= 0;
}

/* get source address method */
int get_src_add_method(int opcode, char *src) {
    int i;
    /* Check source address */
    for (i = 0; i < MAX_ADDRESS_METHODS; i++) {
        if (opcodes[opcode].add_methods_src[i] != -1 &&
            check_address_functions[opcodes[opcode].add_methods_src[i]](src)) {
            return opcodes[opcode].add_methods_src[i];
        }
    }
    return -1;
}

/* get dest address method */
int get_dst_add_method(int opcode, char *dst) {
    int i;
    /* Check dest address */
    for (i = 0; i < MAX_ADDRESS_METHODS; i++) {
        if (opcodes[opcode].add_methods_dst[i] != -1 &&
            check_address_functions[opcodes[opcode].add_methods_dst[i]](dst)) {
            return opcodes[opcode].add_methods_dst[i];
        }
    }
    return -1;
}
