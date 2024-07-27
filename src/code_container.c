#include "code_container.h"

#include <stdlib.h>


int add_data(code_cont **data, unsigned short val, int *dc) {
    int exp_bool;

    exp_bool = expend_memory(data, *dc);
    if (!exp_bool) {
        /*error*/
        return 0;
    }

    (*data + *dc)->bin_rep = val;

    (*dc)++;

    return 1;
}

int expend_memory(code_cont **data, int dc) {
    code_cont *temp;

    temp = realloc(*data, (dc + 1) * sizeof(code_cont));

    if (*data == NULL) {
        /*error*/
        return 0;
    }

    *data = temp;
    return 1;
}


