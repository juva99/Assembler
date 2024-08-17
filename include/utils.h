#ifndef OPENU_PROJECT_UTILS_H
#define OPENU_PROJECT_UTILS_H

#include "../include/consts.h"
#include "../include/symbol_table.h"
#include "../include/code_container.h"
#include <string.h>
#include <ctype.h>

typedef enum {
 NOT_DATA,
 DATA,
 STRING
} DataType;

typedef enum {
 ENTRY,
 EXTERN
} ListType;


/**
 * @brief Extracts the next substring from a source string based on a delimiter, with optional space removal.
 *
 * This function extracts the next substring from the source string (`src`) up to a specified delimiter (`delimiter`).
 * The extracted substring is stored in `next`. If `remove_spaces` is non-zero, leading and trailing spaces are removed
 * from both the source string and the extracted substring. After extraction, the remaining part of the source string is
 * moved to the beginning of `src`.
 *
 * @param src: The source string to extract from. It should be a null-terminated C string.
 * @param next: The buffer where the extracted substring will be stored. It should be large enough to hold the substring.
 * @param delimiter: The character that delimits the substrings in `src`.
 * @param remove_spaces: If non-zero, leading and trailing spaces are removed from both `src` and `next`.
 * @return Returns 1 if a substring was found and extracted, otherwise returns 0.
 *
 * @note The function does not check for NULL pointers; ensure that `src` and `next` are valid pointers.
 * @note If the delimiter is not found, the function will extract up to the end of the string or newline.
 * @note This function modifies the `src` string by shifting the remaining content to the beginning.
 */
int extract_next_full(char *src, char *next, char delimiter, int remove_spaces);

/**
 * @brief Extracts the next substring from a source string based on a delimiter, with spaces removed.
 *
 * This function is a simplified version of `extract_next_full` where spaces are automatically removed
 * from both the source string and the extracted substring. The extracted substring is stored in `next`,
 * and the remaining part of the source string is moved to the beginning of `src`.
 *
 * @param src: The source string to extract from. It should be a null-terminated C string.
 * @param next: The buffer where the extracted substring will be stored. It should be large enough to hold the substring.
 * @param delimiter: The character that delimits the substrings in `src`.
 * @return Returns 1 if a substring was found and extracted, otherwise returns 0.
 *
 * @note The function does not check for NULL pointers; ensure that `src` and `next` are valid pointers.
 * @note This function modifies the `src` string by shifting the remaining content to the beginning.
 */
int extract_next(char *src, char *next, char delimiter);

/**
 * @brief Validates if a string contains only alphanumeric characters.
 *
 * This function checks each character in the given string (`str`) to determine if it is either
 * an alphabetic character (A-Z, a-z) or a numeric digit (0-9). If all characters are alphanumeric,
 * the function returns 1, indicating that the string is valid. If any character is not alphanumeric,
 * or if the string is `NULL`, the function returns 0.
 *
 * @param str: The string to be validated. It should be a null-terminated C string.
 * @return Returns 1 if the string contains only alphanumeric characters and is not `NULL`,
 * otherwise returns 0.
 *
 * @note The function checks for `NULL` pointers. If `str` is `NULL`, the function returns 0.
 */
int is_valid_string(const char *str);

/**
 * @brief Checks if a string starts with a specified prefix.
 *
 * This function compares the beginning of the given string (`str`) with the specified prefix (`pre`).
 * It returns 1 if `str` starts with `pre`, and 0 otherwise.
 *
 * @param str: The string to be checked.
 * @param pre: The prefix to compare against the beginning of `str`.
 * @return Returns 1 if `str` starts with `pre`, otherwise returns 0.
 */
int starts_with(const char *str, const char *pre);

/**
 * @brief Identifies the index of a given instruction token in the instructions array.
 *
 * This function searches through the global `instructions` array to find a match for the given token.
 * If the token matches an instruction, the function returns the index of that instruction in the array.
 * If the token is not found or if the token is NULL, the function returns -1.
 *
 * @param token: The string token representing an instruction. It should be a null-terminated C string.
 * @return Returns the index of the instruction in the `instructions` array if found, otherwise returns -1.
 *
 * @note The function does not check if `token` is valid beyond ensuring it is not NULL.
 * @note The `instructions` array and `INSTRUCTIONS_COUNT` must be defined globally.
 */
int what_instrct(char *token);

/**
 * @brief Identifies the index of a given register token in the registers array.
 *
 * This function searches through the global `registers` array to find a match for the given token.
 * If the token matches a register, the function returns the index of that register in the array.
 * If the token is not found or if the token is NULL, the function returns -1.
 *
 * @param token: The string token representing a register. It should be a null-terminated C string.
 * @return Returns the index of the register in the `registers` array if found, otherwise returns -1.
 *
 * @note The function does not check if `token` is valid beyond ensuring it is not NULL.
 * @note The `registers` array and `REGISTER_COUNT` must be defined globally.
 */
int what_regs(char *token);

/**
 * @brief Determines the data type of a line (e.g., DATA, STRING, or NOT_DATA).
 *
 * This function analyzes a line of code and identifies if it represents a data declaration,
 * a string declaration, or neither. The type is returned as a value of the `DataType` enum.
 *
 * @param line: The line of code to be analyzed. It should be a null-terminated C string.
 * @return Returns a value of the `DataType` enum indicating the type of data.
 */
DataType data_instruction(char *line);

/**
 * @brief Checks if a line starts with the .extern directive.
 *
 * This function determines if the provided line of code starts with the `.extern` directive.
 * If the directive is found, the function returns 1; otherwise, it returns 0.
 *
 * @param line: The line of code to be checked. It should be a null-terminated C string.
 * @return Returns 1 if the line starts with `.extern`, otherwise returns 0.
 */
int is_extern(char *line);

/**
 * @brief Checks if a line starts with the .entry directive.
 *
 * This function determines if the provided line of code starts with the `.entry` directive.
 * If the directive is found, the function returns 1; otherwise, it returns 0.
 *
 * @param line: The line of code to be checked. It should be a null-terminated C string.
 * @return Returns 1 if the line starts with `.entry`, otherwise returns 0.
 */
int is_entry(char *line);

/**
 * @brief Checks if a line is a comment.
 *
 * This function checks if the given line of code is a comment, which is determined by
 * whether it starts with a semicolon (`;`). If the line is a comment, the function returns 1,
 * otherwise it returns 0.
 *
 * @param line: The line of code to be checked. It should be a null-terminated C string.
 * @return Returns 1 if the line is a comment, otherwise returns 0.
 */
int is_comment(char *line);

/**
 * @brief Checks if a line marks the end of a macro definition.
 *
 * This function checks if the provided line of code starts with the `endmacr` keyword, indicating
 * the end of a macro definition. If the keyword is found, the function returns 1; otherwise, it returns 0.
 * Additionally, it checks for extra text after the `endmacr` keyword and returns an error code if found.
 *
 * @param line: The line of code to be checked. It should be a null-terminated C string.
 * @return Returns 1 if the line starts with `endmacr` with no extra text, otherwise returns an error code or 0.
 */
int is_endmacr(char *line);

/**
 * @brief Extracts a symbol name from a line based on a delimiter.
 *
 * This function extracts a symbol name from the beginning of a line up to a specified delimiter.
 * It checks the validity of the symbol name according to assembly language rules, including length
 * and character content. If the symbol is valid, it is stored in `sym_name` and the function returns 1.
 * If the symbol is invalid or the delimiter is not found, the function returns 0.
 *
 * @param line: The line of code containing the symbol. It should be a null-terminated C string.
 * @param sym_name: The buffer where the extracted symbol name will be stored.
 * @param delimeter: The character that delimits the symbol in the line.
 * @return Returns 1 if a valid symbol was extracted, otherwise returns 0.
 */
int extract_symbol(char *line, char *sym_name, char delimeter);

/**
 * @brief Checks the validity of a symbol name.
 *
 * This function checks if a symbol name is valid according to the rules of the assembly language.
 * It verifies the length of the symbol, ensures it starts with an alphabetic character, and contains
 * only alphanumeric characters. It also checks that the symbol is not a reserved word, such as an instruction,
 * opcode, or register name. If the symbol is valid, the function returns 1; otherwise, it returns 0.
 *
 * @param first_token: The symbol name to be checked. It should be a null-terminated C string.
 * @return Returns 1 if the symbol name is valid, otherwise returns 0.
 */
int check_symbol_name(char *first_token);

/**
 * @brief Extracts the opcode from a line of code.
 *
 * This function extracts the opcode from the beginning of a line of code and returns its corresponding
 * numerical value. If the opcode is not recognized, the function returns a negative value.
 *
 * @param line: The line of code containing the opcode. It should be a null-terminated C string.
 * @return Returns the numerical value of the opcode if recognized, otherwise returns a negative value.
 */
int extract_opcode(char *line);

/**
 * @brief Encodes a string into machine code and stores it in the data segment.
 *
 * This function encodes a string from the provided line into machine code, storing each character
 * as an unsigned short in the `data` array. The string is null-terminated in memory. The function
 * returns an error code if any issues occur during encoding.
 *
 * @param line: The line containing the string to be encoded. It should be a null-terminated C string.
 * @param data: A pointer to the data segment where the encoded string will be stored.
 * @param dc: A pointer to the data counter.
 * @param n_line: The line number in the source file, used for error reporting.
 * @return Returns an error code if an issue occurs during encoding, otherwise returns 0.
 */
int encode_string(char *line, code_cont **data, int *dc, int n_line);

/**
 * @brief Encodes data based on its type and stores it in the data segment.
 *
 * This function encodes either numeric data or a string based on the `data_type` parameter.
 * The encoded data is stored in the `data` array, and the data counter (`dc`) is updated.
 * The function returns an error code if any issues occur during encoding.
 *
 * @param line: The line containing the data to be encoded. It should be a null-terminated C string.
 * @param data_type: The type of data to be encoded (e.g., DATA or STRING).
 * @param data: A pointer to the data segment where the encoded data will be stored.
 * @param dc: A pointer to the data counter.
 * @param n_line: The line number in the source file, used for error reporting.
 * @return Returns an error code if an issue occurs during encoding, otherwise returns 0.
 */
int encode_data(char *line, DataType data_type, code_cont **data, int *dc, int n_line);

/**
 * @brief Encodes numeric data into machine code and stores it in the data segment.
 *
 * This function encodes a series of numeric values from the provided line into machine code,
 * storing each value as an unsigned short in the `data` array. The function checks the validity
 * of each number and returns an error code if any issues occur during encoding.
 *
 * @param line: The line containing the numeric data to be encoded. It should be a null-terminated C string.
 * @param data: A pointer to the data segment where the encoded data will be stored.
 * @param dc: A pointer to the data counter.
 * @param n_line: The line number in the source file, used for error reporting.
 * @return Returns an error code if an issue occurs during encoding, otherwise returns 0.
 */
int encode_numeric_data(char *line, code_cont **data, int *dc, int n_line);

/**
 * @brief Converts an integer to an unsigned short value.
 *
 * This function converts a given integer to an unsigned short, retaining only the lower 15 bits
 * of the number. This is used to encode data within the 15-bit limits of the assembly language's
 * machine code format.
 *
 * @param dec_num: The integer to be converted.
 * @return Returns the corresponding unsigned short value.
 */
unsigned short conv_to_ushort(int dec_num);

/**
 * @brief Duplicates a string by allocating memory and copying the content.
 *
 * This function creates a duplicate of the given string by allocating memory for the new string
 * and copying the content from the original string. The function returns a pointer to the duplicated
 * string, or NULL if memory allocation fails.
 *
 * @param s: The string to be duplicated. It should be a null-terminated C string.
 * @return Returns a pointer to the duplicated string, or NULL if memory allocation fails.
 */
char *strduplic(const char *s);

/**
 * @brief Adds a file extension to a filename.
 *
 * This function appends a specified file extension to the given filename. The filename is duplicated
 * and resized to accommodate the extension, which is then concatenated to the end of the filename.
 * The function returns a pointer to the new filename with the added extension.
 *
 * @param filename: The original filename. It should be a null-terminated C string.
 * @param extension: The file extension to be added. It should be a null-terminated C string.
 * @return Returns a pointer to the new filename with the added extension, or NULL if memory allocation fails.
 */
char *add_file_extension(char *filename, char *extension);

/**
 * @brief Reads a numeric argument from a string.
 *
 * This function reads a numeric argument from the given string, accounting for possible negative signs.
 * It returns the corresponding integer value.
 *
 * @param arg: The string containing the numeric argument. It should be a null-terminated C string.
 * @return Returns the integer value of the numeric argument.
 */
int read_num_arg(char *arg);

/**
 * @brief Checks if a given line exceeds the maximum size expected.
 *
 * This function determines whether the provided string exceeds a specified maximum length.
 * It is useful for detecting lines that are too long in contexts where length constraints are important.
 *
 * @param line: The string representing the line to check. It should be a null-terminated C string.
 * @return Returns 1 if the line exceeds maximum line length defined by MAX_LINE_LENGTH, otherwise returns 0.
 */
int is_line_too_long(const char *line);

#endif

