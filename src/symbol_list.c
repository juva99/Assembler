#include "../include/symbol_list.h"

#include <file_manager.h>

SymbolList *create_symbol_list() {
    SymbolList *list = (SymbolList *) malloc(sizeof(SymbolList));
    if (!list) {
        handle_dynamic_alloc_error();
    }
    list->head = NULL;
    list->count = 0;
    return list;
}

void add_symbol(SymbolList *list, char *label, int value) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (!node) {
        handle_dynamic_alloc_error();
    }
    /* set new node values */
    node->label = strduplic(label);
    node->value = value;
    node->next = NULL;

    /* place node in list */
    if (list->head == NULL) {
        list->head = node;
        return;
    }
    node->next = list->head;
    list->head = node;
    list->count++;
}

int free_symbol_list(SymbolList *list) {
    Node *current;

    while (list->head != NULL) {
        current = list->head;
        list->head = list->head->next;
        free(current->label);
        free(current);
    }
    free(list);
    return 1;
}

void print_symbol_list(SymbolList *list) {
    Node *current_node;

    current_node = list->head;
    while (current_node != NULL) {
        printf("%s: %d \n", current_node->label, current_node->value);
        current_node = current_node->next;
    }
}

int validate_entries(SymTable *sym_table, SymbolList *entries) {
    int entry_value;
    Node *curr_node;

    curr_node = entries->head;

    while (curr_node != NULL) {
        entry_value = find_sym_value(sym_table, curr_node->label);
        if (entry_value == -1) {
            /* error - entry without definition */
            return ERROR_ID_20;
        }
        curr_node->value = entry_value;
        curr_node = curr_node->next;
    }

    return ERROR_ID_0;
}


/* use the func that links filename to extensions */
int save_symbol_list(char *filename, ListType list_type, SymbolList *list) {
    char *full_filename;
    FILE *list_file;
    Node *curr_node;

    if (list->count == 0) {
        return 1;
    }

    switch (list_type) {
        case ENTRY: {
            full_filename = (char *) malloc(strlen(filename) + ENTERIES_FILE_EXTENSION_LEN + 1);
            if (full_filename == NULL) {
                handle_dynamic_alloc_error();
            }

            sprintf(full_filename, "%s%s", filename, ENTERIES_FILE_EXTENSION);
            list_file = fopen(full_filename, "w");
            if (list_file == NULL) {
                handle_dynamic_alloc_error();
            }
            break;
        }
        case EXTERN: {
            full_filename = (char *) malloc(strlen(filename) + EXTERNS_FILE_EXTENSION_LEN + 1);
            if (full_filename == NULL) {
                handle_dynamic_alloc_error();
            }

            sprintf(full_filename, "%s%s", filename, EXTERNS_FILE_EXTENSION);
            list_file = fopen(full_filename, "w");
            if (list_file == NULL) {
                handle_dynamic_alloc_error();
            }
            break;
        }
        default: {
            /* unreachable code */
            return 0;
        }
    }

    curr_node = list->head;

    while (curr_node != NULL) {
        /*add entry name and ic to file .ent */
        fprintf(list_file, "%s %d\n", curr_node->label, curr_node->value);
        curr_node = curr_node->next;
    }

    fclose(list_file);
    free(full_filename);
    return 1;
}
