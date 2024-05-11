#ifndef UTILS_H_
#define UTILS_H_

#include "mevent.h"
#include <sys/cdefs.h>

typedef struct {
  int error_code;
  int value;
} ResultInt;

#define EVENT_TYPE_MENU                                                        \
  "\nTipologie Evento\n"                                                       \
  "[1]: Workshop\n"                                                            \
  "[2]: Sessione di keynote\n"                                                 \
  "[3]: Panel di discussione\n"                                                \
  "Seleziona tipologia evento (1, 2 o 3): "

void clean_file(FILE *file);
int read_line_from_file(char *line, int size, FILE *file);
__attribute_warn_unused_result__ int read_line(char *line, int size);
ResultInt read_int(void);
void *my_alloc(unsigned long nmemb, unsigned long size);
__attribute_warn_unused_result__ void *my_realloc(void *p, unsigned long nmemb,
                                                  unsigned long size);
__attribute_warn_unused_result__ char *my_strdup(const char *stringa);
#endif
