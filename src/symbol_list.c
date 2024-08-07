#include "../include/symbol_list.h"

SymbolList *create_symbol_list() {
    SymbolList *list = (SymbolList *) malloc(sizeof(SymbolList));
    if (!list) {
        return NULL;
    }
    list->head = NULL;
    list->count = 0;
    return list;
}

int add_symbol(SymbolList *list, char *label, int value) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (!node) {
        /* error */
        return 0;
    }
    /* set new node values */
    node->label = strduplic(label);
    node->value = value;

    /* place node in list */
    if (list->head == NULL) {
        list->head = node;
        return 1;
    }
    node->next = list->head;
    list->head = node;
    list->count++;
    return 1;
}

int free_symbol_list(SymbolList *list) {
    Node *current;

    while (list->head != NULL) {
        current = list->head;
        list->head = list->head->next;
        free(current);
    }
    free(list);
    return 1;
}

void print_symbol_list(SymbolList *list) {
    Node *current_node;

    current_node = list->head;
    while (current_node != NULL) {
        printf(current_node->label);
        printf("\n %d \n", current_node->value);

        current_node = current_node->next;
    }
}

