#include "../include/file.h"


void create_file(file_struct *file, char *filename) {
    file->filename = filename;
    file->errors = malloc(sizeof(int) * INITIAL_ERROR_SIZE);
    file->error_size = INITIAL_ERROR_SIZE;
    file->error_count = 0;
}

void free_files(file_struct *files, int num_files) {
    int i;
    for (i = 0; i < num_files; ++i) {
        free((files + i)->errors);
    }
    free(files);
}