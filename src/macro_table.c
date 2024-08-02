#include "../include/macro_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int hash(const char *key, int size) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }
    return value % size;
}

Macro *create_entry(const char *key, const char *value) {
    Macro *entry = (Macro *) malloc(sizeof(Macro));
    if (!entry) {
        return NULL;
    }
    entry->key = strduplic(key);
    entry->value = strduplic(value);
    return entry;
}

void free_entry(Macro *entry) {
    if (entry) {
        free(entry->key);
        free(entry->value);
        free(entry);
    }
}

MacroTable *create_table() {
    MacroTable *table = (MacroTable *) malloc(sizeof(MacroTable));
    if (!table) {
        return NULL;
    }
    table->size = INITIAL_SIZE;
    table->count = 0;
    table->table = (Macro **) calloc(table->size, sizeof(Macro *));
    if (!table->table) {
        free(table);
        return NULL;
    }
    return table;
}

void free_table(MacroTable *table) {
    int i;
    for (i = 0; i < table->size; ++i) {
        if (table->table[i]) {
            free_entry(table->table[i]);
        }
    }
    free(table->table);
    free(table);
}

void resize_table(MacroTable *table) {
    int old_size = table->size;
    table->size *= 2;
    Macro **new_table = (Macro **) calloc(table->size, sizeof(Macro *));
    int i;
    for (i = 0; i < old_size; ++i) {
        if (table->table[i]) {
            unsigned int index = hash(table->table[i]->key, table->size);
            while (new_table[index]) {
                index = (index + 1) % table->size;
            }
            new_table[index] = table->table[i];
        }
    }
    free(table->table);
    table->table = new_table;
}

int insert(MacroTable *table, const char *key, const char *value) {
    if ((float) table->count / table->size > LOAD_FACTOR) {
        resize_table(table);
    }

    unsigned int index = hash(key, table->size);

    while (table->table[index]) {
        if (strcmp(table->table[index]->key, key) == 0) {
            /* return 0 if key already exists*/
            return 0;
        }
        index = (index + 1) % table->size;
    }

    table->table[index] = create_entry(key, value);
    if (!table->table[index]) {
        /* return 0 if memory alloc failed */
        return 0;
    }
    table->count++;
    return 1;
}

char *search(MacroTable *table, const char *key) {
    unsigned int index = hash(key, table->size);
    while (table->table[index]) {
        if (strcmp(table->table[index]->key, key) == 0) {
            return table->table[index]->value;
        }
        index = (index + 1) % table->size;
    }
    return NULL;
}

int is_member(MacroTable *table, const char *key) {
    unsigned int index = hash(key, table->size);
    while (table->table[index]) {
        if (strcmp(table->table[index]->key, key) == 0) {
            return 1;
        }
        index = (index + 1) % table->size;
    }
    return 0;
}