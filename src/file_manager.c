#include "../include/file_manager.h"
#include "../include/consts.h"

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
    "Opening final file for writing failed",
    /* 5 */
    "",
    /* 6 */
    "",
    /* 7 */
    "",
    /* 8 */
    "",
    /* 9 */
    "",
    /* 10 */
    "",

    /*internals errors*/
    /* 11 */
    "Macro is not declared",
    /* 12 */
    "Macro name is invalid",
    /* 13 */
    "Macro declaration error - Extraneous text after end of declaration",
    /* 14 */
    "Macro declaration error - Macro name is used more than once", /*insert*/
    /* 15 */
    "Data - string declaration error - Extraneous text after first \" ", /*encode string*/
    /* 16 */
    "Data - numeric declaraion error - No numeric values ", /*encode numeric data*/
    /* 17 */
    "Data - numeric declaraion error - declaration ends with ','", /*encode numeric data*/
    /* 18 */
    "Data - numeric declaraion error - non-numeric value entered ", /*encode numeric data*/
    /* 19 */
    "Unvalid data type ", /*encode_data - maybe the error can be removed*/
    /* 20 */
    "Entry label was never initialized", /*validate_entries*/
    /* 21 */
    "Command - Invalid opcode", /*build_command */
    /* 22 */
    "Command - Extraneous text after command", /*build_command*/
    /* 23 */
    "Command - invalid dst",
    /* 24 */
    "Command - src or dst method illegal",
    /* 25 */
    "Command - invalid arguments count",
    /* 26 */
    "Label name is used more than once",
};

char *stage_name[] = {
    "Unassigned",
    "Pre-process",
    "First",
    "Second"
};

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

    for (i = 0; i <= file->errors_count; i++) {
        int error_id, error_line, stage_id;

        error_id = file->errors[i].error_id;
        error_line = file->errors[i].error_line;
        stage_id = file->errors[i].stage_error;

        fprintf(stderr, "Error: %s occurred at line %d\n in %s stage", error_desc[error_id], error_line,
                stage_name[stage_id]);
    }
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
