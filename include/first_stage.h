#ifndef OPENU_PROJECT_FIRST_STAGE_H
#define OPENU_PROJECT_FIRST_STAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/symbol_table.h"
#include "../include/symbol_list.h"
#include "../include/command.h"
#include "../include/second_stage.h"
#include "../include/file_manager.h"

/**
 * @brief Executes the first stage of the assembly process.
 *
 * This function performs the first stage of the assembly process, where it parses the source code,
 * processes symbols, encodes data, and generates the initial code structure. It also checks for
 * any errors during this stage and prepares the data for the second stage of the process. If errors
 * are found, it cleans up and returns an error code.
 *
 * @param curr_file: A pointer to the current file structure, used for error reporting and file management.
 * @return Returns 0 if the process is successful, or an error code if an issue occurs.
 */
int first_stage_process(file_struct *curr_file);

#endif
