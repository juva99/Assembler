#ifndef OPENU_PROJECT_MACRO_TABLE_H
#define OPENU_PROJECT_MACRO_TABLE_H

#include "../include/utils.h"

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

MacroTable *create_table();

void free_table(MacroTable *table);

int insert(MacroTable *table, const char *key, const char *value);

char *search(MacroTable *table, const char *key);

int is_member(MacroTable *table, const char *key);

#endif
