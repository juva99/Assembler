#ifndef OPENU_PROJECT_COMMAND_H
#define OPENU_PROJECT_COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/consts.h"

typedef struct cmd_struct {
 int opcode; /* opcode number of command */
 char *src; /* source address of command */
 char *dst; /* dest address of command */
 int src_method; /* src address method id */
 int dst_method; /* dst address method id */
 int length; /* command line length */
} cmd_struct;

typedef struct opcode {
 char *name; /* name of opcode */
 int args; /* amount of args of opcode */
 int add_methods_src[MAX_ADDRESS_METHODS]; /* valid address methods for src */
 int add_methods_dst[MAX_ADDRESS_METHODS]; /* valid address methods for dst */
} opcode;

/**
 * @brief Frees the memory allocated for a command structure.
 *
 * This function releases the memory associated with a command structure, including the memory
 * allocated for the source, and destination addresses.
 *
 * @param cmd: A pointer to the command structure to be freed.
 */
void free_command(cmd_struct *cmd);

/**
 * @brief Builds a command structure from a line of assembly code.
 *
 * This function parses a line of assembly code to construct a command structure. It extracts the
 * opcode, source, and destination addresses, and determines the addressing methods and command length.
 * If any errors are encountered during parsing, an appropriate error code is returned.
 *
 * @param line: The line of assembly code to be parsed.
 * @param command: A pointer to the pointer that will hold the newly created command structure.
 * @return Returns 0 if the command is successfully built, or an error code if an issue occurs.
 */
int build_command(char *line, cmd_struct **command);

/**
 * @brief Identifies the opcode corresponding to a given token.
 *
 * This function searches the opcode array to find the index of the given token. If the token matches an opcode,
 * the function returns its index in the opcode array. If the token is not found, the function returns -1.
 *
 * @param token: The token representing an opcode.
 * @return Returns the index of the opcode if found, otherwise returns -1.
 */
int what_opcode(char *token);

/**
 * @brief Retrieves the number of arguments required by an opcode.
 *
 * This function returns the number of arguments expected by a given opcode. If the opcode is invalid,
 * the function returns -1.
 *
 * @param opcode: The opcode index.
 * @return Returns the number of arguments expected by the opcode, or -1 if the opcode is invalid.
 */
int get_opcode_args(int opcode);

/**
 * @brief Checks if a string is a valid type 0 address (immediate addressing).
 *
 * This function checks if a given string represents a valid type 0 address, which is an immediate
 * value prefixed by '#'. The string is checked for correct format, including optional negative sign
 * and numeric value.
 *
 * @param str: The string to be checked.
 * @return Returns 1 if the string is a valid type 0 address, otherwise returns 0.
 */
int check_address_type_0(char *str);

/**
 * @brief Checks if a string is a valid type 1 address (direct addressing).
 *
 * This function checks if a given string represents a valid type 1 address, which is a symbol name.
 * The string is validated to ensure it follows the rules for symbol names.
 *
 * @param str: The string to be checked.
 * @return Returns 1 if the string is a valid type 1 address, otherwise returns 0.
 */
int check_address_type_1(char *str);

/**
 * @brief Checks if a string is a valid type 2 address (relative addressing).
 *
 * This function checks if a given string represents a valid type 2 address, which is a relative
 * address prefixed by '*'. The string is validated as a type 3 address after the '*' prefix.
 *
 * @param str: The string to be checked.
 * @return Returns 1 if the string is a valid type 2 address, otherwise returns 0.
 */
int check_address_type_2(char *str);

/**
 * @brief Checks if a string is a valid type 3 address (register direct addressing).
 *
 * This function checks if a given string represents a valid type 3 address, which is a register name.
 * The string is checked against the list of valid register names.
 *
 * @param str: The string to be checked.
 * @return Returns 1 if the string is a valid type 3 address, otherwise returns 0.
 */
int check_address_type_3(char *str);

/**
 * @brief Determines the addressing method for the source operand of a command.
 *
 * This function checks the source operand against the valid addressing methods for the given opcode
 * and returns the method index. If no valid method is found, the function returns -1.
 *
 * @param opcode: The opcode index.
 * @param src: The source operand string.
 * @return Returns the index of the valid addressing method, or -1 if no valid method is found.
 */
int get_src_add_method(int opcode, char *src);

/**
 * @brief Determines the addressing method for the destination operand of a command.
 *
 * This function checks the destination operand against the valid addressing methods for the given opcode
 * and returns the method index. If no valid method is found, the function returns -1.
 *
 * @param opcode: The opcode index.
 * @param dst: The destination operand string.
 * @return Returns the index of the valid addressing method, or -1 if no valid method is found.
 */
int get_dst_add_method(int opcode, char *dst);


#endif
