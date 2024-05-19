#include "logging.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

static const char *const log_level_strings[] = {"INFO", "WARN", "ERROR"};

static FILE *log_file = NULL;

void set_log_file(FILE *file) { log_file = file; }

void log_message(LogLevel level, const char *message) {
  if (!message) {
    return; // Sanity check for null pointer
  }
  if (log_file == NULL) {
    return;
  }

  FILE *output = log_file;
  time_t now = time(NULL);
  if (now == -1) {
    (void)fprintf(output, "Failed to get current time: %s\n", strerror(errno));
    return;
  }

  struct tm local_time;
  if (!localtime_r(&now, &local_time)) {
    (void)fprintf(output, "Failed to convert time to local time: %s\n",
                  strerror(errno));
    return;
  }

  char time_str[26]; // ctime_r buffer size
  if (!ctime_r(&now, time_str)) {
    (void)fprintf(output, "Failed to format time string: %s\n",
                  strerror(errno));
    return;
  }

  // Remove the newline character added by ctime_r
  time_str[24] = '\0';

  (void)fprintf(output, "%s [%s]: %s\n", time_str, log_level_strings[level],
                message);
  (void)fflush(output);
}

void log_error(const char *message) { log_message(LOG_ERROR, message); }

void log_info(const char *message) { log_message(LOG_INFO, message); }

void log_warn(const char *message) { log_message(LOG_WARN, message); }
