#include <stdio.h>
#include "../include/preprocess.h"
#include "../include/first_stage.h"
#include "../include/file_manager.h"

int main(int argc, char *argv[]) {
    int i, num_files = 0;
    file_struct *files;
    if (argc < 2) {
        fprintf(stderr, "Error missing files, Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return 1;
    }
    files = malloc(sizeof(file_struct) * (argc - 1));
    for (i = 1; i < argc; ++i) {
        num_files++;
        create_file((files + i - 1), argv[i]);
    }
    for (i = 0; i < num_files; ++i) {
        preprocess((files + i));
    }

    for (i = 0; i < num_files; ++i) {
        first_stage_process((files + i));
    }
    for (i = 0; i < num_files; ++i) {
        printf("%d\n", (files + i)->errors_count);
    }
    free_files(files, num_files);
    printf("done\n");

    return 0;
}

