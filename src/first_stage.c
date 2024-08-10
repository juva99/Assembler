#include "../include/first_stage.h"

int first_stage_process(file_struct *curr_file) {
    int ic, dc, symbol, data_size, instr_len, opcode, errors, curr_error_id;
    char line[MAX_LINE_LENGTH + 1];
    DataType data_type;
    char sym_name[MAX_LABEL_LENGTH + 1];
    char *processed_filename;

    int fake_line = 0;

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

    FILE *file;
    processed_filename = add_file_extension(curr_file->filename, PROCESSED_FILE_TYPE);
    file = fopen(processed_filename, "r");
    if (file == NULL) {
        // change fake_line to actual line number
        add_error_to_file(curr_file, ERROR_ID_2, fake_line, FIRST_STAGE);
    }


    while (fgets(line, sizeof(line), file)) {
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
                if (!insert_symbol_table(sym_table, sym_name, ".data", dc)) {
                    /* error */
                    errors++;
                }
            }
            /* encode data to memory return size and increase DC #7 */
            data_size = encode_data(line, data_type, &data, &dc);
            if (!data_size) {
                /* error */
            }
            continue;
        }
        /* #8 */
        if (is_extern(line)) {
            if (extract_symbol(line, sym_name, ' ')) {
                if (!insert_symbol_table(sym_table, sym_name, ".external", 0)) {
                    /* error */
                    errors++;
                }
            }
            continue;
        }

        if (is_entry(line)) {
            if (extract_symbol(line, sym_name, ' ')) {
                if (!add_symbol(entries_list, sym_name, ic + IC_OFFSET)) {
                    /* error */
                    errors++;
                }
            }
            continue;
        }

        /* construct the instruction and return the length of it */

        curr_error_id = build_command(line, &command);
        if (curr_error_id != ERROR_ID_0) {
            // change fake_line to actual line number
            add_error_to_file(curr_file, curr_error_id, fake_line, FIRST_STAGE);
            continue;
        }
        if (symbol) {
            if (!insert_symbol_table(sym_table, sym_name, ".code", ic + IC_OFFSET)) {
                /* error */
                errors++;
            }
        }
        add_command(&code, command, &ic);
    }

    if (errors > 0) {
        return 0;
    }
    update_data_symbols(sym_table, ic + IC_OFFSET);
    return second_stage_process(curr_file, data, code, sym_table, entries_list, ic, dc);
}
