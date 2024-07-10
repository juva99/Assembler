#include "../include/macro_table.h"
#include <stdio.h>

int main() {
    MacroTable *table = create_table();
    if (!table) {
        fprintf(stderr, "Failed to create table\n");
        return 1;
    }

    insert(table, "key1", "value1");
    insert(table, "key2", "value2");
    insert(table, "key3", "value3");
    insert(table, "key4", "value4");
    insert(table, "key5", "value5");
    insert(table, "key6", "value6");
    insert(table, "key7", "value7");

    printf("key1: %s\n", search(table, "key1"));
    printf("key2: %s\n", search(table, "key2"));
    printf("key3: %s\n", search(table, "key3"));
    printf("key4: %s\n", search(table, "key4"));
    printf("key5: %s\n", search(table, "key5"));
    printf("key6: %s\n", search(table, "key6"));
    printf("key7: %s\n", search(table, "key7"));


    free_table(table);
    return 0;
}
