#include "../include/special_symbol_list.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <string.h>

void create_spec_symbol_list(SpecialSymList *list) {
    list->head = NULL;
}

int insert_spec_symbol(SpecialSymList *list, char *label, char *symbol_type, int ic) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (!newNode) {
        /* error */
        return 0;
    }

    newNode->data = (SpecialSym *) malloc(sizeof(SpecialSym));
    if (!newNode->data) {
        /* error */
        free(newNode);
        return 0;
    }

    newNode->data->label = strduplic(label);
    newNode->data->symbol_type = strduplic(symbol_type);
    newNode->data->ic = ic;
    newNode->next = list->head;
    list->head = newNode;

    return 1;
}
