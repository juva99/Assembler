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
            return 0;
        }
        str++;
    }
    return 1;
}

int extract_next(char *src, char *next, char delimiter) {
    return extract_next_full(src, next, delimiter, 1);
}

int extract_next_full(char *src, char *next, char delimiter, int remove_spaces) {
    char *ptr = src;
    char *rest_start;
    int found = 0;

    /* Skip leading spaces */
    while (remove_spaces && isspace((unsigned char) *ptr)) {
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
    while (remove_spaces && isspace((unsigned char) *ptr)) {
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
    char token[MAX_LINE_LENGTH];
    char original_line[MAX_LINE_LENGTH];

    strcpy(original_line, line);
    extract_next(line, token, ' ');

    if (strlen(token) == 0)
        return 0;

    /* if line does not start with .extern */
    if (!starts_with(token, ".extern")) {
        strcpy(line, original_line);
        return 0;
    }

    return 1;
}

int is_entry(char *line) {
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

int is_comment(char *line) {
    char token[MAX_LINE_LENGTH];
    char original_line[MAX_LINE_LENGTH];

    strcpy(original_line, line);
    extract_next(line, token, ' ');

    if (strlen(token) == 0)
        return 0;

    if (*token == ';') {
        return 1;
    }

    strcpy(line, original_line);
    return 0;
}

int extract_symbol(char *line, char *sym_name, char delimeter) {
    int ret_code;
    char first_token[MAX_LINE_LENGTH] = "";
    char original_line[MAX_LINE_LENGTH];

    ret_code = 1;
    strcpy(original_line, line);

    if (delimeter == ':' && strchr(line, delimeter) == NULL) {
        return 0;
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


int encode_numeric_data(char *line, code_cont **data, int *dc, int n_line) {
    int i, count, num;
    unsigned short val;
    char curr_token[MAX_LINE_LENGTH];

    count = 0;

    while (extract_next(line, curr_token, ',')) {
        if (*curr_token == '\0') {
            if (count == 0) {
                /* error - no numeric values */
                return ERROR_ID_16;
            } else {
                /*error - line finished with ',' */
                return ERROR_ID_17;
            }
        }
        i = 0;
        if (*curr_token == '-') {
            /* negative num */
            i = 1;
        }
        /* valid number */
        for (; i < strlen(curr_token); i++) {
            if (!isdigit(curr_token[i])) {
                /*error - not num*/
                return ERROR_ID_18;
            }
        }
        num = atoi(curr_token);
        if (num < MIN_DATA_NUM_VALUE || num > MAX_DATA_NUM_VALUE)
            return ERROR_ID_30;
        val = conv_to_ushort(num);
        add_data(data, val, dc, n_line);

        count++;
    }

    return ERROR_ID_0;
}

int encode_string(char *line, code_cont **data, int *dc, int n_line) {
    int count;
    unsigned short val;
    char curr_token[MAX_LINE_LENGTH];

    count = 0;

    extract_next(line, curr_token, '\"');
    if (*curr_token != '\0') {
        /* error - extra text before first " */
        return ERROR_ID_15;
    }

    extract_next(line, curr_token, '\"');
    while (curr_token[count] != '\0') {
        val = conv_to_ushort((int) curr_token[count]);
        add_data(data, val, dc, n_line);

        count++;
    }
    /*null-terminator*/
    add_data(data, 0, dc, n_line);
    count++;

    return ERROR_ID_0;
}

int encode_data(char *line, DataType data_type, code_cont **data, int *dc, int n_line) {
    int error_id;

    /* data type is .data */
    switch (data_type) {
        case DATA: {
            error_id = encode_numeric_data(line, data, dc, n_line);
            break;
        }
        case STRING: {
            error_id = encode_string(line, data, dc, n_line);
            break;
        }
        default: {
            /* unreachable code */
        }
    }
    return error_id;
}


unsigned short conv_to_ushort(int dec_num) {
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

char *add_file_extension(char *filename, char *extension) {
    char *dup_filename = strduplic(filename);
    dup_filename = (char *) realloc(dup_filename, strlen(dup_filename) + MAX_EXTENSION_LENGTH);
    if (dup_filename == NULL) {
        handle_dynamic_alloc_error();
    }
    strcat(dup_filename, extension);
    return dup_filename;
}

int read_num_arg(char *arg) {
    int is_negative, num;
    arg++;
    is_negative = 1;
    if (*arg == '-') {
        is_negative = -1;
        arg++;
    }
    num = (atoi(arg) * is_negative);
    return num;
}
