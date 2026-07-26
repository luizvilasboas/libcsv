#ifndef libcsv_H
#define libcsv_H

#include <stdio.h>

/**
 * @brief Error codes returned by library operations.
 */
typedef enum {
  CSV_SUCCESS,          /**< Operation completed successfully. */
  CSV_ERROR_MEMORY,     /**< Memory allocation failure. */
  CSV_ERROR_FILE_OPEN,  /**< Error opening or accessing file. */
  CSV_ERROR_INVALID_ARG /**< Invalid argument passed to function. */
} CSVError;

/**
 * @brief Structure representing a single CSV row.
 */
typedef struct {
  char** fields;   /**< Array of strings containing field values. */
  int field_count; /**< Total number of fields in the row. */
} CSVRow;

/**
 * @brief Structure managing the state of a CSV file parser.
 */
typedef struct {
  FILE* file;     /**< Pointer to the opened CSV file. */
  char delimiter; /**< Character used as field delimiter (e.g., ',', ';'). */
} CSVParser;

/**
 * @brief Creates and initializes a parser to read a CSV file.
 *
 * @param filename Path to the CSV file to be opened.
 * @param delimiter Field delimiter character.
 * @return Pointer to the allocated CSVParser structure, or NULL on error.
 */
CSVParser* csv_parser_create(const char* filename, char delimiter);

/**
 * @brief Frees resources associated with the parser and closes the open file.
 *
 * @param parser Pointer to the CSVParser structure to destroy.
 */
void csv_parser_destroy(CSVParser* parser);

/**
 * @brief Reads the next row from the CSV file using the parser.
 *
 * @param parser Pointer to the active CSVParser.
 * @return Pointer to the populated CSVRow structure, or NULL on EOF/error.
 */
CSVRow* csv_read_row(CSVParser* parser);

/**
 * @brief Manually creates and allocates a CSVRow structure from an array of
 * strings.
 *
 * @param field_count Number of fields to insert.
 * @param fields Array of pointers to field strings.
 * @return Pointer to the created CSVRow structure, or NULL on error.
 */
CSVRow* csv_row_create(int field_count, const char** fields);

/**
 * @brief Frees memory allocated for a CSVRow structure and all its internal
 * fields.
 *
 * @param row Pointer to the CSVRow structure to destroy.
 */
void csv_row_destroy(CSVRow* row);

/**
 * @brief Parses an individual CSV-formatted string into a CSVRow structure.
 *
 * @param csv_string The raw CSV-formatted input string.
 * @param delimiter Field delimiter character.
 * @return Pointer to the allocated CSVRow structure, or NULL on error.
 */
CSVRow* csv_parse_string(const char* csv_string, char delimiter);

/**
 * @brief Converts a CSVRow structure into a single formatted string.
 *
 * @param row Pointer to the CSV row structure.
 * @param delimiter Character to place between fields.
 * @return Dynamically allocated string with formatted data (must be freed by
 * caller), or NULL.
 */
char* csv_write_string(const CSVRow* row, char delimiter);

/**
 * @brief Writes the contents of a CSVRow directly to a file.
 *
 * @param row Pointer to the row to write.
 * @param filename Path to the output destination file.
 * @param delimiter Field delimiter character.
 * @return 0 on success, or an error code on failure.
 */
int csv_write_file(const CSVRow* row, const char* filename, char delimiter);

/**
 * @brief Retrieves the value of a specific field in a row by its index.
 *
 * @param row Pointer to the CSV row structure.
 * @param field_index Zero-based index of the target field.
 * @return Pointer to the field string, or NULL if index is out of bounds.
 */
char* csv_get_field(const CSVRow* row, int field_index);

/**
 * @brief Updates the delimiter character used by an active parser.
 *
 * @param parser Pointer to the CSVParser instance.
 * @param new_delimiter New delimiter character to set.
 */
void csv_set_delimiter(CSVParser* parser, char new_delimiter);

/**
 * @brief Gets the current delimiter configured for the parser.
 *
 * @param parser Pointer to the CSVParser instance.
 * @return The delimiter character currently in use.
 */
char csv_get_delimiter(const CSVParser* parser);

/**
 * @brief Returns a human-readable message corresponding to an error code.
 *
 * @param error The CSVError code.
 * @return Constant string describing the error.
 */
const char* csv_error_message(CSVError error);

/**
 * @brief Gets the last error code produced by the library on the calling
 * thread.
 *
 * @return The CSVError code corresponding to the last failure.
 */
CSVError csv_get_last_error(void);

#endif
