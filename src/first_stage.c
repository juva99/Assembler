#include "../include/command.h"
#include "../include/first_stage.h"

int first_stage_process(char *filename) {
    int ic, dc, symbol, data_size, instr_len, opcode, errors;
    char *line;
    DataType data_type;
    char sym_name[MAX_LABEL_LENGTH + 1];
    code_cont *data, *code;
    cmd_struct *command;

    SymTable *sym_table; /* hash table to store symbols */

    /* initialize data storage */
    sym_table = create_symtable();
    data = create_container();
    code = create_container();

    FILE *file;
    ic = 0;
    dc = 0;
    errors = 0;
    while (fgets(line, sizeof(line), file)) {
        symbol = 0;
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
                if (!insert_symbol_table(sym_table, sym_name, ".external", NULL)) {
                    /* error */
                    errors++;
                }
            }
            continue;
        }

        if (is_entry(line)) {
            if (extract_symbol(line, sym_name, ' ')) {
                if (!insert_symbol_table(sym_table, sym_name, ".code", ic + IC_OFFSET)) {
                    /* error */
                    errors++;
                }
            }
            continue;
        }

        /* construct the instruction and return the length of it */
        command = build_command(line);
        if (command == NULL) {
            /* error */
            errors++;
            continue;
        }
        add_command(&code, command, &ic);
    }

    if (errors > 0) {
        return 0;
    }

    update_data_symbols(sym_table, ic + IC_OFFSET);

    return 1;
}
