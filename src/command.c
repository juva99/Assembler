#include "../include/command.h"
#include "../include/utils.h"

cmd_struct *build_command(char *line) {
    int args;
    char sym_name[MAX_LABEL_LENGTH + 1];
    char arg[MAX_LABEL_LENGTH + 1];
    cmd_struct *cmd = malloc(sizeof(cmd_struct));

    if (cmd == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        /* error */
        return NULL;
    }
    /* init command */
    cmd->label = NULL;
    cmd->opcode = -1;
    cmd->src = NULL;
    cmd->dst = NULL;
    cmd->src_method = -1;
    cmd->dst_method = -1;
    cmd->length = 0;

    /* check for command label */
    if (extract_symbol(line, sym_name, ':')) {
        cmd->label = malloc(strlen(sym_name) + 1);
        if (cmd->label == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            /* error */
            free(cmd);
            return NULL;
        }
        strcpy(cmd->label, sym_name);
    }
    /* get command opcode */
    cmd->opcode = extract_opcode(line);
    /* invalid opcode */
    if (cmd->opcode < 0) {
        /* error invalid opcode */
        free(cmd);
        return NULL;
    }

    /* parse arguments */
    args = get_opcode_args(cmd->opcode);
    switch (args) {
        case 0: {
            if (strcmp(line, "") != 0) {
                /* error command extra text */
                free(cmd);
                return NULL;
            }
            cmd->length = 1;
            return cmd;
        }
        case 1: {
            extract_next(line, arg, ' ');
            if (strcmp(line, "") != 0) {
                /* error command extra text */
                free(cmd);
                return NULL;
            }
            if (!dup_argument(&(cmd->dst), arg)) {
                fprintf(stderr, "Memory allocation failed\n");
                /* error */
                free(cmd);
                return NULL;
            }
            cmd->length = 2;
            cmd->dst_method = get_dst_add_method(cmd->opcode, cmd->dst);
            if (cmd->dst_method < 0) {
                /* error dst not valid */
                free(cmd);
                return NULL;
            }
            return cmd;
        }
        case 2: {
            extract_next(line, arg, ',');
            if (!dup_argument(&(cmd->src), arg)) {
                fprintf(stderr, "Memory allocation failed\n");
                /* error */
                free(cmd);
                return NULL;
            }
            extract_next(line, arg, ' ');
            if (strcmp(line, "") != 0) {
                /* error command extra text */
                free(cmd);
                return NULL;
            }
            if (!dup_argument(&(cmd->dst), arg)) {
                fprintf(stderr, "Memory allocation failed\n");
                /* error */
                free(cmd);
                return NULL;
            }
            cmd->src_method = get_src_add_method(cmd->opcode, cmd->src);
            cmd->dst_method = get_dst_add_method(cmd->opcode, cmd->dst);
            if (cmd->src_method < 0 || cmd->dst_method < 0) {
                /* error src or dst method not legal */
                free(cmd);
                return NULL;
            }
            cmd->length = 3;
            /* check if both of the methods are registers to calc command length */
            if ((cmd->src_method == 3 || cmd->src_method == 2) &&
                (cmd->dst_method == 3 || cmd->dst_method == 2)) {
                cmd->length = 2;
            }
            return cmd;
        }
        default: {
            /* error invalid args count */
            free(cmd);
            return NULL;
        }
    }
}

int dup_argument(char **dest, char *str) {
    *(dest) = malloc(strlen(str) + 1);
    if (*(dest) == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        /* error */
        return 0;
    }
    strcpy(*(dest), str);
    return 1;
}