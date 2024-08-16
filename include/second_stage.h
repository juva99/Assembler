
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
#include "../include/file_manager.h"

/**
 * @brief Executes the second stage of the assembly process.
 *
 * This function performs the second stage of the assembly process, where it resolves symbols and updates
 * the code and data containers based on the symbol table. It validates the entries, updates code lines based
 * on symbol values, handles external symbols, and finally saves the binary output files. It also frees all
 * associated memory before returning.
 *
 * @param curr_file: A pointer to the current file structure, used for error reporting and file management.
 * @param data: A pointer to the data container holding the assembled data.
 * @param code: A pointer to the code container holding the assembled code.
 * @param sym_table: A pointer to the symbol table containing all symbols and their associated information.
 * @param entries: A pointer to the symbol list containing entry symbols.
 * @param ic: The instruction counter, representing the number of instructions in the code container.
 * @param dc: The data counter, representing the number of data entries in the data container.
 * @return Returns 1 after successful completion of the second stage.
 */
int second_stage_process(file_struct *curr_file, code_cont *data, code_cont *code, SymTable *sym_table,
                         SymbolList *entries, int ic, int dc);

#endif
