#ifndef OPENU_PROJECT_FILE_H
#define OPENU_PROJECT_FILE_H

#define INITIAL_ERROR_SIZE 10

#include <malloc.h>
#include "../include/errors.h"

typedef struct file_struct {
    char *filename;
    Error *errors;
    int errors_count;
    int errors_size;
} file_struct;

void create_file(file_struct *file, char *filename);

int add_error_to_file(file_struct *file, int error_id, int error_line, STAGE_ERROR stage_error);

void enlarge_errors_arr(file_struct *file);

void print_errors(file_struct *file);

void handle_dynamic_alloc_error();

void free_files(file_struct *files, int num_files);

#endif

