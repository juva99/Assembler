#include "../include/second_stage.h"


int
second_stage_process(file_struct *curr_file, code_cont *data, code_cont *code, SymTable *sym_table,
                     SymbolList *entries, int ic, int dc) {
    int i, errors;
    Symbol *symbol;
    SymbolList *externals;

    FILE *file;

    externals = create_symbol_list();

    if (!validate_entries(sym_table, entries)) {
        /* error */
    }

    for (i = 0; i < ic; ++i) {
        if ((code + i)->bin_rep == 0) {
            if ((code + i)->label != NULL && find_sym_value(sym_table, (code + i)->label) != -1) {
                /* update line based on stored symbol */
                symbol = get_symbol(sym_table, (code + i)->label);
                if (!update_line((code + i), symbol)) {
                    /* error */
                    continue;
                }
                /* if symbol is external add it to ext list */
                if (strcmp(symbol->instr_type, ".external") == 0) {
                    add_symbol(externals, symbol->key, i + IC_OFFSET);
                }
            } else {
                /*error*/
                continue;
            }
        }
    }
    /* merge code and data */

    /* save binary file */
    save_symbol_list(curr_file->filename, ENTRY, entries);
    save_symbol_list(curr_file->filename, EXTERN, externals);
    save_object_file(curr_file->filename, code, data, ic, dc);
    return 1;
}
