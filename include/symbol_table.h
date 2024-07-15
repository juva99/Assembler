#ifndef OPENU_PROJECT_SYMBOL_TABLE_H
#define OPENU_PROJECT_SYMBOL_TABLE_H

#define INITIAL_SIZE 10
#define LOAD_FACTOR 0.75

typedef struct Entry {
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

void free_symbol(SymTable *, char *);

void free_table(SymTable *table);

void enlarge_table(SymTable *table);

int insert_symbol_table(SymTable *table, char *key, char *type, int value);

int find_sym_value(SymTable *table, char *key);

#endif //OPENU_PROJECT_SYMBOL_TABLE_H
