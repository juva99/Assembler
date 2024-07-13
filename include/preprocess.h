#ifndef OPENU_PROJECT_PREPROCESS_H
#define OPENU_PROJECT_PREPROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/macro_table.h"
#include "../include/utils.h"


int preprocess(char filename[]);

int process_line(char line[], FILE *file, FILE *final_file, MacroTable *macros);

int is_macro(char *line);

int handle_macro(char *line, FILE *file, MacroTable *macros);


int is_macro_name_valid(char *mac_name);

#endif //OPENU_PROJECT_PREPROCESS_H

