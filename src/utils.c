#include "../include/utils.h"

#include <stdio.h>
#include <stdlib.h>


char *instructions[] = {".data", ".string", "entry", "extern"};
char *registers[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};


int starts_with(const char *str, const char *pre) {
    return strncmp(pre, str, strlen(pre)) == 0;
}

int is_valid_string(const char *str) {
    while (*str) {
        if (!isalpha(*str) && !isdigit(*str)) {
            return 0; // False, the string contains invalid characters
        }
        str++;
    }
    return 1; // True, the string is valid
}

int extract_next(char *src, char *next, char delimiter) {
    char *ptr = src;
    char *rest_start;
    int found = 0;

    /* Skip leading spaces */
    while (isspace((unsigned char) *ptr)) {
        ptr++;
    }

    /* Copy characters to next until reaching delimiter or null terminator is encountered */
    while (*ptr != delimiter && *ptr != '\0' && *ptr != '\n') {
        found++;
        *next = *ptr;
        next++;
        ptr++;
    }
    if (*ptr == delimiter) {
        if (found == 0)
            found = 1;
        ptr++;
    }
    /* Null-terminate the next string */
    *next = '\0';

    /* Skip spaces after the first word */
    while (isspace((unsigned char) *ptr)) {
        ptr++;
    }

    /* Save the start of the rest of the string */
    rest_start = ptr;

    /* Move the rest of the string to the beginning */
    ptr = src;
    while (*rest_start != '\0') {
        *ptr = *rest_start;
        ptr++;
        rest_start++;
    }
    /* Null-terminate the modified source string */
    *ptr = '\0';
    return (found > 0);
}

int what_instrct(char *token) {
    int i;

    if (token == NULL)
        return -1;

    for (i = 0; i < INSTRUCTIONS_COUNT; i++) {
        if (strcmp(token, instructions[i]) == 0)
            return i; /* returns the index in instructions array */
    }

    return -1; /* returns -1 if token isn't instruction */
}


int what_regs(char *token) {
    int i;

    if (token == NULL)
        return -1;

    for (i = 0; i < REGISTER_COUNT; i++) {
        if (strcmp(token, registers[i]) == 0)
            return i; /* returns the index in instructions array */
    }

    return -1; /* returns -1 if token isn't instruction */
}

DataType data_instruction(char *line) {
    int i;
    char token[MAX_LINE_LENGTH];
    char original_line[MAX_LINE_LENGTH];

    strcpy(original_line, line);
    extract_next(line, token, ' ');

    if (strcmp(token, "") == 0)
        return NOT_DATA;

    if (strcmp(token, ".data") == 0) {
        return DATA;
    }

    if (strcmp(token, ".string") == 0) {
        return STRING;
    }

    strcpy(line, original_line);
    return NOT_DATA;
}

int is_extern(char *line) {
    int i;
    char token[MAX_LINE_LENGTH];
    char original_line[MAX_LINE_LENGTH];

    strcpy(original_line, line);
    extract_next(line, token, ' ');

    if (strlen(token) == 0)
        return 0;

    /* if line doesnt start with .extern */
    if (!starts_with(token, ".extern")) {
        strcpy(line, original_line);
        return 0;
    }

    return 1;
}

int is_entry(char *line) {
    int i;
    char token[MAX_LINE_LENGTH];
    char original_line[MAX_LINE_LENGTH];

    strcpy(original_line, line);
    extract_next(line, token, ' ');

    if (strlen(token) == 0)
        return 0;

    /* if line does not start with .entry */
    if (!starts_with(token, ".entry")) {
        strcpy(line, original_line);
        return 0;
    }

    return 1;
}

int extract_symbol(char *line, char *sym_name, char delimeter) {
    int ret_code;
    char first_token[MAX_LINE_LENGTH] = "";
    char original_line[MAX_LINE_LENGTH];

    ret_code = 1;
    strcpy(original_line, line);

    if (delimeter == ':' && strchr(line, delimeter) == NULL) {
        return 0; // ':' not found
    }

    extract_next(line, first_token, delimeter);
    ret_code = check_symbol_name(first_token);

    if (!ret_code) {
        strcpy(line, original_line);
        return ret_code;
    }

    strcpy(sym_name, first_token);
    return 1;
}

int check_symbol_name(char *first_token) {
    int ret_code = 1; /* token is bigger than size of label or empty -  its invalid */
    if (strlen(first_token) > (MAX_LABEL_LENGTH + 1) || strlen(first_token) == 0) {
        ret_code = 0;
    }

    /*starts with english char */
    if (!isalpha(*first_token)) {
        ret_code = 0;
    }

    /* contain only english chars and numbers */
    if (!is_valid_string(first_token)) {
        ret_code = 0;
    }

    /* isnt  opcode, instruct or register name */
    if (what_instrct(first_token) > -1 || what_opcode(first_token) > -1 || what_regs(first_token) > -1) {
        ret_code = 0;
    }
    return ret_code;
}

int extract_opcode(char *line) {
    int opcode;
    char token[MAX_LINE_LENGTH] = "";
    char original_line[MAX_LINE_LENGTH];

    strcpy(original_line, line);

    extract_next(line, token, ' ');

    opcode = what_opcode(token);

    if (opcode < 0) {
        strcpy(line, original_line);
        return opcode;
    }
    return opcode;
}


int encode_numeric_data(char *line, code_cont **data, int *dc) {
    int i, count, is_negative, num;
    unsigned short val;
    char curr_token[MAX_LINE_LENGTH];

    count = 0;

    while (extract_next(line, curr_token, ',')) {
        if (*curr_token == '\0') {
            /* error - empty token */
        }
        i = 0;
        if (*curr_token == '-') {
            /* negative num */
            i = 1;
        }
        /* valid number */
        for (i; i < strlen(curr_token); i++) {
            if (!isdigit(curr_token[i])) {
                /*error - not num*/
                return 0;
            }
        }
        num = atoi(curr_token);
        val = conv_to_ushort(num);
        add_data(data, val, dc);

        count++;
    }

    return count;
}

int encode_string(char *line, code_cont **data, int *dc) {
    int count;
    unsigned short val;
    char curr_token[MAX_LINE_LENGTH];

    count = 0;

    extract_next(line, curr_token, '\"');
    if (*curr_token != '\0') {
        /* error - extra text before first " */
        /* return */
    }

    extract_next(line, curr_token, '\"');
    while (curr_token[count] != '\0') {
        val = conv_to_ushort((int) curr_token[count]);
        add_data(data, val, dc);

        count++;
    }
    /*null-terminator*/
    add_data(data, 0, dc);
    count++;

    return count;
}

/* need to add line location in file for error description */
int encode_data(char *line, DataType data_type, code_cont **data, int *dc) {
    int count;

    /* data type is .data */
    switch (data_type) {
        case DATA: {
            count = encode_numeric_data(line, data, dc);
            break;
        }
        case STRING: {
            count = encode_string(line, data, dc);
            break;
        }
        default: {
            /* error */
            count = 0;
        }
    }
    return count;
}


unsigned short conv_to_ushort(int dec_num) {
    unsigned short bin = 0;
    /* return ushort value of dec_num as 15bit */
    return (dec_num & ~(1U << MAX_BIN_LENGTH));
}

char *strduplic(const char *s) {
    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (copy) {
        memcpy(copy, s, len);
    }
    return copy;
}

