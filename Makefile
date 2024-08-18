# Compiler and flags
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c90 -Werror

# Directories
SRC_DIR = src
BIN_DIR = bin

# Source files
SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/macro_table.c \
      $(SRC_DIR)/preprocess.c \
      $(SRC_DIR)/utils.c \
      $(SRC_DIR)/symbol_table.c \
      $(SRC_DIR)/code_container.c \
      $(SRC_DIR)/command.c \
      $(SRC_DIR)/second_stage.c \
      $(SRC_DIR)/symbol_list.c \
      $(SRC_DIR)/first_stage.c \
      $(SRC_DIR)/file_manager.c

# Object files
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC))

# Executable name
TARGET = assembler

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Compile each source file into an object file
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the bin directory exists
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean the build
clean:
	rm -f $(BIN_DIR)/*.o $(TARGET)
