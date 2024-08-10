#ifndef OPENU_PROJECT_FIRST_STAGE_H
#define OPENU_PROJECT_FIRST_STAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/symbol_table.h"
#include "../include/symbol_list.h"
#include "../include/command.h"
#include "../include/second_stage.h"
#include "../include/file.h"


int first_stage_process(file_struct *curr_file);

#endif
