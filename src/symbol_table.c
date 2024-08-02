#include "../include/symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned int hash_sym(const char *key, int size) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }
    return value % size;
}

SymTable *create_symtable() {
    SymTable *table;

    table = (SymTable *) malloc(sizeof(SymTable));
    if (!table) {
        printf("Memory allocation falid for symbol table\n");
        return NULL;
    }

    table->size = INITIAL_SIZE;
    table->count = 0;
    table->table = (Symbol **) calloc(INITIAL_SIZE, sizeof(Symbol));
    if (!table->table) {
        printf("Memory allocation falid for symbol table\n");
        free(table);
        return NULL;
    }

    return table;
}

void free_symbol(Symbol *symbol) {
    if (symbol) {
        free(symbol->key);
        free(symbol->instr_type);
        free(symbol);
    }
}

void free_symtable(SymTable *table) {
    unsigned int i;

    for (i = 0; i < table->size; i++) {
        free_symbol(table->table[i]);
    }
    free(table->table);
    free(table);
}

void enlarge_table(SymTable *table) {
    int old_size, i;

    old_size = table->size;
    table->size *= 2;
    Symbol **new_table = (Symbol **) calloc(table->size, sizeof(Symbol *));
    if (!new_table) {
        printf("Memory allocation falid for symbol table\n");
        return NULL;
    }

    for (i = 0; i < old_size; ++i) {
        if (table->table[i]) {
            unsigned int index = hash_sym(table->table[i]->key, table->size);
            while (new_table[index]) {
                index = (index + 1) % table->size;
            }
            new_table[index] = table->table[i];
        }
    }

    free(table->table);
    table->table = new_table;
}


int insert_symbol_table(SymTable *table, char *key, char *type, int value) {
    unsigned i;
    Symbol *newSymbol;
    if ((float) table->count / table->size > LOAD_FACTOR) {
        enlarge_table(table);
    }

    i = hash_sym(key, table->size);
    while (table->table[i] != NULL) {
        if (strcmp(table->table[i]->key, key) == 0) {
            /* If the key already exists - return 0 */
            return 0;
        }
        /* Move to the next slot */
        i = (i + 1) % table->size;
    }

    newSymbol = (Symbol *) malloc(sizeof(Symbol));
    if (!newSymbol) {
        printf("Memory allocation failed");
        return 0;
    }
    newSymbol->key = strduplic(key);
    newSymbol->instr_type = strduplic(type);
    newSymbol->value = value;
    table->table[i] = newSymbol;
    table->count++;

    return 1;
}

int find_sym_value(SymTable *table, char *key) {
    unsigned int index;

    index = hash_sym(key, table->size);
    while (table->table[index]) {
        if (strcmp(table->table[index]->key, key) == 0) {
            return table->table[index]->value;
        }
        index = (index + 1) % table->size;
    }

    return -1;
    /* the function can work as is_member as well - note the false answer will be -1 */
}



