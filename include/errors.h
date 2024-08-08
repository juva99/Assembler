#ifndef ERRORS_H
#define ERRORS_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Error {
    int error_id;
    char *error_desc; /* error description */
} Error;

typedef enum ERROR_IDS {
    ERROR_ID_0,
    ERROR_ID_1,
    ERROR_ID_2,
    ERROR_ID_3,
    ERROR_ID_4,
    ERROR_ID_5,
    ERROR_ID_6,
    ERROR_ID_7
} ERROR_IDS;

#endif //ERRORS_H
