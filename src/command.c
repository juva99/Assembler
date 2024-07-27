#include "../include/command.h"
#include "../include/utils.h"

cmd_struct *build_command(char *line) {
    int is_label, args;
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
            break;
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

            break;
        }
        default: {
            /* error invalid args count */
            free(cmd);
            return NULL;
        }
    }

    /* validate arguments */
    check_command_args(cmd);
    return cmd;
}


int check_command_args(cmd_struct *cmd) {
    return check_opcode_address(cmd->opcode, cmd->src, cmd->dst);
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