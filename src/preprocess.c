#include "../include/preprocess.h"
#include "../include/consts.h"

/* preprocess function */
int preprocess(char filename[]) {
    MacroTable *macros;
    int ret_code = 1, n_line = 0;
    char line[MAX_LINE_LENGTH + 1];
    FILE *file, *final_file;

    /* open file */
    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        ret_code = 0;
        return ret_code;
    }
    /* initialize macro table */
    macros = create_table();
    if (macros == NULL) {
        fprintf(stderr, "Error creating macro table\n");
        fclose(file);
        return 0;
    }

    /* read lines */
    final_file = fopen("preprocessed.txt", "w"); /* TODO: create final file name */
    if (final_file == NULL) {
        fprintf(stderr, "Error opening final file for writing\n");
        free_table(macros);
        fclose(file);
        return 0;
    }

    while (fgets(line, sizeof(line), file)) {
        n_line++;
        /* preprocess line if not empty */
        if (strcmp(line, "\n") != 0) {
            if (!process_line(line, file, final_file, macros)) {
                ret_code = 0;
                break;
            }
        }
    }

    free_table(macros);
    fclose(file);
    fclose(final_file);
    return ret_code;
}

/* process line and write to new preprocessed file */
int process_line(char line[], FILE *file, FILE *final_file, MacroTable *macros) {
    char *mac_name;
    char *mac_content;
    char orig_line[MAX_LINE_LENGTH + 1];
    char first_token[MAX_LINE_LENGTH];

    strcpy(orig_line, line);
    extract_next(line, first_token, ' ');

    if (is_macro(first_token)) {
        handle_macro(line, file, macros);
        return 1;
    } else if (is_member(macros, first_token)) {
        mac_name = first_token;
        mac_content = search(macros, mac_name);
        if (mac_content == NULL) {
            fprintf(stderr, "Error: Macro %s not declared\n", mac_name);
            return 0;
        }
        fprintf(final_file, "%s", mac_content);
    } else {
        fprintf(final_file, "%s", orig_line);
    }
    return 1;
}

/* handle macro declaration */
void handle_macro(char line[], FILE *file, MacroTable *macros) {
    size_t len;
    size_t total_length = 0;
    size_t buffer_size;
    char mac_name[MAX_LINE_LENGTH];
    char *mac_content;

    /* extracting the macro name */
    extract_next(line, mac_name, ' '); /* TODO: validate macro name */

    buffer_size = MAX_LINE_LENGTH * sizeof(char) * 10;
    mac_content = malloc(buffer_size);
    if (mac_content == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    mac_content[0] = '\0';

    while (fgets(line, sizeof(line), file) != NULL && !starts_with(line, "endmacr")) {
        len = strlen(line);
        if (total_length + len + 1 >= buffer_size) {
            buffer_size *= 2;
            mac_content = (char *) realloc(mac_content, buffer_size);
            if (mac_content == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                exit(1);
            }
        }
        strcat(mac_content, line);
        total_length += len;
    }
    insert(macros, mac_name, mac_content);
    free(mac_content);
}

/* check if line is macro declaration */
int is_macro(char *line) {
    return starts_with(line, "macr");
}
