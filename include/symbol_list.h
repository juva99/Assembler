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
} SymbolList;

SymbolList *create_symbol_list();

int add_symbol(SymbolList *list, char *label, int value);

int free_symbol_list(SymbolList *list);

void print_symbol_list(SymbolList *list);

int validate_entries(SymTable *sym_table, SymbolList *entries);

int save_symbol_list(char *filename, ListType list_type, SymbolList *list);

#endif //SPECIAL_SYMBOL_LIST_H
