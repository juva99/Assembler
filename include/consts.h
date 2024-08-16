#ifndef OPENU_PROJECT_CONSTS_H
#define OPENU_PROJECT_CONSTS_H

/**
 * @brief Maximum length of a line in the source file, including the newline character.
 */
#define MAX_LINE_LENGTH 82

/**
 * @brief Number of opcodes supported by the assembler.
 */
#define OPCODES_COUNT 16

/**
 * @brief Number of registers available in the target machine architecture.
 */
#define REGISTER_COUNT 8

/**
 * @brief Number of instruction types recognized by the assembler.
 */
#define INSTRUCTIONS_COUNT 4

/**
 * @brief Maximum length of a label in the source code, excluding the null terminator.
 */
#define MAX_LABEL_LENGTH 31

/**
 * @brief Maximum length of an opcode in the source code.
 */
#define MAX_OPCODE_LENGTH 4

/**
 * @brief Maximum number of addressing methods supported by the assembler.
 */
#define MAX_ADDRESS_METHODS 4

/**
 * @brief Length of a binary word in the target machine, in bits.
 */
#define MAX_BIN_LENGTH 15

/**
 * @brief File extension for preprocessed source files.
 */
#define PREPROCESSED_FILE_TYPE ".as"

/**
 * @brief File extension for processed source files after the first stage.
 */
#define PROCESSED_FILE_TYPE ".am"

/**
 * @brief File extension for final binary object files.
 */
#define FINAL_FILE_EXTENSION ".ob"

/**
 * @brief Length of the file extension for entries files.
 */
#define ENTERIES_FILE_EXTENSION_LEN 4

/**
 * @brief File extension for entries files, which list entry labels.
 */
#define ENTERIES_FILE_EXTENSION ".ent"

/**
 * @brief Length of the file extension for externals files.
 */
#define EXTERNS_FILE_EXTENSION_LEN 4

/**
 * @brief File extension for externals files, which list external symbols.
 */
#define EXTERNS_FILE_EXTENSION ".ext"

/**
 * @brief Maximum length of a file extension, including the dot.
 */
#define MAX_EXTENSION_LENGTH 5

/**
 * @brief Maximum numeric value allowed for data declarations.
 */
#define MAX_DATA_NUM_VALUE 16383

/**
 * @brief Minimum numeric value allowed for data declarations.
 */
#define MIN_DATA_NUM_VALUE -16384

/**
 * @brief Maximum numeric value allowed for command operands.
 */
#define MAX_COMMAND_NUM_VALUE 2047

/**
 * @brief Minimum numeric value allowed for command operands.
 */
#define MIN_COMMAND_NUM_VALUE -2048

/**
 * @brief Maximum allowed size for the binary object file, in bytes.
 */
#define MAX_FILE_SIZE 4096

/**
 * @brief Offset applied to the instruction counter to account for memory addressing.
 */
#define IC_OFFSET 100

#endif

