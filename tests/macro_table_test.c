#include "../include/macro_table.h"
#include "../include/command.h"
#include "../include/code_container.h"
#include "../include/symbol_table.h"
#include <stdio.h>


void printBinary(unsigned short num) {
    int i;
    for (i = sizeof(num) * 8 - 2; i >= 0; i--) {
        printf("%d", (num & (1u << i)) ? 1 : 0);
    }
    printf("\n");
}


int main() {
    cmd_struct *cmd;
    code_cont *code = create_container();
    MacroTable *table = create_table();
    SymTable *sym_table;
    int ic = 0;
    char bla[] = "jmp  LOOP  ";
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

    cmd = build_command(bla);
    printf("%s\n", cmd->label);
    printf("%s\n", cmd->src);
    printf("%s\n", cmd->dst);
    printf("%d\n", cmd->src_method);
    printf("%d\n", cmd->dst_method);
    printf("%d\n", cmd->length);
    add_command(&code, cmd, &ic);
    printBinary(code->bin_rep);
    printBinary((code + 1)->bin_rep);
    printf("%s\n", (code + 1)->label);


    sym_table = create_symtable();
    insert_symbol_table(sym_table, "sym1", ".data", 100);
    insert_symbol_table(sym_table, "sym2", ".code", 100);
    insert_symbol_table(sym_table, "sym3", ".data", 105);

    update_data_symbols(sym_table, 100);
    printf("sym1: %d\n", find_sym_value(sym_table, "sym1"));
    printf("sym2: %d\n", find_sym_value(sym_table, "sym2"));
    printf("sym3: %d\n", find_sym_value(sym_table, "sym3"));

    return 0;
}
