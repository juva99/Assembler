#include <stdio.h>
#include "../include/preprocess.h"
#include "../include/first_stage.h"

int main(void) {
    preprocess("test_files/test.as");
    first_stage_process("test_files/test.am");
    printf("done");
}

