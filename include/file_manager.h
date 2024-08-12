#ifndef OPENU_PROJECT_FILE_H
#define OPENU_PROJECT_FILE_H

#define INITIAL_ERROR_SIZE 10

#include <malloc.h>
#include <stdio.h>

typedef enum STAGE_ERROR {
    UNASSIGNED,
    PRE_STAGE,
    FIRST_STAGE,
    SECOND_STAGE
} STAGE_ERROR;

typedef struct Error {
    int error_id;
    int error_line;
    STAGE_ERROR stage_error;
} Error;

typedef enum ERROR_IDS {
    ERROR_ID_0 = 0,
    ERROR_ID_1 = 1,
    ERROR_ID_2 = 2,
    ERROR_ID_3 = 3,
    ERROR_ID_4 = 4,

    ERROR_ID_9 = 9,

    ERROR_ID_11 = 11,
    ERROR_ID_12 = 12,
    ERROR_ID_13 = 13,
    ERROR_ID_14 = 14,
    ERROR_ID_15 = 15,
    ERROR_ID_16 = 16,
    ERROR_ID_17 = 17,
    ERROR_ID_18 = 18,
    ERROR_ID_19 = 19,
    ERROR_ID_20 = 20,
    ERROR_ID_21 = 21,
    ERROR_ID_22 = 22,
    ERROR_ID_23 = 23,
    ERROR_ID_24 = 24,
    ERROR_ID_25 = 25,
    ERROR_ID_26 = 26,
    ERROR_ID_27 = 27,
    ERROR_ID_28 = 28,
    ERROR_ID_29 = 29,
    ERROR_ID_30 = 30,
    ERROR_ID_31 = 31,
    ERROR_ID_32 = 32
} ERROR_IDS;

typedef struct file_struct {
    char *filename;
    Error *errors;
    int errors_count;
    int errors_size;
} file_struct;

void create_file(file_struct *file, char *filename);

void add_error_to_file(file_struct *file, int error_id, int error_line, STAGE_ERROR stage_error);

void enlarge_errors_arr(file_struct *file);

void print_errors(file_struct *file);

void handle_dynamic_alloc_error();

void free_files(file_struct *files, int num_files);

#endif

