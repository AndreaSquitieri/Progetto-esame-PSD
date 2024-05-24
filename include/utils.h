#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <sys/cdefs.h>

// Structure for storing integer results along with error codes
typedef struct {
  int error_code; // Error code: 0 for success, negative values for errors
  int value;      // Resulting integer value
} ResultInt;

// Menu text for selecting event types
#define EVENT_TYPE_MENU                                                        \
  "\nTipologie Evento\n"                                                       \
  "[1]: Workshop\n"                                                            \
  "[2]: Sessione di keynote\n"                                                 \
  "[3]: Panel di discussione\n"                                                \
  "Seleziona tipologia evento (1, 2 o 3): "

/*
  Syntax Specification:
  - clean_file(FILE*)
  - types: FILE*
  - internal types: none

  Semantic Specification:
  - Function: clean_file(file)
  - Description: Discards characters from the file stream until a newline or
  end-of-file is reached.
  - Preconditions: 'file' is a valid file pointer opened in reading mode.
  - Postconditions: The file pointer is advanced past the discarded characters.
*/
void clean_file(FILE *file);

/*
  Syntax Specification:
  - read_line_from_file(char*, int, FILE*) -> int
  - types: char*, int, FILE*
  - internal types: none

  Semantic Specification:
  - Function: read_line_from_file(line, size, file) -> res
  - Description: Reads a line from the specified file into the buffer, ensuring
  it fits and handles errors.
  - Preconditions: 'line' is a valid buffer of size 'size'. 'file' is a valid
  file pointer opened in reading mode.
  - Postconditions: On success, the line is stored in 'line' without the newline
  character. On failure, returns -1 if end-of-file is reached, -2 if the line is
  too long, and -3 if a read error occurs.
*/
int read_line_from_file(char *line, int size, FILE *file);

/*
  Syntax Specification:
  - read_line(char*, int) -> int
  - types: char*, int
  - internal types: none

  Semantic Specification:
  - Function: read_line(line, size) -> res
  - Description: Reads a line from standard input into the buffer.
  - Preconditions: 'line' is a valid buffer of size 'size'.
  - Postconditions: On success, the line is stored in 'line' without the newline
  character. On failure, returns -1 if end-of-file is reached, -2 if the line is
  too long, and -3 if a read error occurs.
*/
int read_line(char *line, int size);

/*
  Syntax Specification:
  - read_int(void) -> ResultInt
  - types: ResultInt
  - internal types: int, char[], char*, long, errno_t

  Semantic Specification:
  - Function: read_int() -> res
  - Description: Reads an integer from standard input and handles errors.
  - Preconditions: None.
  - Postconditions: On success, returns a ResultInt with the integer value and
  error_code 0. On failure, error_code is set to -1 for input read error, -2 for
  range error, and -3 for invalid input.
*/
ResultInt read_int(void);

/*
  Syntax Specification:
  - my_alloc(unsigned long, unsigned long)
  - types: unsigned long, void*
  - internal types: void*

  Semantic Specification:
  - Function: my_alloc(nmemb, size)
  - Description: Allocates memory for an array of nmemb elements of size bytes
  each and initializes all bytes in the allocated storage to zero.
  - Preconditions: nmemb and size are non-zero.
  - Postconditions: On success, returns a pointer to the allocated memory. On
  failure, logs an error and exits the program.
*/
void *my_alloc(unsigned long nmemb, unsigned long size);

/*
  Syntax Specification:
  - my_realloc(void*, unsigned long, unsigned long)
  - types: void*, unsigned long, void*
  - internal types: void*

  Semantic Specification:
  - Function: my_realloc(p, nmemb, size)
  - Description: Reallocates memory for an array of nmemb elements of size bytes
  each.
  - Preconditions: 'p' is a pointer to a previously allocated block of memory,
  or NULL. nmemb and size are non-zero.
  - Postconditions: On success, returns a pointer to the reallocated memory. On
  failure, logs an error and exits the program.
*/
void *my_realloc(void *p, unsigned long nmemb, unsigned long size);

/*
  Syntax Specification:
  - my_strdup(const char*) -> char*
  - types: char*
  - internal types: char*

  Semantic Specification:
  - Function: my_strdup(string) -> res_string
  - Description: Duplicates the given string.
  - Preconditions: 'string' is a valid null-terminated string.
  - Postconditions: On success, returns a pointer to the duplicated string. On
  failure, logs an error and exits the program.
*/
char *my_strdup(const char *string);

/*
  Syntax Specification:
  - trim_whitespaces(char*, char*, int)
  - types: char*, char*, int
  - internal types: int

  Semantic Specification:
  - Function: trim_whitespaces(dest, src, max_size)
  - Description: Trims leading and trailing whitespace from the source string
  and copies it to the destination buffer.
  - Preconditions: 'dest' and 'src' are valid pointers, 'max_size' is the size
  of 'dest'.
  - Postconditions: 'dest' contains the trimmed string. If 'max_size' is 0, the
  function does nothing.
*/
void trim_whitespaces(char *dest, char *src, int max_size);

#endif
