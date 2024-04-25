#include "mevent.h"
#include "date.h"
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
} Event_t;

Event new_event(EventType type, const char *name, Date date) {
  if (name == NULL) {
    return NULL;
  }
  if (date == NULL) {
    return NULL;
  }
  Event new_event = calloc(1, sizeof(*new_event));
  if (new_event == NULL) {
    log_error("Allocazione oggetto 'event' fallita.");
    return NULL;
  }
  new_event->date = date;
  new_event->name = strdup(name);
  if (new_event->name == NULL) {
    log_error("Allocazione oggetto 'new_event->name' fallita.");
    free_date(new_event->date);
    free(new_event);
    return NULL;
  }
  new_event->type = type;
  new_event->id = event_id_counter;
  event_id_counter += 1;
  return new_event;
}

int is_valid_event_type(int type){
	return type >= 0 && type <= 2;
}

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
  if (event == NULL) {
    return NULL;
  }
  return new_event(event->type, event->name, event->date);
}

unsigned int get_event_id(ConstEvent event) { return event->id; }

ConstDate get_event_date(ConstEvent event) {
  if (event == NULL) {
    return NULL;
  }
  return event->date;
}
char *get_event_name(ConstEvent event) {
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

int set_event_date(Event event, Date date) {
  if (event == NULL) {
    log_error("Passato puntatore NULL alla funzione 'set_date'.");
    return -1;
  }
  Date temp = date;
  if (temp == NULL) {
    log_error("Copia di 'date' in 'set_date' fallita.");
    return -1;
  }
  event->date = temp;
  return 0;
}
int set_event_name(Event event, const char *name) {
  if (event == NULL) {
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
  "Id: %u\n"                                                                   \
  "Evento: \"%s\"\n"                                                           \
  "Tipo: %s"
void print_event(ConstEvent event) {
  printf(FORMAT_EVENT, event->id, event->name,
         stringhe_type_event[event->type]);
	puts("");
  printf("Data: ");
  print_date(event->date);
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
  } while ((type < 0 || type > 2) && printf("Valore inserito non valido\n"));

  // Read event date
  Date date = NULL;
  do {
    printf("Inserisci data evento (DD/MM/AAAA hh:mm): ");
    date = read_date();
  } while (date == NULL && printf("Data inserita non valida\n"));

  // Return event
  Event event = new_event(type, name, date);
  return event;
}

void free_event(Event event) {
  free_date(event->date);
  free(event->name);
  free(event);
}
