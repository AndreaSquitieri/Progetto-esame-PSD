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

Event read_event(void);
int read_line(char *line, int size);
ResultInt read_int(void);
void *my_alloc(unsigned long nmemb, unsigned long size);
__attribute_warn_unused_result__ void *my_realloc(void *p, unsigned long nmemb,
                                                  unsigned long size);

#endif
