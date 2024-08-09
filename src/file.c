#include "../include/file.h"


void create_file(file_struct *file, char *filename) {
    file->filename = filename;
    file->errors = malloc(sizeof(Error) * INITIAL_ERROR_SIZE);
    if (file->errors == NULL) {
        /*error - failed allocate memory for errors array */
    }
    file->errors_size = INITIAL_ERROR_SIZE;
    file->errors_count = 0;
}


int add_error_to_file(file_struct *file, int error_id, int error_line, STAGE_ERROR stage_error) {
    int i;

    i = file->errors_count;

    if (file->errors_count == file->errors_size) {
        enlarge_errors(file);
    }

    file->errors[i].error_id = error_id;
    /* make a char* array with error description for each error_id */
    file->errors[i].error_desc = errors[error_id];
    file->errors[i].error_line = error_line;
    file->errors[i].stage_error = stage_error;

    file->errors_count++;

    return 1;
}

void enlarge_errors(file_struct *file) {
    int new_size;
    Error *temp_errors;

    new_size = file->errors_size * 2;

    temp_errors = realloc(file->errors, sizeof(Error) * new_size);
    if (temp_errors == NULL) {
        /*error - failed to allocate memory */
    }

    file->errors = temp_errors;
    file->errors_size *= 2;
}
