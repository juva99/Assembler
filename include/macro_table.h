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


unsigned int hash(const char *key, int size);

MacroTable *create_table();

void free_entry(Macro *entry);

void free_table(MacroTable *table);

void resize_table(MacroTable *table);

int insert(MacroTable *table, const char *key, const char *value);

char *search(MacroTable *table, const char *key);

int is_member(MacroTable *table, const char *key);

#endif
