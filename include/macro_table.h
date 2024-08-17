#ifndef OPENU_PROJECT_MACRO_TABLE_H
#define OPENU_PROJECT_MACRO_TABLE_H

#include "../include/utils.h"
#include "../include/file_manager.h"

#define INITIAL_SIZE 10
#define LOAD_FACTOR 0.75

typedef struct Entry {
    char *key;
    char *value;
} Macro;

typedef struct {
    Macro **table;
    int size;
    int count;
} MacroTable;


/**
 * @brief Generates a hash value for a given key, used for indexing in the macro table.
 *
 * This function generates a hash value for the given key by iterating through each character of the key,
 * multiplying the accumulated hash value by 37, and adding the character's ASCII value. The result is
 * then modded by the table size to produce an index.
 *
 * @param key: The key to be hashed. It should be a null-terminated C string.
 * @param size: The size of the hash table.
 * @return Returns the computed hash value modded by the table size.
 */
unsigned int hash(const char *key, int size);

/**
 * @brief Creates and initializes a new macro table.
 *
 * This function allocates memory for a new macro table, initializes its size and count,
 * and allocates memory for the macro pointer array. If memory allocation fails, the program
 * handles the error appropriately.
 *
 * @return Returns a pointer to the newly created macro table.
 */
MacroTable *create_table();

/**
 * @brief Frees the memory allocated for a macro entry.
 *
 * This function releases the memory associated with a macro entry, including its key, value,
 * and the macro structure itself.
 *
 * @param entry: A pointer to the macro entry to be freed.
 */
void free_entry(Macro *entry);

/**
 * @brief Frees the memory allocated for the macro table and its entries.
 *
 * This function releases all the memory associated with the macro table, including each entry in the table
 * and the table structure itself.
 *
 * @param table: A pointer to the macro table to be freed.
 */
void free_table(MacroTable *table);

/**
 * @brief Resizes the macro table to accommodate more entries.
 *
 * This function doubles the size of the macro table and rehashes all existing entries to their new positions
 * in the enlarged table. If memory allocation fails, the program handles the error appropriately.
 *
 * @param table: A pointer to the macro table to be resized.
 */
void resize_table(MacroTable *table);

/**
 * @brief Inserts a new macro into the macro table.
 *
 * This function inserts a new macro with the specified key and value into the macro table.
 * If the load factor of the table exceeds the predefined threshold, the table is resized before insertion.
 * The function returns an error code if the key already exists in the table.
 *
 * @param table: A pointer to the macro table.
 * @param key: The key of the macro to be inserted. It should be a null-terminated C string.
 * @param value: The value of the macro to be inserted. It should be a null-terminated C string.
 * @return Returns 0 if the macro is successfully inserted, or an error code if the key already exists.
 */
int insert(MacroTable *table, const char *key, const char *value);

/**
 * @brief Searches for a macro in the table by its key.
 *
 * This function searches the macro table for an entry with the specified key and returns its associated value.
 * If the key is not found, the function returns NULL.
 *
 * @param table: A pointer to the macro table.
 * @param key: The key of the macro to be found. It should be a null-terminated C string.
 * @return Returns the value associated with the key if found, otherwise returns NULL.
 */
char *search(MacroTable *table, const char *key);

/**
 * @brief Checks if a key exists in the macro table.
 *
 * This function checks if a key is a member of the macro table. It returns 1 if the key exists,
 * otherwise it returns 0.
 *
 * @param table: A pointer to the macro table.
 * @param key: The key to be checked. It should be a null-terminated C string.
 * @return Returns 1 if the key exists in the table, otherwise returns 0.
 */
int is_member(MacroTable *table, const char *key);

#endif
