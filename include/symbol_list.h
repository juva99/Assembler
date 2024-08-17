#ifndef SPECIAL_SYMBOL_LIST_H
#define SPECIAL_SYMBOL_LIST_H

#include "../include/utils.h"
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *label;
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int count;
    int max_len;
} SymbolList;

/**
 * @brief Creates and initializes a new symbol list.
 *
 * This function allocates memory for a new symbol list and initializes its head to NULL,
 * its count to 0, and its maximum label length to 0. If memory allocation fails, the program
 * handles the error appropriately.
 *
 * @return Returns a pointer to the newly created symbol list.
 */
SymbolList *create_symbol_list();

/**
 * @brief Adds a new symbol to the symbol list.
 *
 * This function adds a new symbol to the symbol list with the specified label and value.
 * The symbol is inserted at the head of the list, and the list's maximum label length is updated
 * if the new label is longer than the current maximum.
 *
 * @param list: A pointer to the symbol list.
 * @param label: The label of the symbol to be added. It should be a null-terminated C string.
 * @param value: The value associated with the symbol.
 */
void add_symbol(SymbolList *list, char *label, int value);

/**
 * @brief Frees the memory allocated for the symbol list and its nodes.
 *
 * This function releases all the memory associated with the symbol list, including each node in the list
 * and the list structure itself.
 *
 * @param list: A pointer to the symbol list to be freed.
 * @return Returns 1 after successfully freeing the list.
 */
int free_symbol_list(SymbolList *list);

/**
 * @brief Prints the contents of the symbol list.
 *
 * This function iterates through the symbol list and prints each symbol's label and value to the standard output.
 *
 * @param list: A pointer to the symbol list to be printed.
 */
void print_symbol_list(SymbolList *list);

/**
 * @brief Validates the entries in the symbol list against the symbol table.
 *
 * This function checks each symbol in the entries list to ensure it exists in the symbol table.
 * If a symbol is found without a corresponding definition in the symbol table, an error is added to the current file.
 * The function updates the value of each entry in the list with the value from the symbol table.
 *
 * @param curr_file: A pointer to the current file structure used for error reporting.
 * @param sym_table: A pointer to the symbol table used for validation.
 * @param entries: A pointer to the symbol list containing entries to be validated.
 */
void validate_entries(file_struct *curr_file, SymTable *sym_table, SymbolList *entries);

/**
 * @brief Saves the contents of the symbol list to a file.
 *
 * This function saves the symbols in the list to a file with the appropriate extension based on the list type (entry or extern).
 * The function creates a file with the correct extension and writes each symbol's label and value to the file.
 * If the list is empty, the function does nothing.
 *
 * @param filename: The base name of the file to save the list to. It should be a null-terminated C string.
 * @param list_type: The type of list being saved (ENTRY or EXTERN).
 * @param list: A pointer to the symbol list to be saved.
 * @return Returns 1 if the list was successfully saved, or 0 in case of an error.
 */
int save_symbol_list(char *filename, ListType list_type, SymbolList *list);

#endif
