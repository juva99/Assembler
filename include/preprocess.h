#ifndef OPENU_PROJECT_PREPROCESS_H
#define OPENU_PROJECT_PREPROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/macro_table.h"
#include "../include/utils.h"
#include "../include/file_manager.h"

#define INITIAL_MACRO_BUFFER 10

/**
 * @brief Preprocesses the source file to handle macros.
 *
 * This function processes the source file to handle macro definitions and expansions,
 * and writes the preprocessed content to a new file. It also checks for any errors in
 * macro handling during the preprocessing stage.
 *
 * @param curr_file: A pointer to the current file structure, used for error reporting and file management.
 * @return Returns 0 if preprocessing is successful, or an error code if an issue occurs.
 */
int preprocess(file_struct *curr_file);

/**
 * @brief Processes a single line of the source file during preprocessing.
 *
 * This function processes a single line of the source file to handle macros. If the line
 * is a macro definition, it delegates the handling to `handle_macro`. If the line contains
 * a macro invocation, it expands the macro. Otherwise, it writes the line to the final preprocessed file.
 *
 * @param line: The line of code to be processed. It should be a null-terminated C string.
 * @param file: The source file being preprocessed.
 * @param final_file: The file where the preprocessed content is written.
 * @param macros: A pointer to the macro table used to store and retrieve macro definitions.
 * @return Returns 0 if the line is processed successfully, or an error code if an issue occurs.
 */
int process_line(char line[], FILE *file, FILE *final_file, MacroTable *macros);

/**
 * @brief Checks if a line contains a macro declaration.
 *
 * This function checks whether the given line is a macro declaration, specifically
 * if it starts with the keyword "macr".
 *
 * @param line: The line of code to be checked. It should be a null-terminated C string.
 * @return Returns 1 if the line contains a macro declaration, otherwise returns 0.
 */
int is_macro(char *line);

/**
 * @brief Handles the processing of a macro declaration.
 *
 * This function processes a macro declaration by reading its content, storing it in the macro table,
 * and handling any errors that may occur during the macro's definition or end declaration.
 *
 * @param line: The line containing the macro declaration. It should be a null-terminated C string.
 * @param file: The source file being preprocessed.
 * @param macros: A pointer to the macro table used to store the macro definition.
 * @return Returns 0 if the macro is processed successfully, or an error code if an issue occurs.
 */
int handle_macro(char *line, FILE *file, MacroTable *macros);

/**
 * @brief Validates the name of a macro.
 *
 * This function checks whether the given macro name is valid. It ensures that the macro name
 * is not NULL, not an instruction, opcode, or register name, and is not "macr".
 *
 * @param mac_name: The macro name to be validated. It should be a null-terminated C string.
 * @return Returns 0 if the macro name is valid, or an error code if the name is invalid.
 */
int is_macro_name_valid(char *mac_name);

#endif
