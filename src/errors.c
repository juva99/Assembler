#include "../include/errors.h"

Error errors[] = {
    {ERROR_ID_0, ""},
    /*extrenals errors */
    {ERROR_ID_1, "New file opening failed"},
    {ERROR_ID_2, "Dynamic memory allocation failed"},
    {ERROR_ID_3, "Creating macro table failed"},
    {ERROR_ID_4, "Opening final file for writing failed"},
    {ERROR_ID_5, ""},
    {ERROR_ID_6, ""},
    {ERROR_ID_7, ""},
    {, ""},
    {, ""},
    {, ""},
    {, ""},
    /*iternals errors */
    {, "Macro is not declared"},
    {, "Macro name is invalid"},
    {, "Macro declaration error - Extraneous text after end of declaration"},
    {, "Macro declaration error - Macro name is used more than once"}/*insert*/,
    {, "Data - string declaration error - Extraneous text after first \" "}/*encode string*/,
    {, "Data - numeric declaraion error - No numeric values "}/*encode numeric data*/,
    {, "Data - numeric declaraion error - declaration ends with ','"}/*encode numeric data*/,
    {, "Data - numeric declaraion error - non-numeric value entered "}/*encode numeric data*/,
    {, "Unvalid data type "}/*encode_data - maybe the error can be removed*/,
    {, "Entry label was never initialized"} /*validate_entries*/,
    {, "Command - Invalid opcode"}/*build_command */,
    {, "Command - Extraneous text after command"} /*build_command*/,
    {, "Command - invalid dst"},
    {,"Command - src or dst method illegal"},
    {,"Command - invalid arguments count"},
};

void print_internal_error(int error_id) {
}

void print_external_error(int error_id, ) {
}
