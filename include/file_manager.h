#ifndef OPENU_PROJECT_FILE_H
#define OPENU_PROJECT_FILE_H

#define INITIAL_ERROR_SIZE 10

#include <malloc.h>
#include <stdio.h>
#include "../include/consts.h"
#include "../include/utils.h"

typedef enum STAGE_ERROR {
    UNASSIGNED,
    PRE_STAGE,
    FIRST_STAGE,
    SECOND_STAGE
} STAGE_ERROR;

typedef struct Error {
    int error_id;
    int error_line;
    STAGE_ERROR stage_error;
} Error;

typedef enum ERROR_IDS {
    ERROR_ID_0 = 0,
    ERROR_ID_1 = 1,
    ERROR_ID_2 = 2,
    ERROR_ID_3 = 3,
    ERROR_ID_4 = 4,

    ERROR_ID_9 = 9,

    ERROR_ID_11 = 11,
    ERROR_ID_12 = 12,
    ERROR_ID_13 = 13,
    ERROR_ID_14 = 14,
    ERROR_ID_15 = 15,
    ERROR_ID_16 = 16,
    ERROR_ID_17 = 17,
    ERROR_ID_18 = 18,
    ERROR_ID_19 = 19,
    ERROR_ID_20 = 20,
    ERROR_ID_21 = 21,
    ERROR_ID_22 = 22,
    ERROR_ID_23 = 23,
    ERROR_ID_24 = 24,
    ERROR_ID_25 = 25,
    ERROR_ID_26 = 26,
    ERROR_ID_27 = 27,
    ERROR_ID_28 = 28,
    ERROR_ID_29 = 29,
    ERROR_ID_30 = 30,
    ERROR_ID_31 = 31,
    ERROR_ID_32 = 32,
    ERROR_ID_33 = 33,
    ERROR_ID_34 = 34
} ERROR_IDS;

typedef struct file_struct {
    char *filename;
    Error *errors;
    int errors_count;
    int errors_size;
} file_struct;

/**
 * @brief Initializes a file structure with the given filename.
 *
 * This function sets up a file structure, allocating memory for the error array and initializing
 * the error count and size. If memory allocation fails, the program handles the error appropriately.
 *
 * @param file: A pointer to the file structure to be initialized.
 * @param filename: The name of the file to be associated with the file structure.
 */
void create_file(file_struct *file, char *filename);

/**
 * @brief Adds an error to the file's error list.
 *
 * This function records an error in the file structure's error list, including the error ID, the line
 * where the error occurred, and the stage of the assembly process in which the error was found.
 * If the error array is full, it is enlarged to accommodate more errors.
 *
 * @param file: A pointer to the file structure where the error will be recorded.
 * @param error_id: The ID of the error being recorded.
 * @param error_line: The line number where the error occurred.
 * @param stage_error: The stage of the assembly process where the error occurred.
 */
void add_error_to_file(file_struct *file, int error_id, int error_line, STAGE_ERROR stage_error);

/**
 * @brief Enlarges the error array in the file structure.
 *
 * This function doubles the size of the error array in the file structure to accommodate additional errors.
 * If memory allocation fails, the program handles the error appropriately.
 *
 * @param file: A pointer to the file structure whose error array will be enlarged.
 */
void enlarge_errors_arr(file_struct *file);

/**
 * @brief Prints the list of errors found in the file.
 *
 * This function outputs the list of errors recorded in the file structure to the standard error stream.
 * It includes details such as the error description, the line where the error occurred, and the stage
 * of the assembly process where the error was found.
 *
 * @param file: A pointer to the file structure containing the errors to be printed.
 */
void print_errors(file_struct *file);

/**
 * @brief Handles dynamic memory allocation errors.
 *
 * This function prints an error message related to memory allocation failure and exits the program.
 */
void handle_dynamic_alloc_error();

/**
 * @brief Frees the memory allocated for an array of file structures.
 *
 * This function releases all memory associated with an array of file structures, including the memory
 * allocated for their error arrays.
 *
 * @param files: A pointer to the array of file structures to be freed.
 * @param num_files: The number of file structures in the array.
 */
void free_files(file_struct *files, int num_files);

#endif

