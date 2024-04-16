#include "mevent.h"
#include "logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct EventStruct {
  EventType type;
  char *name;
  Date date;
} Event_t;

Event new_event(EventType type, const char *name, ConstDate date) {
  Event new_event = calloc(1, sizeof(*new_event));
  if (new_event == NULL) {
    log_error("Allocazione oggetto 'event' fallita.");
    return NULL;
  }
  new_event->date = copy_date(date);
  if (new_event->date == NULL) {
    log_error("Allocazione oggetto 'new_event->date' fallita.");
    free(new_event);
    return NULL;
  }
  new_event->name = strdup(name);
  if (new_event->name == NULL) {
    log_error("Allocazione oggetto 'new_event->name' fallita.");
    free_date(new_event->date);
    free(new_event);
    return NULL;
  }
  new_event->type = type;
  return new_event;
}

Event copy_event(ConstEvent event) {
  if (event == NULL) {
    return NULL;
  }
  return new_event(event->type, event->name, event->date);
}

Date get_date(ConstEvent event) {
  if (event == NULL) {
    return NULL;
  }
  return copy_date(event->date);
}
char *get_name(ConstEvent event) {
  if (event == NULL) {
    return NULL;
  }
  return strdup(event->name);
}
EventType get_type_event(ConstEvent event) {
  if (event == NULL) {
    return -1;
  }
  return event->type;
}

int set_date(Event event, const Date date) {
  if (event == NULL) {
    log_error("Passato puntatore NULL alla funzione 'set_date'.");
    return -1;
  }
  Date temp = copy_date(date);
  if (temp == NULL) {
    log_error("Copia di 'date' in 'set_date' fallita.");
    return -1;
  }
  event->date = temp;
  return 0;
}
int set_name(Event event, const char *name) {
  if (event == NULL) {
    log_error("Passato puntatore NULL alla funzione 'set_name'.");
    return -1;
  }
  char *temp = strdup(name);
  if (temp == NULL) {
    log_error("Copia di 'name' in 'set_name' fallita.");
    return -1;
  }
  event->name = temp;
  return 0;
}
int set_event_type(Event event, EventType type) {
  if (event == NULL) {
    log_error("Passato puntatore NULL alla funzione 'set_event_type'.");
    return -1;
  }
  event->type = type;
  return 0;
}

static const char *const stringhe_type_event[] = {
    "Workshop", "Sessione di keynote", "Panel di discussione"};

#define FORMAT_EVENT                                                           \
  "Evento: \"%s\"\n"                                                           \
  "Tipo: %s\n"                                                                 \
  "Data: %s"

char *to_string_event(ConstEvent event) {
  const char *str_type = stringhe_type_event[event->type];

  char *str_date = to_string_date(event->date);
  if (str_date == NULL) {
    log_error("Allocazione oggetto 'str_date' fallita.");
    return NULL;
  }

  int len = snprintf(NULL, 0, FORMAT_EVENT, event->name, str_type, str_date);

  char *str_res = calloc(len + 1, sizeof(char));
  if (str_res == NULL) {
    log_error("Allocazione oggetto 'str_res' fallita.");
    return NULL;
  }

  if (snprintf(str_res, len + 1, FORMAT_EVENT, event->name, str_type,
               str_date) < 0) {
    log_error("Creazione 'stringa event' fallita.");
    free(str_date);
    free(str_res);
    return NULL;
  }

  free(str_date);
  return str_res;
}

void free_event(Event event) {
  free_date(event->date);
  free(event->name);
  free(event);
}
