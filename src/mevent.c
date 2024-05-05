#include "mevent.h"
#include "date.h"
#include "logging.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int event_id_counter = 0;

typedef struct EventStruct {
  unsigned int id;
  EventType type;
  char *name;
  Date start_date;
  Date end_date;
} Event_t;

Event new_event(EventType type, const char *name, Date start_date,
                Date end_date) {
  if (name == NULL) {
    return NULL_EVENT;
  }
  if (start_date == NULL_DATE) {
    return NULL_EVENT;
  }
  Event new_event = calloc(1, sizeof(*new_event));
  if (new_event == NULL) {
    log_error("Allocazione oggetto 'event' fallita.");
    return NULL_EVENT;
  }
  new_event->start_date = start_date;
  new_event->end_date = end_date;
  new_event->name = strdup(name);
  if (new_event->name == NULL) {
    log_error("Allocazione oggetto 'new_event->name' fallita.");
    free_date(new_event->start_date);
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
      cmp_date(get_event_start_date(event_a), get_event_start_date(event_b));
  if (date_comparison < 0) {
    return -1;
  }
  if (date_comparison > 0) {
    return 1;
  }
  return strcmp(event_a->name, event_b->name);
}

Event copy_event(ConstEvent event) {
  if (event == NULL_EVENT) {
    return NULL_EVENT;
  }
  return new_event(event->type, event->name, copy_date(event->start_date),
                   copy_date(event->end_date));
}

unsigned int get_event_id(ConstEvent event) { return event->id; }

ConstDate get_event_start_date(ConstEvent event) {
  if (event == NULL_EVENT) {
    return NULL_DATE;
  }
  return event->start_date;
}

ConstDate get_event_end_date(ConstEvent event) {
  if (event == NULL_EVENT) {
    return NULL_DATE;
  }
  return event->end_date;
}

const char *get_event_name(ConstEvent event) {
  if (event == NULL_EVENT) {
    return NULL;
  }
  return event->name;
}
EventType get_type_event(ConstEvent event) {
  if (event == NULL_EVENT) {
    return -1;
  }
  return event->type;
}

int set_event_start_date(Event event, Date start_date) {
  if (event == NULL_EVENT) {
    log_error("Passato puntatore NULL alla funzione 'set_event_start_date'.");
    return -1;
  }
  if (cmp_date(start_date, event->end_date) > 0) {
    log_error(
        "Data inizio superiore alla data di fine in 'set_event_start_date'.");
    return -2;
  }
  free_date(event->start_date);
  event->start_date = start_date;
  return 0;
}

int set_event_end_date(Event event, Date end_date) {
  if (event == NULL_EVENT) {
    log_error("Passato puntatore NULL alla funzione 'set_event_end_date'.");
    return -1;
  }
  if (cmp_date(end_date, event->start_date) < 0) {
    log_error(
        "Data fine inferiore alla data di inizio in 'set_event_end_date'.");
    return -2;
  }
  free_date(event->end_date);
  event->end_date = end_date;
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
  printf("Data inizio: ");
  print_date(event->start_date);
  puts("");
  printf("Data fine: ");
  print_date(event->end_date);
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
  Date start_date = NULL_DATE;
  do {
    printf("Inserisci data inizio evento (DD/MM/AAAA hh:mm): ");
    start_date = read_date();
  } while (start_date == NULL_DATE && printf("Data inserita non valida\n"));

  Date end_date = NULL_DATE;
  do {
    printf("Inserisci data fine evento (DD/MM/AAAA hh:mm): ");
    end_date = read_date();
  } while ((end_date == NULL_DATE || cmp_date(start_date, end_date) > 0) &&
           printf("Data inserita non valida\n"));

  // Return event
  Event event = new_event(type, name, start_date, end_date);
  return event;
}

int is_event_equal(ConstEvent event_a, ConstEvent event_b) {
  return event_a != NULL_EVENT && event_b != NULL_EVENT &&
         event_a->id == event_b->id;
}

bool do_events_overlap(ConstEvent event_a, ConstEvent event_b) {
  ConstDate start_a = get_event_start_date(event_a);
  ConstDate end_a = get_event_end_date(event_a);

  ConstDate start_b = get_event_start_date(event_b);
  ConstDate end_b = get_event_end_date(event_b);

  bool part_a =
      cmp_date(start_b, start_a) <= 0 && cmp_date(start_a, end_b) <= 0;

  bool part_b =
      cmp_date(start_a, start_b) <= 0 && cmp_date(start_b, end_a) <= 0;
  return part_a || part_b;
}

void free_event(Event event) {
  free_date(event->start_date);
  free_date(event->end_date);
  free(event->name);
  free(event);
}
