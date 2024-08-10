#include "../include/code_container.h"

#include <file.h>

void write_data(code_cont **container, unsigned short data, int *counter) {
    int success;

    expend_memory(container, *counter);
    (*container + *counter)->bin_rep = data;
    (*counter)++;
}

void add_data(code_cont **data, unsigned short val, int *dc) {
    write_data(data, val, dc);
}

void write_data_label(code_cont **container, unsigned short data, int *counter, char *label) {
    write_data(container, data, counter)
            (*container + *counter - 1)->label = strduplic(label);
}

void expend_memory(code_cont **container, int counter) {
    code_cont *temp;

    temp = realloc(*container, (counter + 1) * sizeof(code_cont));
    if (temp == NULL) {
        handle_dynamic_alloc_error();
    }
    *container = temp;
}

code_cont *create_container() {
    code_cont *temp;
    temp = malloc(sizeof(code_cont));
    if (temp == NULL) {
        handle_dynamic_alloc_error();
    }
    return temp;
}

void add_command(code_cont **code, cmd_struct *cmd, int *ic) {
    unsigned short command = 0;
    unsigned short src_command = 0;
    unsigned short dst_command = 0;

    /* add command opcode */
    command = (cmd->opcode << OPCODE_OFFSET);
    /* add source address method */
    if (cmd->src_method >= 0) {
        command |= 1u << (SRC_OFFSET + cmd->src_method);
        src_command = create_method_line(cmd, cmd->src_method, cmd->src, 1);
    }
    /* add dest address method */
    if (cmd->dst_method >= 0) {
        command |= 1u << (DST_OFFSET + cmd->dst_method);
        dst_command = create_method_line(cmd, cmd->dst_method, cmd->dst, 0);
    }
    /* turn ABSOLUTE flag */
    command |= 1U << ABSOLUTE;
    /* write command */
    write_data(code, command, ic);

    /* if both methods reg merge them */
    if (src_command && dst_command && cmd->length == 2) {
        write_data(code, src_command | dst_command, ic);
        return;
    }
    /* handle source command */
    if (src_command) {
        write_data(code, src_command, ic);
    } else if (cmd->src_method == 1) {
        write_data_label(code, src_command, ic, cmd->src);
    }
    /* handle dest command */
    if (dst_command) {
        write_data(code, dst_command, ic);
    } else if (cmd->dst_method == 1) {
        write_data_label(code, dst_command, ic, cmd->dst);
    }
}

unsigned short create_method_line(cmd_struct *cmd, int method, char *value, int is_src) {
    int reg_num, offset;
    unsigned short method_line = 0;
    int is_negative = 1;


    switch (method) {
        case 0: {
            method_line = 1U << ABSOLUTE;
            value++;
            if (*value == '-') {
                is_negative = -1;
                value++;
            }
            method_line |= ((atoi(value) * is_negative) << DATA_OFFSET);
            break;
        }
        case 1: {
            break;
        }
        case 2:
            value++;
        case 3: {
            method_line = 1U << ABSOLUTE;
            reg_num = what_regs(value);
            offset = REG_DST_OFFSET;
            if (is_src) {
                offset = REG_SRC_OFFSET;
            }
            method_line |= reg_num << offset;
            break;
        }
        default: {
            /* unreachable code */
            break;
        }
    }
    return method_line;
}

int update_line(code_cont *code, Symbol *symbol) {
    ARE line_are;
    unsigned short new_val = 0;

    /* set ARE type based on instruction type */
    if (strcmp(symbol->instr_type, ".data") == 0 || strcmp(symbol->instr_type, ".code") == 0)
        line_are = RELOCATABLE;
    else if (strcmp(symbol->instr_type, ".external") == 0)
        line_are = EXTERNAL;
    else {
        /* unreachable code */
        return 0;
    }

    /* creating new line */
    new_val |= 1U << line_are;
    new_val |= symbol->value << DATA_OFFSET;
    code->bin_rep = new_val;
    return 1;
}
