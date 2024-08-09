#include "../include/file.h"


void create_file(file_struct *file, char *filename) {
    file->filename = filename;
    file->errors = malloc(sizeof(int) * INITIAL_ERROR_SIZE);
    file->error_size = INITIAL_ERROR_SIZE;
    file->error_count = 0;
}