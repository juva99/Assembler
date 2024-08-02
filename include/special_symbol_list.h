

#ifndef SPECIAL_SYMBOL_LIST_H
#define SPECIAL_SYMBOL_LIST_H

/* sumboltype is quite unnecessasry */
typedef struct Entry {
    char *label;
    char *symbol_type;
    int ic;
} SpecialSym;

typedef struct Node {
    SpecialSym *data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} SpecialSymList;

void create_spec_symbol_list(SpecialSymList *list);

int insert_spec_symbol(SpecialSymList *list, char *label, char *symbol_type, int ic);

int free_spec_symbol_list(SpecialSymList *list);

#endif //SPECIAL_SYMBOL_LIST_H
