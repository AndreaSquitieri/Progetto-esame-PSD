#ifndef LOGGING_H_
#define LOGGING_H_
#include <stdio.h>

void logger(const char *tag, const char *message, FILE *file);
void log_error(const char *message);

#endif // LOGGING_H_
