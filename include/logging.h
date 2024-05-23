#ifndef LOGGING_H_
#define LOGGING_H_
#include <stdio.h>

// Enumerates different log levels
typedef enum {
  LOG_INFO, // Informational messages
  LOG_WARN, // Warning messages
  LOG_ERROR // Error messages
} LogLevel;

/*
Syntactic Specification
- set_log_file(FILE*)
  - types: FILE*
  - internal types: None

Semantic Specification
- set_log_file(file)
  - Sets the log file to the specified file.
  - Preconditions: 'file' is a valid FILE pointer opened in writing mode.
  - Postconditions: The logging functions will write to the specified file. If
'file' is NULL, logging functions will not write to any file.
*/
void set_log_file(FILE *file);

/*
Syntactic Specification
- log_message(LogLevel, const char*)
  - types: LogLevel, const char*
  - internal types: time_t, struct tm, char[26], FILE*

Semantic Specification
- log_message(level, message)
  - Logs a message with the specified log level.
  - Preconditions:
    - 'level' is one of LOG_INFO, LOG_WARN, LOG_ERROR.
    - 'message' is a non-null pointer to a null-terminated string.
    - The log file has been set using set_log_file.
  - Postconditions:
    - The message is written to the log file with a timestamp and log level
prefix.
    - If the log file is not set, no output will be generated.
*/
void log_message(LogLevel level, const char *message);

/*
Syntactic Specification
- log_error(const char*)
  - types: const char*
  - internal types: None

Semantic Specification
- log_error(message)
  - Logs an error message.
  - Preconditions:
    - 'message' is a non-null pointer to a null-terminated string.
    - The log file has been set using set_log_file.
  - Postconditions:
    - The error message is written to the log file with a timestamp and "ERROR"
prefix.
    - If the log file is not set, no output will be generated.
*/
void log_error(const char *message);

#endif // LOGGING_H_
