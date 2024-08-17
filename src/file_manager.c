#include "../include/file_manager.h"

char *error_desc[] = {
        /* 0  - no error*/
        "",

        /* externals errors */
        /* 1 */
        "File opening failed",
        /* 2 */
        "Dynamic memory allocation failed",
        /* 3 */
        "Creating macro table failed",
        /* 4 */
        "Opening processed file for writing failed",
        /* 5 */
        "",
        /* 6 */
        "",
        /* 7 */
        "",
        /* 8 */
        "",
        /* 9 */
        "Errors were found in first stage",
        /* 10 */
        "",

        /*internals errors*/
        /* 11 */
        "Trying to initailize macro, but it is not declared",
        /* 12 */
        "Macro name is invalid",
        /* 13 */
        "Macro declaration error - Extra text after end of declaration",
        /* 14 */
        "Macro declaration error - Macro name is used more than once", /*insert*/
        /* 15 */
        "Data - string declaration error - Extra text after first \"", /*encode string*/
        /* 16 */
        "Data - numeric declaraion error - No numeric values", /*encode numeric data*/
        /* 17 */
        "Data - numeric declaraion error - declaration ends with ','", /*encode numeric data*/
        /* 18 */
        "Data - numeric declaraion error - non-numeric value entered", /*encode numeric data*/
        /* 19 */
        "Invalid data type", /*encode_data - maybe the error can be removed*/
        /* 20 */
        "Entry label was never initialized", /*validate_entries, check if the error description is good */
        /* 21 */
        "Command - Invalid opcode", /*build_command */
        /* 22 */
        "Command - Extra text after command", /*build_command*/
        /* 23 */
        "Command - invalid dst",
        /* 24 */
        "Command - src or dst method illegal",
        /* 25 */
        "Command - invalid arguments count",
        /* 26 */
        "Symbol Table - Label name is used more than once",
        /* 27 */
        "Macro declaration error - Macro declaration without macro name",
        /* 28 */
        "Macro declaration error - Macro name cant be instruction, opcode or register name",
        /* 29 */
        "Macro declaration error - Macro name cannot be 'macr'",
        /* 30 */
        "Data - numeric value out of bound",
        /* 31 */
        "Command - numeric value out of bound",
        /* 32 */
        "Data - Binary file size exceeds maximum value",
        /* 33 */
        "Command - Symbol used is not defined",
        /* 34 */
        "Macro declaration error - Extra text after 'endmacr'",
        /* 35 */
        "Line too long",
        /* 36 */
        "Symbol name is missing",
        /* 37 */
        "Symbol name is invalid",
        /* 38 */
        "Symbol declaration cannot contain .extern or .entry",
        /* 39 */
        "Data - String missing \"",
        /* 40 */
        "Data - string declaration error - Extra text after string",
};

char *stage_name[] = {
        "unassigned",
        "pre-process",
        "first",
        "second"};

void create_file(file_struct *file, char *filename) {
    file->filename = filename;
    file->errors = malloc(sizeof(Error) * INITIAL_ERROR_SIZE);
    if (file->errors == NULL) {
        handle_dynamic_alloc_error();
    }
    file->errors_size = INITIAL_ERROR_SIZE;
    file->errors_count = 0;
}


void add_error_to_file(file_struct *file, int error_id, int error_line, STAGE_ERROR stage_error) {
    int i;

    i = file->errors_count;

    if (file->errors_count == file->errors_size) {
        enlarge_errors_arr(file);
    }

    file->errors[i].error_id = error_id;
    file->errors[i].error_line = error_line;
    file->errors[i].stage_error = stage_error;

    file->errors_count++;
}

void enlarge_errors_arr(file_struct *file) {
    int new_size;
    Error *temp_errors;

    new_size = file->errors_size * 2;

    temp_errors = realloc(file->errors, sizeof(Error) * new_size);
    if (temp_errors == NULL) {
        handle_dynamic_alloc_error();
    }

    file->errors = temp_errors;
    file->errors_size *= 2;
}

void print_errors(file_struct *file) {
    int i;
    char *relevant_file;
    if (file->errors_count == 0) {
        fprintf(stdout, "File %s passed\n", file->filename);
        return;
    }

    fprintf(stderr, "List of errors in file \'%s\':\n", file->filename);
    for (i = 0; i < file->errors_count; i++) {
        int error_id, error_line, stage_id;

        error_id = file->errors[i].error_id;
        error_line = file->errors[i].error_line;
        stage_id = file->errors[i].stage_error;
        switch (file->errors[i].stage_error) {
            case PRE_STAGE: {
                relevant_file = add_file_extension(file->filename, PREPROCESSED_FILE_TYPE);
                break;
            }
            case FIRST_STAGE:
            case SECOND_STAGE: {
                relevant_file = add_file_extension(file->filename, PROCESSED_FILE_TYPE);
                break;
            }
            default: {
                relevant_file = strduplic(file->filename);
            }
        }

        fprintf(stderr, "\tError: %s, occurred in %s:%d in %s stage.\n", error_desc[error_id], relevant_file,
                error_line,
                stage_name[stage_id]);
    }
    if (relevant_file != NULL) {
        free(relevant_file);
    }
    fprintf(stderr, "Overall %d errors.\n\n", file->errors_count);
}

void handle_dynamic_alloc_error() {
    fprintf(stderr, "Error: %s\n", error_desc[ERROR_ID_2]);
    exit(2);
}

void free_files(file_struct *files, int num_files) {
    int i;
    for (i = 0; i < num_files; ++i) {
        free((files + i)->errors);
    }
    free(files);
}
