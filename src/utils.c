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
    clean_file(file);
    return -1;
  }

  if (line[strlen(line) - 1] != '\n') {
    clean_file(file);
    return -2;
  }

  line[strcspn(line, "\n")] = '\0';
  return 0;
}

int read_line(char *line, int size) {
  return read_line_from_file(line, size, stdin);
}

ResultInt read_int(void) {
  ResultInt res = {0};
  int choice = 0;
  char temp[MAXINTSIZE] = {0};
  if (read_line(temp, MAXINTSIZE)) {
    res.error_code = -1;
    return res;
  }
  char *endptr = NULL;
  errno = 0;
  choice = strtol(temp, &endptr, 10);
  if ((errno == ERANGE) || (errno != 0 && choice == 0)) {
    log_error("strtol");
    res.error_code = -2;
    return res;
  }
  if (endptr == temp) {
    res.error_code = -3;
    return res;
  }
  res.value = choice;
  return res;
}

void *my_alloc(unsigned long nmemb, unsigned long size) {
  void *p = calloc(nmemb, size);
  if (p == NULL) {
    log_error("Allocazione fallita\n");
    exit(EXIT_FAILURE);
  }
  return p;
}

void *my_realloc(void *p, unsigned long nmemb, unsigned long size) {
  void *temp = realloc(p, nmemb * size);
  if (temp == NULL) {
    log_error("Allocazione fallita\n");
    exit(EXIT_FAILURE);
  }
  return temp;
}

char *my_strdup(const char *stringa) {
  char *temp = strdup(stringa);
  if (temp == NULL) {
    log_error("Allocazione fallita\n");
    exit(EXIT_FAILURE);
  }
  return temp;
}

void trim_whitespaces(char *dest, char *src, int max_size) {
  if (max_size == 0) {
    return;
  }
  while (isspace(*src)) {
    src++;
  }
  int i = 0;
  for (i = 0; i < (max_size - 1) && *src; i++) {
    dest[i] = *src++;
  }
  dest[i] = '\0';
  for (int j = i - 1; j >= 0 && isspace(dest[j]); j--) {
    dest[j] = '\0';
  }
}
