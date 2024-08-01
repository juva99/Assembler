#include "../include/code_container.h"


int write_data(code_cont **container, unsigned short data, int *counter) {
    int success;
    if (!expend_memory(container, *counter)) {
        /* expend error */
        return 0;
    }
    (*container + *counter)->bin_rep = data;
    (*counter)++;
    return 1;
}

int add_data(code_cont **data, unsigned short val, int *dc) {
    return write_data(data, val, dc);
}

int write_data_label(code_cont **container, unsigned short data, int *counter, char *label) {
    if (!write_data(container, data, counter))
        return 0;
    (*container + *counter - 1)->label = strduplic(label);
    return 1;
}


int expend_memory(code_cont **container, int counter) {
    code_cont *temp;

    temp = realloc(*container, (counter + 1) * sizeof(code_cont));
    if (temp == NULL) {
        /*error*/
        return 0;
    }
    *container = temp;
    return 1;
}

code_cont *create_container() {
    code_cont *temp;
    temp = malloc(sizeof(code_cont));
    return temp;
}

