#include <stdio.h>
#include "../include/preprocess.h"
#include "../include/first_stage.h"
#include "../include/file_manager.h"

/**
 * @brief The main entry point for the assembler program.
 *
 * This function processes a list of assembly source files provided as command-line arguments.
 * It performs preprocessing, the first stage of assembly (which handles the execution of the
 * second stage), and prints any errors encountered during processing.
 * Finally, it frees all allocated resources and exits.
 *
 * @param argc: The number of command-line arguments, including the program name.
 * @param argv: An array of command-line arguments, where each argument is a filename.
 * @return Returns 0 on successful completion, or 1 if no files are provided.
 */
int main(int argc, char *argv[]) {
    int i, num_files = 0;
    file_struct *files;

    /* Check if at least one file is provided */
    if (argc < 2) {
        fprintf(stderr, "Error missing files, Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return 1;
    }

    /* Allocate memory for file structures based on the number of files */
    files = malloc(sizeof(file_struct) * (argc - 1));

    /* Initialize file structures */
    for (i = 1; i < argc; ++i) {
        num_files++;
        create_file((files + i - 1), argv[i]);
    }

    /* Preprocess each file */
    for (i = 0; i < num_files; ++i) {
        preprocess((files + i));
    }

    /* Perform the first stage of assembly for each file
       Note: The first stage also handles running the second stage. */
    for (i = 0; i < num_files; ++i) {
        /* continue to first and second stage if no errors in preprocess */
        if ((files + i)->errors_count == 0) {
            first_stage_process((files + i));
        }
    }

    /* Print errors for each file */
    for (i = 0; i < num_files; ++i) {
        print_errors(files + i);
    }

    /* Free all allocated resources */
    free_files(files, num_files);
    printf("done\n");

    return 0;
}

