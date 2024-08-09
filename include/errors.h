#ifndef ERRORS_H
#define ERRORS_H

#include <stdlib.h>
#include <stdio.h>

typedef enum STAGE_ERROR {
    UNASSIGNED,
    PRE,
    FIRST,
    SECOND
} STAGE_ERROR;

typedef struct Error {
    int error_id;
    char *error_desc;
    int error_line;
    STAGE_ERROR stage_error;
} Error;

typedef enum ERROR_IDS {
    ERROR_ID_0,
    ERROR_ID_1,
    ERROR_ID_2,
    ERROR_ID_3,
    ERROR_ID_4,
    ERROR_ID_5,
    ERROR_ID_6,
    ERROR_ID_7,
    ERROR_ID_11,
    ERROR_ID_12,
    ERROR_ID_13,
    ERROR_ID_14,
    ERROR_ID_15,
    ERROR_ID_16,
    ERROR_ID_17,
    ERROR_ID_18,
    ERROR_ID_19,
    ERROR_ID_20,
    ERROR_ID_21,
    ERROR_ID_22,
    ERROR_ID_23,
    ERROR_ID_24,
    ERROR_ID_25,
    ERROR_ID_26
} ERROR_IDS;

#endif //ERRORS_H
