#include "../include/second_stage.h"


int second_stage_process(file_struct *curr_file, code_cont *data, code_cont *code, SymTable *sym_table,
                         SymbolList *entries, int ic, int dc) {
    int i;
    Symbol *symbol;
    SymbolList *externals;
    externals = create_symbol_list();

    /* check entries list is valid */
    validate_entries(curr_file, sym_table, entries);

    for (i = 0; i < ic; ++i) {
        if ((code + i)->bin_rep == 0) {
            /* check if instruction used label */
            if ((code + i)->label != NULL) {
                /* check if label exists */
                if (find_sym_value(sym_table, (code + i)->label) != -1) {
                    /* update line based on stored symbol */
                    symbol = get_symbol(sym_table, (code + i)->label);
                    update_line((code + i), symbol);

                    /* if symbol is external add it to ext list */
                    if (strcmp(symbol->instr_type, ".external") == 0) {
                        add_symbol(externals, symbol->key, i + IC_OFFSET);
                    }
                } else {
                    /* error - Symbol is not defined */
                    add_error_to_file(curr_file, ERROR_ID_33, (code + i)->code_line, SECOND_STAGE);
                }
            }
        }
    }
    /* save outputs if no errors */
    if (curr_file->errors_count == 0) {
        /* save binary file */
        save_symbol_list(curr_file->filename, ENTRY, entries);
        save_symbol_list(curr_file->filename, EXTERN, externals);
        save_object_file(curr_file->filename, code, data, ic, dc);
    }

    /* free memory */
    free_container(code, ic);
    free_container(data, dc);
    free_symtable(sym_table);
    free_symbol_list(entries);
    free_symbol_list(externals);

    return 1;
}
