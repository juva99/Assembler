#include "code_container.h"


int add_data(code_cont **data, unsigned short val, int *dc) {
    /* allocate memory for current data cell */

    (*data + *dc)->bin_rep = val;

    (*dc)++;
}


