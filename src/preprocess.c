#include "../include/preprocess.h"

/* preprocess function */
int preprocess(file_struct *curr_file) {
    MacroTable *macros;
    int n_line = 0, error_id;
    char line[MAX_LINE_LENGTH];
    char *preprocessed_filename;
    char *processed_filename;
    FILE *file, *proccessed_file;


    /* open file */
    preprocessed_filename = add_file_extension(curr_file->filename, PREPROCESSED_FILE_TYPE);
    file = fopen(preprocessed_filename, "r");
    free(preprocessed_filename);
    if (file == NULL) {
        add_error_to_file(curr_file, ERROR_ID_1, n_line, PRE_STAGE);
        return ERROR_ID_1;
    }

    /* initialize macro table */
    macros = create_table();

    processed_filename = add_file_extension(curr_file->filename, PROCESSED_FILE_TYPE);

    /* read lines */
    proccessed_file = fopen(processed_filename, "w");
    free(processed_filename);

    if (proccessed_file == NULL) {
        add_error_to_file(curr_file, ERROR_ID_4, n_line, PRE_STAGE);
        return ERROR_ID_4;
    }

    while (fgets(line, sizeof(line), file)) {
        n_line++;
        /* preprocess line if not empty */
        if (strcmp(line, "\n") != 0) {
            error_id = process_line(line, file, proccessed_file, macros);
            if (error_id != ERROR_ID_0) {
                add_error_to_file(curr_file, error_id, n_line, PRE_STAGE);
                break;
            }
        }
    }

    free_table(macros);
    fclose(file);
    fclose(proccessed_file);
    return ERROR_ID_0;
}

/* process line and write to new preprocessed file */
int process_line(char line[], FILE *file, FILE *final_file, MacroTable *macros) {
    int error_id;
    char *mac_name;
    char *mac_content;
    char orig_line[MAX_LINE_LENGTH];
    char first_token[MAX_LINE_LENGTH];

    strcpy(orig_line, line);
    extract_next(line, first_token, ' ');

    if (is_macro(first_token)) {
        error_id = handle_macro(line, file, macros);
        if (error_id != ERROR_ID_0) {
            return error_id;
        }
    } else if (is_member(macros, first_token)) {
        mac_name = first_token;
        mac_content = search(macros, mac_name);
        if (mac_content == NULL) {
            /* error - Trying to initailize macro, but it is not declared */
            return ERROR_ID_11;
        }
        fprintf(final_file, "%s", mac_content);
    } else {
        fprintf(final_file, "%s", orig_line);
    }
    return ERROR_ID_0;
}

/* handle macro declaration */
int handle_macro(char *line, FILE *file, MacroTable *macros) {
    int error_id;
    size_t len;
    size_t total_length = 0;
    size_t buffer_size;
    char mac_name[MAX_LINE_LENGTH];
    char *mac_content;

    /* extracting the macro name */
    extract_next(line, mac_name, ' ');
    error_id = is_macro_name_valid(mac_name);
    if (error_id != ERROR_ID_0) {
        return error_id;
    }

    /* checks if rest is empty */
    if (strlen(line) != 0) {
        /* error - Extraneous text after end of declaration */
        return ERROR_ID_13;
    }

    buffer_size = MAX_LINE_LENGTH * sizeof(char) * INITIAL_MACRO_BUFFER;
    mac_content = malloc(buffer_size);
    if (mac_content == NULL) {
        handle_dynamic_alloc_error();
    }
    mac_content[0] = '\0';

    while (fgets(line, sizeof(line), file) != NULL && !starts_with(line, "endmacr")) {
        len = strlen(line);
        if (total_length + len + 1 >= buffer_size) {
            buffer_size *= 2;
            mac_content = (char *) realloc(mac_content, buffer_size);
            if (mac_content == NULL) {
                handle_dynamic_alloc_error();
            }
        }
        strcat(mac_content, line);
        total_length += len;
    }
    error_id = insert(macros, mac_name, mac_content);
    if (error_id != 0) {
        return error_id;
    }
    free(mac_content);

    return ERROR_ID_0;
}

/* check if line is macro declaration */
int is_macro(char *line) {
    return starts_with(line, "macr");
}

int is_macro_name_valid(char *mac_name) {
    if (mac_name == NULL) {
        /* error - macro declaration without macro name */
        return ERROR_ID_27;
    }

    if (what_instrct(mac_name) >= 0 || what_opcode(mac_name) >= 0 || what_regs(mac_name) >= 0)
        /* error - Macro name cant be instruction, opcode or register name */
        return ERROR_ID_28;

    if (strcmp(mac_name, "macr") == 0)
        /* error - Macro name cannot be 'macr' */
        return ERROR_ID_29;

    return ERROR_ID_0;
}


