#include "../include/second_stage.h"


int second_stage_process(code_cont *data, code_cont *code, SymTable *sym_table, SymbolList *entries, int ic, int dc) {
    int i, errors;
    Symbol *symbol;
    SymbolList *externals;

    FILE *file;

    /* check entries */

    for (i = 0; i < ic; ++i) {
        if ((code + i)->bin_rep == 0) {
            if ((code + i)->label != NULL && find_sym_value(sym_table, (code + i)->label) != -1) {
                /* check if extern or data*/
            } else {
                /*error*/
            }
        }
    }

    /* merge code and data */

    /* save binary file */
}
