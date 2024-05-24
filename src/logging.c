#include "logging.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Array of strings corresponding to log levels
static const char *const log_level_strings[] = {"INFO", "WARN", "ERROR"};

// Static file pointer to the log file, initialized to NULL
static FILE *log_file = NULL;

// Function to set the log file pointer
void set_log_file(FILE *file) { log_file = file; }

// Function to log a message with a given log level
void log_message(LogLevel level, const char *message) {
  // Return early if the message is NULL
  if (!message) {
    return; // Sanity check for null pointer
  }
  // Return early if the log file is not set
  if (log_file == NULL) {
    return;
  }

  // Use the provided log file for output
  FILE *output = log_file;
  // Get the current time
  time_t now = time(NULL);
  if (now == -1) {
    // Handle error if time retrieval fails
    (void)fprintf(output, "Failed to get current time: %s\n", strerror(errno));
    return;
  }

  // Convert the current time to local time
  struct tm local_time;
  if (!localtime_r(&now, &local_time)) {
    // Handle error if local time conversion fails
    (void)fprintf(output, "Failed to convert time to local time: %s\n",
                  strerror(errno));
    return;
  }

  // Buffer to hold the formatted time string
  char time_str[26]; // ctime_r buffer size
  if (!ctime_r(&now, time_str)) {
    // Handle error if time formatting fails
    (void)fprintf(output, "Failed to format time string: %s\n",
                  strerror(errno));
    return;
  }

  // Remove the newline character added by ctime_r
  time_str[24] = '\0';

  // Log the message with the timestamp and log level
  (void)fprintf(output, "%s [%s]: %s\n", time_str, log_level_strings[level],
                message);
  // Flush the output to ensure the message is written to the file
  (void)fflush(output);
}

// Convenience function to log an error message
void log_error(const char *message) { log_message(LOG_ERROR, message); }
