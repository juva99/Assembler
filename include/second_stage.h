
#ifndef SECOND_STAGE_H
#define SECOND_STAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/symbol_table.h"
#include "../include/command.h"
#include "../include/code_container.h"
#include "../include/symbol_list.h"

int second_stage_process(char *filename, code_cont *data, code_cont *code, SymTable *sym_table, SymbolList *entries,
                         int ic, int dc);

#endif //SECOND_STAGE_H
