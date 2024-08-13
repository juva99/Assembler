#include "../include/first_stage.h"

int first_stage_process(file_struct *curr_file) {
    int ic, dc, symbol, errors, curr_error_id, n_line;
    char line[MAX_LINE_LENGTH + 1];
    DataType data_type;
    char sym_name[MAX_LABEL_LENGTH + 1];
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
    errors = 0;
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
        if (extract_symbol(line, sym_name, ':')) {
            symbol = 1;
        }
        /* check if line is a data storing instruction #5 */
        data_type = data_instruction(line);
        if (data_type != NOT_DATA) {
            if (symbol) {
                /* insert to data table #6 */
                curr_error_id = insert_symbol_table(sym_table, sym_name, ".data", dc);
                if (curr_error_id != ERROR_ID_0) {
                    add_error_to_file(curr_file, curr_error_id, n_line, FIRST_STAGE);
                    errors++;
                }
            }
            /* encode data to memory return size and increase DC #7 */
            curr_error_id = encode_data(line, data_type, &data, &dc, n_line);
            if (curr_error_id != ERROR_ID_0) {
                add_error_to_file(curr_file, curr_error_id, n_line, FIRST_STAGE);
                errors++;
            }
            continue;
        }
        /* #8 */
        if (is_extern(line)) {
            if (extract_symbol(line, sym_name, ' ')) {
                curr_error_id = insert_symbol_table(sym_table, sym_name, ".external", 0);
                if (curr_error_id != ERROR_ID_0) {
                    add_error_to_file(curr_file, curr_error_id, n_line, FIRST_STAGE);
                    errors++;
                }
            }
            continue;
        }

        if (is_entry(line)) {
            if (extract_symbol(line, sym_name, ' ')) {
                add_symbol(entries_list, sym_name, n_line);
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
                errors++;
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
