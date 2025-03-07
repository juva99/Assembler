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
        handle_dynamic_alloc_error();
    }

    table->size = INITIAL_SIZE;
    table->count = 0;
    table->table = (Symbol **) calloc(table->size, sizeof(Symbol *));
    if (!table->table) {
        handle_dynamic_alloc_error();
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
    unsigned int index;
    Symbol **new_table;

    old_size = table->size;
    table->size *= 2;
    new_table = (Symbol **) calloc(table->size, sizeof(Symbol *));
    if (!new_table) {
        handle_dynamic_alloc_error();
    }

    for (i = 0; i < old_size; ++i) {
        if (table->table[i]) {
            index = hash_sym(table->table[i]->key, table->size);
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
    unsigned int i;
    Symbol *newSymbol;
    if ((float) table->count / table->size > LOAD_FACTOR) {
        enlarge_table(table);
    }

    i = hash_sym(key, table->size);
    while (table->table[i]) {
        if (strcmp(table->table[i]->key, key) == 0) {
            /* error -  symbol already exists */
            return ERROR_ID_26;
        }
        /* Move to the next slot */
        i = (i + 1) % table->size;
    }

    newSymbol = (Symbol *) malloc(sizeof(Symbol));
    if (!newSymbol) {
        handle_dynamic_alloc_error();
    }
    newSymbol->key = strduplic(key);
    newSymbol->instr_type = strduplic(type);
    newSymbol->value = value;
    table->table[i] = newSymbol;
    table->count++;

    return ERROR_ID_0;
}

int find_sym_value(SymTable *table, char *key) {
    Symbol *sym;
    sym = get_symbol(table, key);
    if (sym == NULL)
        return -1;
    return sym->value;
}

void update_data_symbols(SymTable *table, int ic) {
    int i;
    Symbol *temp;
    for (i = 0; i < table->size; i++) {
        if (table->table[i] != NULL) {
            temp = table->table[i];
            if (strcmp(temp->instr_type, ".data") == 0) {
                temp->value += ic;
            }
        }
    }
}

Symbol *get_symbol(SymTable *table, char *key) {
    unsigned int index;

    index = hash_sym(key, table->size);
    while (table->table[index]) {
        if (strcmp(table->table[index]->key, key) == 0) {
            return (Symbol *) table->table[index];
        }
        index = (index + 1) % table->size;
    }
    return NULL;
}
