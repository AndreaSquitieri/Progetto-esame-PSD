#include "logging.h"
#include <stdio.h>
#include <time.h>

void log_error(const char *message) {
  logger("ERROR", message, stderr);
  (void)fflush(stderr);
}

void logger(const char *tag, const char *message, FILE *file) {
  time_t now = 0;
  (void)time(&now);
  (void)fprintf(file, "%s [%s]: %s\n", ctime(&now), tag, message);
}
