#include "../include/second_stage.h"

#include <consts.h>
#include <stdio.h>
#include <utils.h>

int second_stage_process(char *filename, code_cont *data, code_cont *code, SymTable *sym_table, SpecialSymList entries,
                         int ic) {
    int i, errors;
    char line;
    char sym_name[MAX_LABEL_LENGTH + 1];
    cmd_struct *command;

    FILE *file;

    if (!handle_entries(filename, sym_table, entries)) {
        /* error */
    }

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
