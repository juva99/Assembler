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
 * @brief Executes the first stage of the assembly process, preparing for and triggering the second stage.
 *
 * This function performs the initial phase of the assembly process by parsing the source code, identifying
 * symbols, encoding data, and generating the initial code structure. It also checks for errors during this
 * stage and manages symbol tables and data containers. After completing its tasks, the first stage gracefully
 * transitions into the second stage of the assembly process by invoking the `second_stage_process` function.
 * The first stage not only prepares the necessary data structures for the second stage but also ensures a seamless
 * continuation of the assembly process by handling the transition in an elegant manner.
 *
 * If errors are detected during the first stage, it cleans up resources and returns an error code. Otherwise,
 * it proceeds to the second stage and returns the result from `second_stage_process`.
 *
 * @param curr_file: A pointer to the current file structure, used for error reporting and file management.
 * @return Returns the result from `second_stage_process` if the first stage completes successfully, or an
 * error code if issues are encountered during the first stage.
 */
int first_stage_process(file_struct *curr_file);

#endif
