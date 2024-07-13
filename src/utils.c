#include "../include/utils.h"

char *opcodes[] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "red", "prn", "jsr",
                   "rts", "stop"};
char *instructions[] = {".data", ".string", "entry", "extern"};
char *registers[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};


int starts_with(const char *str, const char *pre) {
    return strncmp(pre, str, strlen(pre)) == 0;
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

int what_opcode(char *token) {
    int i;

    if (token == NULL)
        return -1;

    for (i = 0; i < OPCODES_COUNT; i++) {
        if (strcmp(token, opcodes[i]) == 0)
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
