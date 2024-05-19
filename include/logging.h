#ifndef LOGGING_H_
#define LOGGING_H_
#include <stdio.h>

typedef enum { LOG_INFO, LOG_WARN, LOG_ERROR } LogLevel;

void set_log_file(FILE *file);
void log_message(LogLevel level, const char *message);
void log_error(const char *message);

#endif // LOGGING_H_
