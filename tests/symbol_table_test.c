#include "../include/symbol_table.h"
#include <stdio.h>


// Function prototypes for testing
void test_create_symtable();

void test_insert_symbol_table();

void test_find_sym_value();

void test_free_table();

void test_enlarge_table();

int main() {
    test_create_symtable();
    test_insert_symbol_table();
    test_find_sym_value();
    test_free_table();
    test_enlarge_table();
    return 0;
}

// Test creating a symbol table
void test_create_symtable() {
    SymTable *table = create_symtable();
    if (table && table->size == INITIAL_SIZE && table->count == 0) {
        printf("test_create_symtable PASSED\n");
    } else {
        printf("test_create_symtable FAILED\n");
    }
    free_table(table);
}

// Test inserting into the symbol table
void test_insert_symbol_table() {
    SymTable *table = create_symtable();
    if (!table) {
        printf("test_insert_symbol_table FAILED (table creation)\n");
        return;
    }

    int result1 = insert_symbol_table(table, "symbol1", "type1", 100);
    int result2 = insert_symbol_table(table, "symbol2", "type2", 200);
    int result3 = insert_symbol_table(table, "symbol1", "type1", 300); // Duplicate key

    if (result1 == 1 && result2 == 1 && result3 == 0 && table->count == 2) {
        printf("test_insert_symbol_table PASSED\n");
    } else {
        printf("test_insert_symbol_table FAILED\n");
    }

    free_table(table);
}

// Test finding a symbol's value
void test_find_sym_value() {
    SymTable *table = create_symtable();
    if (!table) {
        printf("test_find_sym_value FAILED (table creation)\n");
        return;
    }

    insert_symbol_table(table, "symbol1", "type1", 100);
    insert_symbol_table(table, "symbol2", "type2", 200);

    int value1 = find_sym_value(table, "symbol1");
    int value2 = find_sym_value(table, "symbol2");
    int value3 = find_sym_value(table, "symbol3"); // Non-existent key

    if (value1 == 100 && value2 == 200 && value3 == -1) {
        printf("test_find_sym_value PASSED\n");
    } else {
        printf("test_find_sym_value FAILED\n");
    }

    free_table(table);
}

// Test freeing the symbol table
void test_free_table() {
    SymTable *table = create_symtable();
    if (!table) {
        printf("test_free_table FAILED (table creation)\n");
        return;
    }

    insert_symbol_table(table, "symbol1", "type1", 100);
    insert_symbol_table(table, "symbol2", "type2", 200);

    free_table(table);
    // If there are no memory leaks and the program runs without errors, we can assume it passed.
    printf("test_free_table PASSED (manual check for memory leaks needed)\n");
}

// Test enlarging the table
void test_enlarge_table() {
    SymTable *table = create_symtable();
    if (!table) {
        printf("test_enlarge_table FAILED (table creation)\n");
        return;
    }

    char key[20];
    char type[20];
    int value = 100;
    int result;
    int i;
    for (i = 0; i < 15; ++i) {
        snprintf(key, sizeof(key), "symbol%d", i);
        snprintf(type, sizeof(type), "type%d", i);
        result = insert_symbol_table(table, key, type, value + i);
        if (result == 0) {
            printf("test_enlarge_table FAILED (insertion failed)\n");
            free_table(table);
            return;
        }
    }

    // Check if the table has been enlarged and all entries are present
    int all_found = 1;
    for (i = 0; i < 15; ++i) {
        snprintf(key, sizeof(key), "symbol%d", i);
        if (find_sym_value(table, key) == -1) {
            all_found = 0;
            break;
        }
    }

    if (table->size > INITIAL_SIZE && all_found && table->count == 15) {
        printf("test_enlarge_table PASSED\n");
    } else {
        printf("test_enlarge_table FAILED\n");
    }

    free_table(table);
}
