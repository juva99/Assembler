#include "../include/file_manager.h"

char *error_desc[] = {
        /* 0  - no error*/
        "",

        /* externals errors */
        /* 1 */
        "General: File opening failed",
        /* 2 */
        "General: Dynamic memory allocation failed",
        /* 3 */
        "General: Creating macro table failed",
        /* 4 */
        "General: Opening processed file for writing failed",
        /* 5 */
        "",
        /* 6 */
        "",
        /* 7 */
        "",
        /* 8 */
        "",
        /* 9 */
        "General: Errors were found in first stage",
        /* 10 */
        "",

        /*internals errors*/
        /* 11 */
        "Macro: Trying to initialize macro, but it is not declared",
        /* 12 */
        "Macro: name is invalid",
        /* 13 */
        "Macro: Extra text after end of declaration",
        /* 14 */
        "Macro: Macro name is used more than once", /*insert*/
        /* 15 */
        "Data.String: Extra text after first \"", /*encode string*/
        /* 16 */
        "Data.Numeric: No numeric values", /*encode numeric data*/
        /* 17 */
        "Data.Numeric: declaration ends with ','", /*encode numeric data*/
        /* 18 */
        "Data.Numeric: non-numeric value entered", /*encode numeric data*/
        /* 19 */
        "Data: Invalid data type", /*encode_data - maybe the error can be removed*/
        /* 20 */
        "General: Entry label was never initialized", /*validate_entries, check if the error description is good */
        /* 21 */
        "Command: Invalid opcode", /*build_command */
        /* 22 */
        "Command: Extra text after command", /*build_command*/
        /* 23 */
        "Command: invalid dst",
        /* 24 */
        "Command: src or dst method illegal",
        /* 25 */
        "Command: invalid arguments count",
        /* 26 */
        "Symbol Table - Label name is used more than once",
        /* 27 */
        "Marco: Macro declaration without macro name",
        /* 28 */
        "Marco: Macro name cant be instruction, opcode or register name",
        /* 29 */
        "Marco: Macro name cannot be 'macr'",
        /* 30 */
        "Data.Numeric: value out of bound",
        /* 31 */
        "Command: numeric value out of bound",
        /* 32 */
        "General: Binary file size exceeds maximum value",
        /* 33 */
        "Command: Symbol used is not defined",
        /* 34 */
        "Macro: Extra text after 'endmacr'",
        /* 35 */
        "General: Line too long",
        /* 36 */
        "Symbol: name is missing",
        /* 37 */
        "Symbol: name is invalid",
        /* 38 */
        "Symbol: declaration cannot contain .extern or .entry",
        /* 39 */
        "Data.String: String missing \"",
        /* 40 */
        "Data.String: Extra text after string",
        /* 41 */
        "Command: Missing comma",
        /* 42 */
        "Symbol: no whitespace after ':'",
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
    /* skip if error ok */
    if (error_id == ERROR_ID_0) {
        return;
    }

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

void print_errors(file_struct *file, int index) {
    int i, error_id, error_line, stage_id;
    char *relevant_file;

    if (index == 0) {
        printf("--------------------------------------------------------------\n");
    }
    if (file->errors_count == 0) {
        fprintf(stdout, "File %s passed\n", file->filename);
        printf("--------------------------------------------------------------\n");
        return;
    }
    fprintf(stdout, "File %s failed at %s stage\n", file->filename, stage_name[file->errors[0].stage_error]);
    fprintf(stderr, "List of errors in file \'%s\':\n", file->filename);
    for (i = 0; i < file->errors_count; i++) {
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
    printf("--------------------------------------------------------------\n");
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
