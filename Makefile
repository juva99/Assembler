# Compiler and flags
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c90 -Werror

# Source files
SRC = src/main.c \
      src/macro_table.c \
      src/preprocess.c \
      src/utils.c \
      src/symbol_table.c \
      src/code_container.c \
      src/command.c \
      src/second_stage.c \
      src/symbol_list.c \
      src/first_stage.c \
      src/file_manager.c

# Object files
OBJ = $(SRC:.c=.o)

# Executable name
TARGET = assembler

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Compile each source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the build
clean:
	rm -f $(OBJ) $(TARGET)

