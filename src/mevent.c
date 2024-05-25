#include "mevent.h"
#include "date.h"
#include "logging.h"
#include "room.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FORMAT_EVENT                                                           \
  "Id: %u\n"                                                                   \
  "Evento: \"%s\"\n"                                                           \
  "Tipo: %s"

#define MAX_NAME_SIZE 100

static const char *const stringhe_type_event[] = {
    "Workshop", "Sessione di keynote", "Panel di discussione"};

// Event structure definition
typedef struct EventStruct {
  unsigned int id; // Unique identifier for the event
  EventType type;  // Type of the event (e.g., workshop, keynote session)
  char *name;      // Name of the event
  unsigned int assigned_room_id; // ID of the room assigned to the event
  Date start_date;               // Start date and time of the event
  Date end_date;                 // End date and time of the event
} Event_t;

// Function to create a new event
Event new_event(EventType type, const char *name, Date start_date,
                Date end_date, unsigned int id) {
  if (name == NULL || start_date == NULL_DATE) {
    log_error("Invalid parameters passed to 'new_event' function.");
    return NULL_EVENT;
  }
  // Allocate memory for the new event
  Event new_event = my_alloc(1, sizeof(*new_event));
  // Set the event properties
  new_event->start_date = start_date;
  new_event->end_date = end_date;
  new_event->name = my_strdup(name);
  new_event->type = type;
  new_event->assigned_room_id = NULL_ROOM_ID;
  new_event->id = id;
  return new_event;
}

int is_valid_event_type(int type) { return type >= 0 && type <= 2; }

// Function to compare two events based on their start dates and names
int cmp_event(ConstEvent event_a, ConstEvent event_b) {
  int date_comparison =
      cmp_date(get_event_start_date(event_a), get_event_start_date(event_b));
  if (date_comparison != 0) {
    return date_comparison; // Return the comparison result if start dates are
                            // different
  }
  // If start dates are equal, compare the names
  return strcmp(event_a->name, event_b->name);
}
unsigned int get_event_id(ConstEvent event) {
  if (are_events_equal(event, NULL_EVENT)) {
    log_error("NULL pointer passed to 'get_event_id' function.");
    return NULL_EVENT_ID;
  }
  return event->id;
}

ConstDate get_event_start_date(ConstEvent event) {
  if (are_events_equal(event, NULL_EVENT)) {
    log_error("NULL pointer passed to 'get_event_start_date' function.");
    return NULL_DATE;
  }
  return event->start_date;
}

ConstDate get_event_end_date(ConstEvent event) {
  if (are_events_equal(event, NULL_EVENT)) {
    log_error("NULL pointer passed to 'get_event_end_date' function.");
    return NULL_DATE;
  }
  return event->end_date;
}

const char *get_event_name(ConstEvent event) {
  if (are_events_equal(event, NULL_EVENT)) {
    log_error("NULL pointer passed to 'get_event_name' function.");
    return NULL;
  }
  return event->name;
}

EventType get_event_type(ConstEvent event) {
  if (are_events_equal(event, NULL_EVENT)) {
    log_error("NULL pointer passed to 'get_event_type' function.");
    return -1;
  }
  return event->type;
}
unsigned int get_event_room_id(ConstEvent event) {
  if (are_events_equal(event, NULL_EVENT)) {
    log_error("NULL pointer passed to 'get_event_room_id' function.");
    return NULL_ROOM_ID;
  }
  return event->assigned_room_id;
}

int set_event_room_id(Event event, unsigned int room_id) {
  if (are_events_equal(event, NULL_EVENT)) {
    log_error("NULL pointer passed to 'set_event_room_id' function.");
    return -1;
  }
  event->assigned_room_id = room_id;
  return 0;
}

int set_event_start_date(Event event, Date start_date) {
  if (are_events_equal(event, NULL_EVENT)) {
    log_error("NULL pointer passed to 'set_event_start_date' function.");
    return -1;
  }
  if (cmp_date(start_date, event->end_date) > 0) {
    log_error("Start date is later than end date in 'set_event_start_date'.");
    return -2;
  }
  free_date(event->start_date);
  event->start_date = start_date;
  return 0;
}

int set_event_end_date(Event event, Date end_date) {
  if (are_events_equal(event, NULL_EVENT)) {
    log_error("NULL pointer passed to 'set_event_end_date' function.");
    return -1;
  }
  if (cmp_date(end_date, event->start_date) < 0) {
    log_error("End date is earlier than start date in 'set_event_end_date'.");
    return -2;
  }
  free_date(event->end_date);
  event->end_date = end_date;
  return 0;
}

int set_event_name(Event event, const char *name) {
  if (are_events_equal(event, NULL_EVENT)) {
    log_error("NULL pointer passed to 'set_event_name' function.");
    return -1;
  }
  char *temp = my_strdup(name);
  free(event->name);
  event->name = temp;
  return 0;
}
int set_event_type(Event event, EventType type) {
  if (are_events_equal(event, NULL_EVENT)) {
    log_error("NULL pointer passed to 'set_event_type' function.");
    return -1;
  }
  event->type = type;
  return 0;
}

// Function to print the details of an event
void print_event(ConstEvent event, ConstRoom assigned_room) {
  if (are_events_equal(event, NULL_EVENT)) {
    log_error("NULL pointer passed to 'print_event' function.");
    return;
  }
  printf(FORMAT_EVENT, event->id, event->name,
         stringhe_type_event[event->type]);
  puts("");
  if (assigned_room != NULL_ROOM) {
    printf("Sala: ");
    puts(get_room_name(assigned_room));
  }
  printf("Data inizio: ");
  print_date(event->start_date);
  puts("");
  printf("Data fine: ");
  print_date(event->end_date);
}

// Function to read an event from input
Event read_event(unsigned int event_id) {
  // Read event name
  char name[MAX_NAME_SIZE + 2] = {0};
  while (1) {
    char temp[MAX_NAME_SIZE + 2] = {0};
    printf("Inserisci nome evento [Max 100 caratteri]: ");
    if (read_line(temp, MAX_NAME_SIZE + 2)) {
      printf("Nome evento troppo lungo.\n");
      continue;
    }
    // trims leading and trailing whitespaces
    trim_whitespaces(name, temp, MAX_NAME_SIZE + 2);
    if (strlen(name) == 0) {
      continue;
    }
    break;
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

  // Read event start date
  Date start_date = NULL_DATE;
  do {
    printf("Inserisci data inizio evento (DD/MM/AAAA hh:mm): ");
    start_date = read_date();
  } while (start_date == NULL_DATE && printf("Data inserita non valida\n"));

  // Read event end date
  Date end_date = NULL_DATE;
  do {
    printf("Inserisci data fine evento (DD/MM/AAAA hh:mm): ");
    end_date = read_date();
  } while ((end_date == NULL_DATE || cmp_date(start_date, end_date) > 0) &&
           printf("Data inserita non valida\n"));

  // Return event
  Event event = new_event(type, name, start_date, end_date, event_id);
  return event;
}

// Function to check if two events overlap in time
bool do_events_overlap(ConstEvent event_a, ConstEvent event_b) {
  if (are_events_equal(event_a, NULL_EVENT)) {
    return false;
  }
  if (are_events_equal(event_b, NULL_EVENT)) {
    return false;
  }

  // Get the start and end dates of both events
  ConstDate start_a = get_event_start_date(event_a);
  ConstDate end_a = get_event_end_date(event_a);
  ConstDate start_b = get_event_start_date(event_b);
  ConstDate end_b = get_event_end_date(event_b);

  // Check if event_a overlaps with event_b
  bool part_a = cmp_date(start_b, start_a) <= 0 && cmp_date(start_a, end_b) < 0;

  // Check if event_b overlaps with event_a
  bool part_b = cmp_date(start_a, start_b) <= 0 && cmp_date(start_b, end_a) < 0;

  // Return true if there is any overlap, otherwise false
  return part_a || part_b;
}

// Function to check if two events are equal
int are_events_equal(ConstEvent event_a, ConstEvent event_b) {
  if (event_a == event_b) {
    return true;
  }
  // Check if both event pointers are not NULL and have the same ID
  return event_a != NULL_EVENT && event_b != NULL_EVENT &&
         event_a->id == event_b->id;
}

// Function to free the memory allocated for an event
void free_event(Event event) {
  free_date(event->start_date);
  free_date(event->end_date);
  free(event->name);
  free(event);
}

// Function to save an event to a file
void save_event_to_file(ConstEvent event, FILE *file) {
  if (file == NULL) {
    log_error("File pointer is NULL");
    return;
  }

  // Write event data to the file
  fprintf(file, "%u %u %u %s\n", event->id, event->type,
          event->assigned_room_id, event->name);

  // Save start date to file
  save_date_to_file(event->start_date, file);

  // Save end date to file
  save_date_to_file(event->end_date, file);
}

// Function to read an event from a file
Event read_event_from_file(FILE *file) {
  if (file == NULL) {
    log_error("File pointer is NULL");
    return NULL_EVENT;
  }

  unsigned int id = 0;
  unsigned int type = 0;
  unsigned int assigned_room_id = 0;
  char name[MAX_NAME_SIZE + 2];

  // Read event data from the file
  if (fscanf(file, "%u %u %u", &id, &type, &assigned_room_id) != 3) {
    clean_file(file);
    return NULL_EVENT;
  }
  (void)fgetc(file);
  read_line_from_file(name, MAX_NAME_SIZE + 2, file);

  // Read start date from file
  Date start_date = read_date_from_file(file);
  if (start_date == NULL_DATE) {
    return NULL_EVENT;
  }

  // Read end date from file
  Date end_date = read_date_from_file(file);
  if (end_date == NULL_DATE) {
    free_date(start_date); // Free allocated memory before returning NULL_EVENT
    return NULL_EVENT;
  }
  clean_file(file);

  // Create a new event object with the read data
  Event event = new_event(type, name, start_date, end_date, id);
  if (event != NULL_EVENT) {
    event->assigned_room_id = assigned_room_id;
  } else {
    free_date(start_date);
    free_date(end_date);
  }

  return event;
}
