#include "utils.h"
#include "logging.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 102
#define MAXINTSIZE 13

void clean_file(FILE *file) {
  int temp = 0;
  while ((temp = getc(file)) != '\n' && temp != EOF)
    ;
}

int read_line_from_file(char *line, int size, FILE *file) {
  if (fgets(line, size, file) == NULL) {
    if (feof(file)) {
      return -1; // End-of-file reached
    }
    if (ferror(file)) {
      return -3; // Error reading from file
    }
  }

  if (line[strlen(line) - 1] != '\n') {
    clean_file(file); // Clean the remaining content if the line is too long
    return -2;
  }

  line[strcspn(line, "\n")] = '\0'; // Remove the newline character
  return 0;
}

int read_line(char *line, int size) {
  return read_line_from_file(line, size, stdin);
}

ResultInt read_int(void) {
  ResultInt res = {0}; // Initialize result struct
  int choice = 0;
  char temp[MAXINTSIZE] = {0};

  if (read_line(temp, MAXINTSIZE)) {
    res.error_code = -1; // Set error code if reading fails
    return res;
  }

  char *endptr = NULL;
  errno = 0;
  choice = strtol(temp, &endptr, 10); // Convert the string to an integer

  if ((errno == ERANGE) || (errno != 0 && choice == 0)) {
    log_error("strtol: range error or invalid input");
    res.error_code = -2; // Set error code for range error
    return res;
  }
  if (endptr == temp) {
    log_error("strtol: no digits were found");
    res.error_code = -3; // Set error code if no digits were found
    return res;
  }

  res.value = choice; // Set the resulting value
  return res;
}

void *my_alloc(unsigned long nmemb, unsigned long size) {
  void *p = calloc(nmemb, size); // Allocate memory
  if (p == NULL) {
    log_error("Allocation failed");
    exit(EXIT_FAILURE); // Exit the program on failure
  }
  return p;
}

void *my_realloc(void *p, unsigned long nmemb, unsigned long size) {
  void *temp = realloc(p, nmemb * size); // Reallocate memory
  if (temp == NULL) {
    log_error("Allocation failed");
    exit(EXIT_FAILURE); // Exit the program on failure
  }
  return temp;
}

char *my_strdup(const char *string) {
  char *temp = strdup(string); // Duplicate the string
  if (temp == NULL) {
    log_error("Allocation failed");
    exit(EXIT_FAILURE); // Exit the program on failure
  }
  return temp;
}

void trim_whitespaces(char *dest, char *src, int max_size) {
  if (max_size == 0) {
    return;
  }

  // Skip leading whitespace
  while (isspace(*src)) {
    src++;
  }

  // Copy the string without leading whitespace
  int i = 0;
  for (i = 0; i < (max_size - 1) && *src; i++) {
    dest[i] = *src++;
  }
  dest[i] = '\0'; // Null-terminate the destination string

  // Remove trailing whitespace
  for (int j = i - 1; j >= 0 && isspace(dest[j]); j--) {
    dest[j] = '\0';
  }
}
