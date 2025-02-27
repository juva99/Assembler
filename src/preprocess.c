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
        if (is_line_too_long(line)) {
            add_error_to_file(curr_file, ERROR_ID_35, n_line, PRE_STAGE);
            while (strchr(line, '\n') == NULL && fgets(line, MAX_LINE_LENGTH, file) != NULL) {
            }
        }

        if (strcmp(line, "\n") != 0) {
            error_id = process_line(line, file, proccessed_file, macros, curr_file, &n_line);
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
int process_line(char line[], FILE *file, FILE *final_file, MacroTable *macros, file_struct *curr_file, int *n_line) {
    char *mac_name;
    char *mac_content;
    char orig_line[MAX_LINE_LENGTH];
    char first_token[MAX_LINE_LENGTH];

    /*check if line is a comment line */
    if (is_comment(line)) {
        return ERROR_ID_0;
    }

    strcpy(orig_line, line);
    extract_next(line, first_token, ' ');

    if (is_macro(first_token)) {
        handle_macro(line, file, macros, curr_file, n_line);
        return ERROR_ID_0;
    } else if (is_member(macros, first_token)) {
        if (strlen(line) > 0) {
            return ERROR_ID_43;
        }
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
void handle_macro(char *line, FILE *file, MacroTable *macros, file_struct *curr_file, int *n_line) {
    int error_id, ret_code, start_line;
    size_t len;
    size_t total_length = 0;
    size_t buffer_size;
    char mac_name[MAX_LINE_LENGTH];
    char *mac_content;

    /* extracting the macro name */
    extract_next(line, mac_name, ' ');
    error_id = is_macro_name_valid(mac_name);
    if (error_id != ERROR_ID_0) {
        add_error_to_file(curr_file, error_id, *n_line, PRE_STAGE);
    }

    /* checks if rest is empty */
    if (strlen(line) != 0) {
        /* error - Extraneous text after end of declaration */
        add_error_to_file(curr_file, ERROR_ID_13, *n_line, PRE_STAGE);
    }

    buffer_size = MAX_LINE_LENGTH * sizeof(char) * INITIAL_MACRO_BUFFER;
    mac_content = malloc(buffer_size);
    if (mac_content == NULL) {
        handle_dynamic_alloc_error();
    }
    mac_content[0] = '\0';

    start_line = *n_line;
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        (*n_line)++;
        if (is_line_too_long(line)) {
            add_error_to_file(curr_file, ERROR_ID_35, *n_line, PRE_STAGE);
            while (strchr(line, '\n') == NULL && fgets(line, MAX_LINE_LENGTH, file) != NULL) {
            }
        }
        /* check if line is a comment line */
        if (is_comment(line)) {
            continue;
        }
        ret_code = is_endmacr(line);
        if (ret_code == ERROR_ID_34) {
            /*error - extra text after 'endmacr' */
            free(mac_content);
            add_error_to_file(curr_file, ERROR_ID_34, *n_line, PRE_STAGE);
            return;
        }
        if (ret_code) {
            /* line is a valid macro end statement*/
            break;
        }

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
        add_error_to_file(curr_file, error_id, start_line, PRE_STAGE);
    }
    free(mac_content);
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

    if (what_instrct(mac_name) >= 0 || what_opcode(mac_name) >= 0 || what_regs(mac_name) >= 0) {
        /* error - Macro name cant be instruction, opcode or register name */
        return ERROR_ID_28;
    }

    if (strcmp(mac_name, "macr") == 0) {
        /* error - Macro name cannot be 'macr' */
        return ERROR_ID_29;
    }

    return ERROR_ID_0;
}
