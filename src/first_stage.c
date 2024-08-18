#include "../include/first_stage.h"

int first_stage_process(file_struct *curr_file) {
    int ic, dc, symbol, curr_error_id, n_line;
    char line[MAX_LINE_LENGTH];
    DataType data_type;
    char sym_name[MAX_LABEL_LENGTH];
    char *processed_filename;
    FILE *file;

    code_cont *data, *code;
    cmd_struct *command;

    SymTable *sym_table; /* hash table to store symbols */
    SymbolList *entries_list;

    /* initialize data storage */
    sym_table = create_symtable();
    data = create_container();
    code = create_container();
    entries_list = create_symbol_list();

    ic = 0;
    dc = 0;
    n_line = 0;

    processed_filename = add_file_extension(curr_file->filename, PROCESSED_FILE_TYPE);
    file = fopen(processed_filename, "r");
    free(processed_filename);
    if (file == NULL) {
        add_error_to_file(curr_file, ERROR_ID_1, n_line, FIRST_STAGE);
        return 0;
    }

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        n_line++;
        symbol = 0;
        sym_name[0] = '\0';
        /* check if line has a symbol #3 */
        if (is_symbol_declaration(line)) {
            curr_error_id = extract_symbol(line, sym_name, ':');
            if (curr_error_id == ERROR_ID_0) {
                symbol = 1;
            } else {
                /* error - symbol name is invalid */
                add_error_to_file(curr_file, curr_error_id, n_line, FIRST_STAGE);
                continue;
            }
        }
        /* check if line is a data storing instruction #5 */
        data_type = data_instruction(line);
        if (data_type != NOT_DATA) {
            if (symbol) {
                /* insert to data table #6 */
                curr_error_id = insert_symbol_table(sym_table, sym_name, ".data", dc);
                if (curr_error_id != ERROR_ID_0) {
                    add_error_to_file(curr_file, curr_error_id, n_line, FIRST_STAGE);
                }
            }
            /* encode data to memory return size and increase DC #7 */
            curr_error_id = encode_data(line, data_type, &data, &dc, n_line);
            if (curr_error_id != ERROR_ID_0) {
                add_error_to_file(curr_file, curr_error_id, n_line, FIRST_STAGE);
            }
            continue;
        }
        /* #8 */
        if (is_extern(line)) {
            if (symbol) {
                /*error - Symbol declaration cannot contain .extern or .entry */
                add_error_to_file(curr_file, ERROR_ID_38, n_line, FIRST_STAGE);
            }
            curr_error_id = extract_symbol(line, sym_name, ' ');
            if (curr_error_id == ERROR_ID_0) {
                curr_error_id = insert_symbol_table(sym_table, sym_name, ".external", 0);
                add_error_to_file(curr_file, curr_error_id, n_line, FIRST_STAGE);
            } else {
                add_error_to_file(curr_file, curr_error_id, n_line, FIRST_STAGE);
            }
            continue;
        }

        if (is_entry(line)) {
            if (symbol) {
                /*error - Symbol declaration cannot contain .extern or .entry */
                add_error_to_file(curr_file, ERROR_ID_38, n_line, FIRST_STAGE);
            }
            curr_error_id = extract_symbol(line, sym_name, ' ');
            if (curr_error_id == ERROR_ID_0) {
                add_symbol(entries_list, sym_name, n_line);
            } else {
                add_error_to_file(curr_file, curr_error_id, n_line, FIRST_STAGE);
            }
            continue;
        }

        /* construct the instruction and return the length of it */
        curr_error_id = build_command(line, &command);
        if (curr_error_id != ERROR_ID_0) {
            add_error_to_file(curr_file, curr_error_id, n_line, FIRST_STAGE);
            continue;
        }
        if (symbol) {
            curr_error_id = insert_symbol_table(sym_table, sym_name, ".code", ic + IC_OFFSET);
            if (curr_error_id != ERROR_ID_0) {
                add_error_to_file(curr_file, curr_error_id, n_line, FIRST_STAGE);
            }
        }
        add_command(&code, command, &ic, n_line);
        free_command(command);
    }

    fclose(file);

    if (ic + dc + IC_OFFSET > MAX_FILE_SIZE) {
        add_error_to_file(curr_file, ERROR_ID_32, 0, FIRST_STAGE);
    }
    if (curr_file->errors_count > 0) {
        free_container(code, ic);
        free_container(data, dc);
        free_symtable(sym_table);
        free_symbol_list(entries_list);
        return ERROR_ID_9;
    }
    update_data_symbols(sym_table, ic + IC_OFFSET);

    return second_stage_process(curr_file, data, code, sym_table, entries_list, ic, dc);
}
