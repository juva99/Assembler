#ifndef OPENU_PROJECT_SYMBOL_TABLE_H
#define OPENU_PROJECT_SYMBOL_TABLE_H


#define INITIAL_SIZE 10
#define LOAD_FACTOR 0.75

typedef struct Symbol {
    char *key;
    char *instr_type;
    int value;
} Symbol;

typedef struct {
    Symbol **table;
    int size;
    int count;
} SymTable;

#include "../include/utils.h"
#include "../include/file_manager.h"


/**
 * @brief Generates a hash value for a given key, used for indexing in the symbol table.
 *
 * This function generates a hash value for the given key by iterating through each character of the key,
 * multiplying the accumulated hash value by 37, and adding the character's ASCII value. The result is
 * then modded by the table size to produce an index.
 *
 * @param key: The key to be hashed. It should be a null-terminated C string.
 * @param size: The size of the hash table.
 * @return Returns the computed hash value modded by the table size.
 */
unsigned int hash_sym(const char *key, int size);

/**
 * @brief Creates and initializes a new symbol table.
 *
 * This function allocates memory for a new symbol table, initializes its size and count,
 * and allocates memory for the symbol pointer array. If memory allocation fails, the program
 * handles the error appropriately.
 *
 * @return Returns a pointer to the newly created symbol table.
 */
SymTable *create_symtable();

/**
 * @brief Frees the memory allocated for a symbol.
 *
 * This function releases the memory associated with a symbol, including its key, instruction type,
 * and the symbol structure itself.
 *
 * @param symbol: A pointer to the symbol to be freed.
 */
void free_symbol(Symbol *symbol);

/**
 * @brief Frees the memory allocated for the symbol table and its symbols.
 *
 * This function releases all the memory associated with the symbol table, including each symbol in the table
 * and the table structure itself.
 *
 * @param table: A pointer to the symbol table to be freed.
 */
void free_symtable(SymTable *table);

/**
 * @brief Doubles the size of the symbol table and rehashes existing symbols.
 *
 * This function resizes the symbol table to double its previous size and rehashes all existing symbols
 * to their new positions in the enlarged table. If memory allocation fails, the program handles the error appropriately.
 *
 * @param table: A pointer to the symbol table to be resized.
 */
void enlarge_table(SymTable *table);

/**
 * @brief Inserts a new symbol into the symbol table.
 *
 * This function inserts a new symbol with the specified key, type, and value into the symbol table.
 * If the load factor of the table exceeds the predefined threshold, the table is enlarged before insertion.
 * The function returns an error code if the symbol already exists in the table.
 *
 * @param table: A pointer to the symbol table.
 * @param key: The key of the symbol to be inserted. It should be a null-terminated C string.
 * @param type: The instruction type of the symbol. It should be a null-terminated C string.
 * @param value: The value associated with the symbol.
 * @return Returns 0 if the symbol is successfully inserted, or an error code if the symbol already exists.
 */
int insert_symbol_table(SymTable *table, char *key, char *type, int value);

/**
 * @brief Finds the value of a symbol in the symbol table.
 *
 * This function searches for a symbol with the specified key in the symbol table and returns its associated value.
 * If the symbol is not found, the function returns -1.
 *
 * @param table: A pointer to the symbol table.
 * @param key: The key of the symbol to be found. It should be a null-terminated C string.
 * @return Returns the value of the symbol if found, otherwise returns -1.
 */
int find_sym_value(SymTable *table, char *key);

/**
 * @brief Updates the values of all data symbols by adding the instruction counter (IC).
 *
 * This function iterates through the symbol table and adds the instruction counter (IC) to the value
 * of each symbol that is of type `.data`.
 *
 * @param table: A pointer to the symbol table.
 * @param ic: The instruction counter value to be added to each data symbol's value.
 */
void update_data_symbols(SymTable *table, int ic);

/**
 * @brief Retrieves a symbol from the symbol table by its key.
 *
 * This function searches for a symbol with the specified key in the symbol table and returns a pointer to it.
 * If the symbol is not found, the function returns NULL.
 *
 * @param table: A pointer to the symbol table.
 * @param key: The key of the symbol to be retrieved. It should be a null-terminated C string.
 * @return Returns a pointer to the symbol if found, otherwise returns NULL.
 */
Symbol *get_symbol(SymTable *table, char *key);

#endif
