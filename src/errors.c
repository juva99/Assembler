#include "../include/errors.h"

Error errors[] = {
    /* no error */
    {ERROR_ID_0, "", 0, UNASSIGNED},
    /*extrenals errors */
    {ERROR_ID_1, "New file opening failed", 0, UNASSIGNED},
    {ERROR_ID_2, "Dynamic memory allocation failed", 0, UNASSIGNED},
    {ERROR_ID_3, "Creating macro table failed", 0, UNASSIGNED},
    {ERROR_ID_4, "Opening final file for writing failed", 0, UNASSIGNED},
    {ERROR_ID_5, "", 0, UNASSIGNED},
    {ERROR_ID_6, "", 0, UNASSIGNED},
    {ERROR_ID_7, "", 0, UNASSIGNED},
    {, "", 0, UNASSIGNED},
    {, "", 0, UNASSIGNED},
    {, "", 0, UNASSIGNED},

    /*iternals errors */
    {ERROR_ID_11, "Macro is not declared", 0, UNASSIGNED},
    {ERROR_ID_12, "Macro name is invalid", 0, UNASSIGNED},
    {ERROR_ID_13, "Macro declaration error - Extraneous text after end of declaration", 0, UNASSIGNED},
    {ERROR_ID_14, "Macro declaration error - Macro name is used more than once", 0, UNASSIGNED}/*insert*/,
    {ERROR_ID_15, "Data - string declaration error - Extraneous text after first \" ", 0, UNASSIGNED}/*encode string*/,
    {ERROR_ID_16, "Data - numeric declaraion error - No numeric values ", 0, UNASSIGNED}/*encode numeric data*/,
    {ERROR_ID_17, "Data - numeric declaraion error - declaration ends with ','", 0, UNASSIGNED}/*encode numeric data*/,
    {ERROR_ID_18, "Data - numeric declaraion error - non-numeric value entered ", 0, UNASSIGNED}/*encode numeric data*/,
    {ERROR_ID_19, "Unvalid data type ", 0, UNASSIGNED}/*encode_data - maybe the error can be removed*/,
    {ERROR_ID_20, "Entry label was never initialized", 0, UNASSIGNED} /*validate_entries*/,
    {ERROR_ID_21, "Command - Invalid opcode", 0, UNASSIGNED}/*build_command */,
    {ERROR_ID_22, "Command - Extraneous text after command", 0, UNASSIGNED} /*build_command*/,
    {ERROR_ID_23, "Command - invalid dst", 0, UNASSIGNED},
    {ERROR_ID_24, "Command - src or dst method illegal", 0, UNASSIGNED},
    {ERROR_ID_25, "Command - invalid arguments count", 0, UNASSIGNED},
    {ERROR_ID_26, "Label name is used more than once", 0, UNASSIGNED},

};

void print_error(int error_id) {
}

void print_external_error(int error_id, ) {
}
