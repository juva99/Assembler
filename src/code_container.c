#include "../include/code_container.h"


int write_data(code_cont **container, unsigned short data, int *counter) {
    int success;
    if (!expend_memory(container, *counter)) {
        /* expend error */
        return 0;
    }
    (*container + *counter)->bin_rep = data;
    (*counter)++;
    return 1;
}

int add_data(code_cont **data, unsigned short val, int *dc) {
    return write_data(data, val, dc);
}

int write_data_label(code_cont **container, unsigned short data, int *counter, char *label) {
    if (!write_data(container, data, counter))
        return 0;
    (*container + *counter - 1)->label = strduplic(label);
    return 1;
}


int expend_memory(code_cont **container, int counter) {
    code_cont *temp;

    temp = realloc(*container, (counter + 1) * sizeof(code_cont));
    if (temp == NULL) {
        /*error*/
        return 0;
    }
    *container = temp;
    return 1;
}

code_cont *create_container() {
    code_cont *temp;
    temp = malloc(sizeof(code_cont));
    return temp;
}

int add_command(code_cont **code, cmd_struct *cmd, int *ic) {
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
    if (!write_data(code, command, ic))
        return 0;
    /* if both methods reg merge them */
    if (src_command && dst_command && cmd->length == 2) {
        return write_data(code, src_command | dst_command, ic);
    }
    /* handle source command */
    if (src_command) {
        if (!write_data(code, src_command, ic)) {
            return 0;
        }
    } else if (cmd->src_method == 1) {
        if (!write_data_label(code, src_command, ic, cmd->src)) {
            return 0;
        }
    }
    /* handle dest command */
    if (dst_command) {
        if (!write_data(code, dst_command, ic)) {
            return 0;
        }
    } else if (cmd->dst_method == 1) {
        if (!write_data_label(code, dst_command, ic, cmd->dst)) {
            return 0;
        }
    }
    return 1;
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
            /* invalid method */
            break;
        }
    }
    return (method_line & ~(1U << MAX_BIN_LENGTH));
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
        /* error */
        return 0;
    }

    /* creating new line */
    new_val |= 1U << line_are;
    new_val |= symbol->value << DATA_OFFSET;
    code->bin_rep = new_val;
    return 1;
}

int save_object_file(char *filename, code_cont *code, code_cont *data, int ic, int dc) {
    int i;
    char *full_filename;
    FILE *ob_file;
    full_filename = add_file_extension(filename, FINAL_FILE_EXTENSION);
    ob_file = fopen(full_filename, "w");
    if (ob_file == NULL) {
        /* error */
    }
    fprintf(ob_file, "%d %d\n", ic, dc);
    for (i = 0; i < ic; ++i) {
        fprintf(ob_file, "%04d %05u\n", i + IC_OFFSET, to_octal((code + i)->bin_rep));
    }
    for (i = ic; i < ic + dc; ++i) {
        fprintf(ob_file, "%04d %05u\n", i + IC_OFFSET, to_octal((data + i - ic)->bin_rep));
    }
    return 1;
}

unsigned int to_octal(unsigned short number) {
    unsigned int octal = 0;
    unsigned int place_value = 1;

    while (number > 0) {
        octal += (number % 8) * place_value;
        number /= 8;
        place_value *= 10;
    }

    return octal;
}

void free_container(code_cont *container, int size) {
    int i;
    for (i = 0; i < size; ++i) {
        if ((container + i)->label != NULL)
            free((container + i)->label);
    }
    free(container);
}