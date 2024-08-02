cmake_minimum_required(VERSION 3.28)
project(openu_project C)

set(CMAKE_C_STANDARD 90)

# Include directories
include_directories(include)

# Source files
set(SOURCES
        src/main.c
        src/macro_table.c
        src/preprocess.c
        src/utils.c
        src/preprocess.c
        src/symbol_table.c
        src/code_container.c
        src/command.c
        src/special_symbol_list.c
        include/special_symbol_list.h
)

# Create the main executable
add_executable(openu_project ${SOURCES})

# Unit tests
set(TEST_SOURCES
        tests/macro_table_test.c
        src/macro_table.c
        src/preprocess.c
        src/utils.c
        src/first_stage.c
        src/symbol_table.c
        tests/symbol_table_test.c
        src/command.c
)

# Create the test executable
add_executable(macro_table_test ${TEST_SOURCES})

# Enable testing
enable_testing()

# Add a test
add_test(NAME MacroTableTest COMMAND macro_table_test)
