# libcsv

CSV parser library in C.

## Appendix

This is a C library that provides simple functions to parse CSV data, manipulate CSV rows, and handle common CSV errors. Whether you need to read CSV files, generate CSV strings, or work with CSV data in your C application.

## Features

- Parse CSV data from files or strings
- Create and manipulate CSV rows
- Write CSV data to files or strings
- Retrieve CSV field values by index
- Handle common CSV errors with ease

## Tech Stack

**Languages:** C

**Build:** Make and Docker

## Installation

Clone the project

```bash
git clone https://codeberg.org/luizvilasboas/libcsv.git
```

Go to the project directory

```bash
cd libcsv
```

Compile the library

```bash
make
```

Install the library

```bash
sudo make install
```

## Usage/Examples

```c
#include <stdio.h>
#include <libcsv.h>

int main() {
    // Create a CSVParser to read a CSV file
    CSVParser *parser = csv_parser_create("example.csv", ',');

    if (!parser) {
        fprintf(stderr, "Error: Unable to create CSV parser\n");
        return 1;
    }

    // Read rows from the CSV file
    CSVRow *row;
    while ((row = csv_read_row(parser)) != NULL) {
        for (int i = 0; i < row->field_count; i++) {
            printf("Field %d: %s\n", i, csv_get_field(row, i));
        }
        // Don't forget to free the row
        csv_row_destroy(row);
    }

    // Clean up the parser
    csv_parser_destroy(parser);

    return 0;
}
```

## Documentation

[Documentation](#)

## Running Tests

To run tests, run the following command

```bash
make test
```

## Contributing

If you have a suggestion that would make this better, please fork the repo and create a pull request.

## License

[LGPLv3](https://codeberg.org/luizvilasboas/libcsv/src/branch/main/LICENSE)
