#ifndef CODE_CONTAINER_H
#define CODE_CONTAINER_H

typedef struct code_cont {
    unsigned short bin_rep;
    int code_line;
    char *label; /* not in use for data*/
} code_cont;

int add_data(code_cont **data, unsigned short val, int *dc);

int expend_memory(code_cont **data, int dc);

#endif //CODE_CONTAINER_H
