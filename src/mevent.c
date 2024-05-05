#include "mevent.h"
#include "date.h"
#include "duration.h"
#include "logging.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int event_id_counter = 0;

typedef struct EventStruct {
  unsigned int id;
  EventType type;
  char *name;
  Date date;
  Duration duration;
} Event_t;

Event new_event(EventType type, const char *name, Date date,
                Duration duration) {
  if (name == NULL) {
    return NULL_EVENT;
  }
  if (date == NULL_DATE) {
    return NULL_EVENT;
  }
  Event new_event = calloc(1, sizeof(*new_event));
  if (new_event == NULL) {
    log_error("Allocazione oggetto 'event' fallita.");
    return NULL_EVENT;
  }
  new_event->date = date;
  new_event->duration = duration;
  new_event->name = strdup(name);
  if (new_event->name == NULL) {
    log_error("Allocazione oggetto 'new_event->name' fallita.");
    free_date(new_event->date);
    free(new_event);
    return NULL_EVENT;
  }
  new_event->type = type;
  new_event->id = event_id_counter;
  event_id_counter += 1;
  return new_event;
}

int is_valid_event_type(int type) { return type >= 0 && type <= 2; }

int is_same_instance_event(ConstEvent event_a, ConstEvent event_b) {
  return event_a->id == event_b->id;
}

int cmp_event(ConstEvent event_a, ConstEvent event_b) {
  int date_comparison =
      cmp_date(get_event_date(event_a), get_event_date(event_b));
  if (date_comparison < 0) {
    return -1;
  }
  if (date_comparison > 0) {
    return 1;
  }
  return strcmp(get_event_name(event_a), get_event_name(event_b));
}

Event copy_event(ConstEvent event) {
  if (event == NULL_EVENT) {
    return NULL_EVENT;
  }
  return new_event(event->type, event->name, copy_date(event->date),
                   copy_duration(event->duration));
}

unsigned int get_event_id(ConstEvent event) { return event->id; }

ConstDate get_event_date(ConstEvent event) {
  if (event == NULL_EVENT) {
    return NULL_DATE;
  }
  return event->date;
}
char *get_event_name(ConstEvent event) {
  if (event == NULL_EVENT) {
    return NULL;
  }
  return strdup(event->name);
}
EventType get_type_event(ConstEvent event) {
  if (event == NULL_EVENT) {
    return -1;
  }
  return event->type;
}

int set_event_date(Event event, Date date) {
  if (event == NULL_EVENT) {
    log_error("Passato puntatore NULL alla funzione 'set_date'.");
    return -1;
  }
  event->date = date;
  return 0;
}
int set_event_name(Event event, const char *name) {
  if (event == NULL_EVENT) {
    log_error("Passato puntatore NULL alla funzione 'set_name'.");
    return -1;
  }
  char *temp = strdup(name);
  if (temp == NULL) {
    log_error("Copia di 'name' in 'set_name' fallita.");
    return -1;
  }
  free(event->name);
  event->name = temp;
  return 0;
}
int set_event_type(Event event, EventType type) {
  if (event == NULL_EVENT) {
    log_error("Passato puntatore NULL alla funzione 'set_event_type'.");
    return -1;
  }
  event->type = type;
  return 0;
}

static const char *const stringhe_type_event[] = {
    "Workshop", "Sessione di keynote", "Panel di discussione"};

#define FORMAT_EVENT                                                           \
  "Id: %u\n"                                                                   \
  "Evento: \"%s\"\n"                                                           \
  "Tipo: %s"
void print_event(ConstEvent event) {
  printf(FORMAT_EVENT, event->id, event->name,
         stringhe_type_event[event->type]);
  puts("");
  printf("Data: ");
  print_date(event->date);
  puts("");
  printf("Durata ");
  print_duration(event->duration);
}

#define MAXSIZE 102

Event read_event(void) {
  // Read event name
  printf("Inserisci nome evento [Max 100 caratteri]: ");
  char name[MAXSIZE] = {0};
  if (read_line(name, MAXSIZE)) {
    return NULL_EVENT;
  }

  // Read event type
  int type = -1;
  do {
    printf(EVENT_TYPE_MENU);
    ResultInt res = read_int();
    if (res.error_code) {
      continue;
    }
    type = res.value - 1;
  } while (!is_valid_event_type(type) &&
           printf("Valore inserito non valido\n"));

  // Read event date
  Date date = NULL_DATE;
  do {
    printf("Inserisci data evento (DD/MM/AAAA hh:mm): ");
    date = read_date();
  } while (date == NULL_DATE && printf("Data inserita non valida\n"));

  Duration duration = NULL_DURATION;
  do {
    printf("Inserisci durata evento (hh:mm): ");
    duration = read_duration();
  } while (duration == NULL_DURATION && printf("Durata inserita non valida\n"));

  // Return event
  Event event = new_event(type, name, date, duration);
  return event;
}

int is_event_equal(ConstEvent event_a, ConstEvent event_b) {
  return event_a != NULL_EVENT && event_b != NULL_EVENT &&
         event_a->id == event_b->id;
}

void free_event(Event event) {
  free_date(event->date);
  free(event->name);
  free(event->duration);
  free(event);
}
