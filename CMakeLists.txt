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
        src/symbol_table.c
        src/code_container.c
        src/command.c
        src/second_stage.c
        src/symbol_list.c
        src/first_stage.c
        src/file.c
)

# Create the main executable
add_executable(openu_project ${SOURCES})

# Unit tests
set(TEST_SOURCES
        tests/macro_table_test.c
        src/macro_table.c
        src/preprocess.c
        src/utils.c
        src/symbol_table.c
        src/command.c
        src/code_container.c
        src/symbol_list.c
)

# Create the test executable
add_executable(macro_table_test ${TEST_SOURCES})


# Enable testing
enable_testing()

# Add a test
add_test(NAME MacroTableTest COMMAND macro_table_test)
