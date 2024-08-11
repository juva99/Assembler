#ifndef OPENU_PROJECT_SYMBOL_TABLE_H
#define OPENU_PROJECT_SYMBOL_TABLE_H


#define INITIAL_SIZE 10
#define LOAD_FACTOR 0.75

#include "../include/utils.h"
#include "../include/file_manager.h"

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


SymTable *create_symtable();

void free_symbol(Symbol *symbol);

void free_symtable(SymTable *table);

void enlarge_table(SymTable *table);

int insert_symbol_table(SymTable *table, char *key, char *type, int value);

int find_sym_value(SymTable *table, char *key);

void update_data_symbols(SymTable *table, int ic);

Symbol *get_symbol(SymTable *table, char *key);

#endif
