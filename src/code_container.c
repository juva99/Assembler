#include "../include/code_container.h"

#include "../include/file_manager.h"

void write_data(code_cont **container, unsigned short data, int *counter, int n_line) {
    unsigned short mask = 0;
    expend_memory(container, *counter);
    mask = ((1 << MAX_BIN_LENGTH) - 1);
    (*container + *counter)->bin_rep = data & mask;
    (*container + *counter)->code_line = n_line;
    (*container + *counter)->label = NULL;
    (*counter)++;
}

void add_data(code_cont **data, unsigned short val, int *dc, int n_line) {
    write_data(data, val, dc, n_line);
}

void write_data_label(code_cont **container, unsigned short data, int *counter, char *label, int n_line) {
    write_data(container, data, counter, n_line);
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

void add_command(code_cont **code, cmd_struct *cmd, int *ic, int n_line) {
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
    write_data(code, command, ic, n_line);

    /* if both methods reg merge them */
    if (src_command && dst_command && cmd->length == 2) {
        write_data(code, src_command | dst_command, ic, n_line);
        return;
    }
    /* handle source command */
    if (src_command) {
        write_data(code, src_command, ic, n_line);
    } else if (cmd->src_method == 1) {
        write_data_label(code, src_command, ic, cmd->src, n_line);
    }
    /* handle dest command */
    if (dst_command) {
        write_data(code, dst_command, ic, n_line);
    } else if (cmd->dst_method == 1) {
        write_data_label(code, dst_command, ic, cmd->dst, n_line);
    }
}

unsigned short create_method_line(cmd_struct *cmd, int method, char *value, int is_src) {
    int reg_num, offset, num;
    unsigned short method_line = 0;
    int is_negative = 1;


    switch (method) {
        case 0: {
            method_line = 1U << ABSOLUTE;
            num = read_num_arg(value);
            method_line |= (num << DATA_OFFSET);
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
    return (method_line & ~(1U << MAX_BIN_LENGTH));
}

void update_line(code_cont *code, Symbol *symbol) {
    ARE line_are;
    unsigned short new_val = 0;

    /* set ARE type based on instruction type */
    if (strcmp(symbol->instr_type, ".data") == 0 || strcmp(symbol->instr_type, ".code") == 0)
        line_are = RELOCATABLE;
    else if (strcmp(symbol->instr_type, ".external") == 0)
        line_are = EXTERNAL;
    else {
        /* unreachable code */
        return;
    }

    /* creating new line */
    new_val |= 1U << line_are;
    new_val |= symbol->value << DATA_OFFSET;
    code->bin_rep = new_val;
}

int save_object_file(char *filename, code_cont *code, code_cont *data, int ic, int dc) {
    int i;
    char *full_filename;
    FILE *ob_file;
    full_filename = add_file_extension(filename, FINAL_FILE_EXTENSION);
    ob_file = fopen(full_filename, "w");
    if (ob_file == NULL) {
        /* error - file opening failed */
        free(full_filename);
        return ERROR_ID_1;
    }
    fprintf(ob_file, "%4d %d\n", ic, dc);
    for (i = 0; i < ic; ++i) {
        fprintf(ob_file, "%04d %05u\n", i + IC_OFFSET, to_octal((code + i)->bin_rep));
    }
    for (i = ic; i < ic + dc; ++i) {
        fprintf(ob_file, "%04d %05u\n", i + IC_OFFSET, to_octal((data + i - ic)->bin_rep));
    }

    fclose(ob_file);
    free(full_filename);
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
