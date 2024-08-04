#include "../include/special_symbol_list.h"

void create_spec_symbol_list(SpecialSymList *list) {
    list->head = NULL;
}

int insert_spec_symbol(SpecialSymList *list, char *label, int value) {
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
    newNode->data->value = value;
    newNode->next = list->head;
    list->head = newNode;

    return 1;
}

int free_spec_symbol_list(SpecialSymList *list) {
    Node *current;

    while (list->head != NULL) {
        current = list->head;
        list->head = list->head->next;
        free(current->data->label);
        free(current->data);
        free(current);
    }

    return 1;
}

void print_spec_symbol_list(SpecialSymList *list) {
    Node *current_node;

    current_node = list->head;
    while (current_node != NULL) {
        printf(current_node->data->label);
        printf("\n %d \n", current_node->data->value);

        current_node = current_node->next;
    }
}

