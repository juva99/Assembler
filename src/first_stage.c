#include "../include/first_stage.h"

int first_stage_process(char *filename) {
    int ic, dc, symbol, data_size, instr_len, opcode, errors;
    char *line;
    char sym_name[MAX_LABEL_LENGTH + 1];
    char opcode_name[MAX_OPCODE_LENGTH + 1];

    SymTable *sym_table; /* hash table to store symbols */

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
        if (data_instruction(line)) {
            if (symbol) {
                /* insert to data table #6 */
                if (!insert_symbol_table(sym_table, sym_name, ".data", dc)) {
                    /* error */
                    errors++;
                }
            }
            /* encode data to memory return size and increase DC #7 */
            data_size = encode_data(line);
            dc += data_size;
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

        opcode = extract_opcode(line, opcode_name);
        if (opcode < 0) {
            /* error */
            errors++;
        }
        /* construct the instruction and return the length of it */
        instr_len = calc_opcode_instr(line, opcode);
        ic += instr_len;
    }

    if (errors > 0) {
        return 0;
    }

    update_data_symbols(sym_table, ic + IC_OFFSET);

    return 1;
}
