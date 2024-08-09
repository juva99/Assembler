#ifndef OPENU_PROJECT_FILE_H
#define OPENU_PROJECT_FILE_H

#define INITIAL_ERROR_SIZE 10

#include <malloc.h>

typedef struct file_struct {
    char *filename;
    int *errors;
    int error_count;
    int error_size;
} file_struct;


void create_file(file_struct *file, char *filename);

#endif //OPENU_PROJECT_FILE_H
