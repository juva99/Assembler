#ifndef CODE_CONTAINER_H
#define CODE_CONTAINER_H


/* offsets for command structure */
#define OPCODE_OFFSET 11
#define SRC_OFFSET 7
#define DST_OFFSET 3

/* offsets for SRC and DST lines*/
#define DATA_OFFSET 3
#define REG_DST_OFFSET 3
#define REG_SRC_OFFSET 6


/* A.R.E enum offsets */
typedef enum {
    EXTERNAL = 0,
    RELOCATABLE = 1,
    ABSOLUTE = 2
} ARE;

typedef struct code_cont {
    unsigned short bin_rep;
    int code_line;
    char *label; /* not in use for data*/
} code_cont;

#include "../include/utils.h"
#include "../include/command.h"
#include "../include/symbol_table.h"

/**
 * @brief Writes a piece of data into the code or data container.
 *
 * This function writes a 15-bit piece of data into the specified container at the current counter position,
 * and increments the counter. The function also stores the line number associated with the data.
 *
 * @param container: A pointer to the code or data container where the data will be written.
 * @param data: The 15-bit data to be written.
 * @param counter: A pointer to the current position in the container, which will be incremented.
 * @param n_line: The line number associated with the data.
 */
void write_data(code_cont **container, unsigned short data, int *counter, int n_line);

/**
 * @brief Writes a piece of data with an associated label into the code container.
 *
 * This function writes a 15-bit piece of data into the code container at the current counter position,
 * assigns a label to the data, and increments the counter. The function also stores the line number
 * associated with the data.
 *
 * @param container: A pointer to the code container where the data will be written.
 * @param data: The 15-bit data to be written.
 * @param counter: A pointer to the current position in the container, which will be incremented.
 * @param label: The label associated with the data.
 * @param n_line: The line number associated with the data.
 */
void write_data_label(code_cont **container, unsigned short data, int *counter, char *label, int n_line);

/**
 * @brief Adds data to the data container.
 *
 * This function adds a piece of data to the data container by calling `write_data` and incrementing the data counter.
 *
 * @param data: A pointer to the data container.
 * @param val: The 15-bit data value to be added.
 * @param dc: A pointer to the data counter, which will be incremented.
 * @param n_line: The line number associated with the data.
 */
void add_data(code_cont **data, unsigned short val, int *dc, int n_line);

/**
 * @brief Expands the memory allocated for the code or data container.
 *
 * This function reallocates memory for the code or data container to accommodate additional entries.
 * If memory allocation fails, the program handles the error appropriately.
 *
 * @param container: A pointer to the code or data container to be expanded.
 * @param counter: The current number of entries in the container.
 */
void expend_memory(code_cont **container, int counter);

/**
 * @brief Adds a command to the code container.
 *
 * This function encodes a command into the code container, including its opcode, source, and destination operands.
 * It also handles the addressing methods and calculates the length of the command. The command is then written
 * to the code container, and the instruction counter is updated.
 *
 * @param code: A pointer to the code container.
 * @param cmd: A pointer to the command structure to be added.
 * @param ic: A pointer to the instruction counter, which will be incremented.
 * @param n_line: The line number associated with the command.
 */
void add_command(code_cont **code, cmd_struct *cmd, int *ic, int n_line);

/**
 * @brief Creates a method line for an operand based on its addressing method.
 *
 * This function encodes an operand into a 15-bit method line based on its addressing method.
 * It handles immediate values, register direct addressing, and other methods as needed.
 *
 * @param cmd: A pointer to the command structure containing the operand.
 * @param method: The addressing method of the operand.
 * @param value: The operand value as a string.
 * @param is_src: A flag indicating if the operand is the source (1) or destination (0).
 * @return Returns the 15-bit encoded method line.
 */
unsigned short create_method_line(cmd_struct *cmd, int method, char *value, int is_src);

/**
 * @brief Creates a new code container.
 *
 * This function allocates memory for a new code container and returns a pointer to it.
 * If memory allocation fails, the program handles the error appropriately.
 *
 * @return Returns a pointer to the newly created code container.
 */
code_cont *create_container();

/**
 * @brief Updates a code line with the value of a symbol.
 *
 * This function updates a code line with the value of a symbol, setting the appropriate ARE flags
 * based on the symbol's type (relocatable, external, etc.). The updated value is then stored in the
 * code line's binary representation.
 *
 * @param code: A pointer to the code line to be updated.
 * @param symbol: A pointer to the symbol whose value will be used to update the code line.
 */
void update_line(code_cont *code, Symbol *symbol);

/**
 * @brief Saves the code and data containers to an object file in octal format.
 *
 * This function writes the contents of the code and data containers to an object file, converting
 * the binary data to octal format. The object file is then saved with a specified filename.
 *
 * @param filename: The base name of the file to save the object file to.
 * @param code: A pointer to the code container.
 * @param data: A pointer to the data container.
 * @param ic: The instruction counter, representing the number of instructions in the code container.
 * @param dc: The data counter, representing the number of data entries in the data container.
 * @return Returns 1 if the file is successfully saved, or an error code if an issue occurs.
 */
int save_object_file(char *filename, code_cont *code, code_cont *data, int ic, int dc);

/**
 * @brief Converts a binary number to its octal representation.
 *
 * This function converts a 15-bit binary number to its octal representation and returns the result
 * as an unsigned integer.
 *
 * @param number: The 15-bit binary number to be converted.
 * @return Returns the octal representation of the binary number.
 */
unsigned int to_octal(unsigned short number);

/**
 * @brief Frees the memory allocated for a code or data container.
 *
 * This function releases all memory associated with a code or data container, including the memory
 * allocated for labels.
 *
 * @param container: A pointer to the code or data container to be freed.
 * @param size: The number of entries in the container.
 */
void free_container(code_cont *container, int size);

#endif
