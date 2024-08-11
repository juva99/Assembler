#include "../include/second_stage.h"


int second_stage_process(file_struct *curr_file, code_cont *data, code_cont *code, SymTable *sym_table,
                         SymbolList *entries, int ic, int dc) {
    int i, error_id;
    Symbol *symbol;
    SymbolList *externals;
    externals = create_symbol_list();


    validate_entries(curr_file, sym_table, entries);

    for (i = 0; i < ic; ++i) {
        if ((code + i)->bin_rep == 0) {
            if ((code + i)->label != NULL && find_sym_value(sym_table, (code + i)->label) != -1) {
                /* update line based on stored symbol */
                symbol = get_symbol(sym_table, (code + i)->label);
                update_line((code + i), symbol);

                /* if symbol is external add it to ext list */
                if (strcmp(symbol->instr_type, ".external") == 0) {
                    add_symbol(externals, symbol->key, i + IC_OFFSET);
                }
            } else {
                /* unreachable code */
                continue;
            }
        }
    }

    /* save binary file */
    save_symbol_list(curr_file->filename, ENTRY, entries);
    save_symbol_list(curr_file->filename, EXTERN, externals);
    save_object_file(curr_file->filename, code, data, ic, dc);
    /* free memory */
    free_container(code, ic);
    free_container(data, dc);
    free_symtable(sym_table);
    free_symbol_list(entries);
    free_symbol_list(externals);

    return 1;
}
