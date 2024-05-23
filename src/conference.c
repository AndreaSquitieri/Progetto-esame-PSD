#include "conference.h"
#include "date.h"
#include "event_bst.h"
#include "logging.h"
#include "mevent.h"
#include "room.h"
#include "room_list.h"
#include "utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 102 // Define a maximum size constant

// Define the structure of a conference
struct ConferenceStruct {
  unsigned int event_id_counter; // Counter for event IDs
  unsigned int room_id_counter;  // Counter for room IDs
  EventBst bst;                  // Event binary search tree
  RoomList rooms;                // List of rooms
};

// Function to create a new conference
Conference new_conference(void) {
  // Create a new event binary search tree
  EventBst bst = new_event_bst();
  if (bst == NULL_EVENT_BST) {
    return NULL_CONFERENCE;
  }

  // Create a new list of rooms
  RoomList room_list = new_room_list();
  if (room_list == NULL_ROOM_LIST) {
    return NULL_CONFERENCE;
  }

  // Allocate memory for the conference structure
  Conference conf = my_alloc(1, sizeof(*conf));
  conf->bst = bst;
  conf->rooms = room_list;
  conf->event_id_counter = 0;
  conf->room_id_counter = NULL_ROOM_ID + 1;
  return conf;
}

// Function to add an event to the conference
int add_conference_event(Conference conf) {
  // Read an event with the current event ID counter
  Event event = read_event(conf->event_id_counter);
  if (event == NULL_EVENT) {
    return -1;
  }

  // Insert the event into the event binary search tree
  if (bst_insert_event(conf->bst, event)) {
    free_event(event);
    return -2;
  }

  // Increment the event ID counter
  conf->event_id_counter += 1;
  return 0;
}

// Function to add a room to the conference
int add_conference_room(Conference conf) {
  // Read a room with the current room ID counter
  Room room = read_room(conf->room_id_counter);
  if (room == NULL_ROOM) {
    return -1;
  }

  // Add the room to the list of rooms
  cons_room_list(conf->rooms, room);

  // Increment the room ID counter
  conf->room_id_counter += 1;
  return 0;
}

// Function to remove a room from the conference
int remove_conference_room(Conference conf) {
  // Check if there are rooms to remove
  if (get_size_room_list(conf->rooms) == 0) {
    puts("Non ci sono sale da rimuovere");
    return 1;
  }

  // Display the list of rooms
  print_room_list(conf->rooms);

  // Prompt the user to select a room to remove
  int pos = 0;
  do {
    printf("Inserire il numero della sala che si desidera rimuovere [Inserire "
           "un numero negativo per annullare l'operazione]: ");
    ResultInt res_room = read_int();
    if (res_room.error_code) {
      printf("Qualcosa è andato storto\n");
      return -2;
    }
    pos = res_room.value - 1;

  } while ((pos >= get_size_room_list(conf->rooms)) &&
           printf("Numero sala inseriro non valido\n"));
  if (pos < 0) {
    return 2;
  }

  // Remove the selected room from the list of rooms
  Room room = remove_at_room_list(conf->rooms, pos);
  free_room(room);
  return 0;
}

// Function to select an event from the conference
static int conference_select_event(Conference conf, const char *to_print) {
  // Print the list of events
  print_event_bst(conf->bst, conf->rooms);

  ResultInt res;
  while (1) {
    printf("%s", to_print);
    res = read_int();
    if (res.error_code) {
      printf("Valore inserito non valido\n");
      continue;
    }
    break;
  }
  return res.value;
}

// Function to remove an event from the conference
int remove_conference_event(Conference conf) {
  // Check if there are events to remove
  if (get_bst_size(conf->bst) == 0) {
    puts("Non ci sono eventi da rimuovere");
    return 1;
  }

  // Prompt the user to select an event to remove
  int res = conference_select_event(
      conf, "Inserisci l'id dell'evento da rimuovere [inserire un numero "
            "negativo "
            "per annullare l'operazione]: ");
  if (res < 0) {
    return 2; // Action aborted by the user
  }

  // Remove the selected event from the event binary search tree
  Event removed = bst_remove_event_by_id(conf->bst, res);
  if (removed == NULL_EVENT) {
    puts("Qualcosa è andato storto durante la rimozione dell'evento");
    return -1;
  }
  free_event(removed);
  printf("Evento correttamente rimosso\n");
  return 0;
}

// Function to free a room assigned to an event in the conference
int conference_free_event_room(Conference conf) {
  // Check if there are events with assigned rooms
  if (get_bst_size(conf->bst) == 0) {
    puts("Non ci sono sale assegnate");
    return 1;
  }

  // Prompt the user to select an event to free its room assignment
  int res =
      conference_select_event(conf, "Inserisci l'id dell'evento la cui sala si "
                                    "desidera liberare [inserire un numero "
                                    "negativo "
                                    "per annullare l'operazione]: ");
  if (res < 0) {
    return 2; // Action aborted by the user
  }

  // Retrieve the selected event
  Event event = bst_get_event_by_id(conf->bst, res);

  // Unassign the room from the event
  if (set_event_room_id(event, NULL_ROOM_ID)) {
    return -1;
  }
  return 0;
}

// Function to edit the title of an event in the conference
static int edit_conference_event_title(Conference conf, Event to_edit) {
  char name[MAXSIZE] = {0};
  while (1) {
    char temp[MAXSIZE] = {0};
    printf("Inserisci nome evento [Max 100 caratteri]: ");
    if (read_line(temp, MAXSIZE)) {
      printf("Nome evento troppo lungo.\n");
      continue;
    }
    // Trims leading whitespaces
    trim_whitespaces(name, temp, MAXSIZE);
    if (strlen(name) == 0) {
      continue;
    }
    break;
  }

  // Set the event's name
  if (set_event_name(to_edit, name)) {
    puts("Qualcosa è andato storto durante l'inserimento del nome dell'evento");
    return -1;
  }
  return 0;
}
// Function to edit the type of an event in the conference
static int edit_conference_event_type(Conference conf, Event to_edit) {
  int type = -1;
  while (!is_valid_event_type(type)) {
    printf(EVENT_TYPE_MENU);
    ResultInt res = read_int();
    if (res.error_code || res.value < 1 || res.value > 3) {
      puts("Valore inserito non valido");
      continue;
    }
    type = res.value - 1;
    break;
  }
  if (set_event_type(to_edit, type)) {
    puts("Qualcosa è andato storto durante l'inserimento del tipo dell'evento");
    return -1;
  }
  return 0;
}

// Function to check if two events are compatible
static bool are_events_compatible(Event event, va_list args) {
  Event second_event = va_arg(args, Event);
  Room room = va_arg(args, Room);
  RoomList room_list = va_arg(args, RoomList);
  if (are_events_equal(event, second_event)) {
    return true;
  }
  if (are_rooms_equal(NULL_ROOM, room)) {
    return true;
  }
  if (!are_rooms_equal(room,
                       get_room_by_id(room_list, get_event_room_id(event)))) {
    return true;
  }
  return !do_events_overlap(event, second_event);
}

// Function to edit the start date of an event in the conference
static int edit_conference_event_start_date(Conference conf, Event to_edit) {
  Date date = NULL_DATE;
  do {
    printf("Inserisci data inizio evento (DD/MM/AAAA hh:mm): ");
    date = read_date();
    if (date == NULL_DATE) {
      continue;
    }
    if (cmp_date(date, get_event_end_date(to_edit)) > 0) {
      free_date(date);
      date = NULL_DATE;
      continue;
    }
    Date old_date = copy_date(get_event_start_date(to_edit));
    if (set_event_start_date(to_edit, date)) {
      free_date(date);
      free_date(old_date);
      return -1;
    }
    Room room = get_room_by_id(conf->rooms, get_event_room_id(to_edit));
    if (!event_bst_every(conf->bst, are_events_compatible, to_edit, room,
                         conf->rooms)) {
      if (set_event_start_date(to_edit, old_date)) {
        free_date(old_date);
        return -2;
      }
      date = NULL_DATE;
      continue;
    }
  } while (date == NULL_DATE && printf("Data inserita non valida\n"));
  return 0;
}
// Function to edit the end date of an event in the conference
static int edit_conference_event_end_date(Conference conf, Event to_edit) {
  Date date = NULL_DATE;
  do {
    printf("Inserisci data fine evento (DD/MM/AAAA hh:mm): ");
    date = read_date();
    if (date == NULL_DATE) {
      continue;
    }
    if (cmp_date(date, get_event_start_date(to_edit)) < 0) {
      free_date(date);
      date = NULL_DATE;
      continue;
    }
    Date old_date = copy_date(get_event_end_date(to_edit));
    if (set_event_end_date(to_edit, date)) {
      free_date(date);
      free_date(old_date);
      return -1;
    }
    Room room = get_room_by_id(conf->rooms, get_event_room_id(to_edit));
    if (!event_bst_every(conf->bst, are_events_compatible, to_edit, room,
                         conf->rooms)) {
      if (set_event_end_date(to_edit, old_date)) {

        free_date(old_date);
        return -2;
      }
      date = NULL_DATE;
      continue;
    }
  } while (date == NULL_DATE && printf("Data inserita non valida\n"));
  return 0;
}
// Define the edit menu options
#define EDIT_MENU                                                              \
  "[1] Nome\n"                                                                 \
  "[2] Tipo\n"                                                                 \
  "[3] Data inizio\n"                                                          \
  "[4] Data fine\n"                                                            \
  "[5] Esci\n"                                                                 \
  "Selezionare cosa si desidera modificare: "

// Enumeration for edit menu choices
typedef enum {
  EDIT_EVENT_TITLE = 1,
  EDIT_EVENT_TYPE,
  EDIT_EVENT_START_DATE,
  EDIT_EVENT_END_DATE,
  EDIT_EVENT_EXIT
} EditMenuChoice;

// Function to edit an event in the conference
int edit_conference_event(Conference conf) {
  // Check if there are events to edit
  if (get_bst_size(conf->bst) == 0) {
    printf("Non ci sono eventi da modificare\n");
    return 0;
  }

  // Prompt the user to select an event to edit
  int res = conference_select_event(
      conf, "Inserisci l'id dell'evento da modificare [inserire un numero "
            "negativo "
            "per annullare l'operazione]: ");
  if (res < 0) {
    return 1; // Action aborted by the user
  }

  // Remove the selected event from the event binary search tree
  Event to_edit = bst_remove_event_by_id(conf->bst, res);
  if (to_edit == NULL_EVENT) {
    printf("Qualcosa è andato storto durante la ricerca dell'evento\n");
    return -1;
  }

  int flag = 1;
  while (flag) {
    printf(EDIT_MENU);
    ResultInt res = read_int();
    if (res.error_code || res.value < 1 || res.value > EDIT_EVENT_EXIT) {
      puts("Valore inserito non valido");
      continue;
    }
    switch ((EditMenuChoice)res.value) {
    case EDIT_EVENT_TITLE: {
      edit_conference_event_title(conf, to_edit);
    } break;
    case EDIT_EVENT_TYPE: {
      edit_conference_event_type(conf, to_edit);
    } break;
    case EDIT_EVENT_START_DATE: {
      if (edit_conference_event_start_date(conf, to_edit)) {
        printf("Qualcosa è andato storto durante la modifica della data di "
               "inizio dell'evento\n");
      }
    } break;
    case EDIT_EVENT_END_DATE: {
      if (edit_conference_event_end_date(conf, to_edit)) {
        printf("Qualcosa è andato storto durante la modifica della data di "
               "fine dell'evento\n");
      }
      break;
    }
    case EDIT_EVENT_EXIT:
      flag = 0;
      break;
    }
    if (flag) {
      printf("\n\n");
      Room room = get_room_by_id(conf->rooms, get_event_room_id(to_edit));
      print_event(to_edit, room);
      printf("\n\n");
    }
  }

  // Insert the modified event back into the event binary search tree
  if (bst_insert_event(conf->bst, to_edit)) {
    free_event(to_edit);
    puts("Qualcosa è andato storto durante la modifica dell'evento");
    return -1;
  }
  puts("Evento correttamente modificato");
  return 0;
}

// Function to display the conference schedule
void display_conference_schedule(ConstConference conf) {
  if (get_bst_size(conf->bst) == 0) {
    puts("Non ci sono eventi da visualizzare");
    return;
  }
  print_event_bst(conf->bst, conf->rooms);
}

// Function to display the conference rooms
void display_conference_rooms(ConstConference conf) {
  if (get_size_room_list(conf->rooms) == 0) {
    puts("Non ci sono sale da visualizzare");
    return;
  }
  print_room_list(conf->rooms);
}

// Function to assign an event to a room in the conference
int conference_assign_event_to_room(Conference conf) {
  if (get_size_room_list(conf->rooms) == 0) {
    puts("Non ci sono sale da assegnare");
    return 0;
  }
  if (get_bst_size(conf->bst) == 0) {
    puts("Non ci sono eventi a cui assegnare una sala");
    return 0;
  }
  int res = 0;
  Event to_assign = NULL_EVENT;
  do {
    res = conference_select_event(
        conf, "Inserisci l'id dell'evento da assegnare [inserire un numero "
              "negativo "
              "per annullare l'operazione]: ");
    if (res < 0) {
      return 1; // Action aborted by the user
    }
    to_assign = bst_get_event_by_id(conf->bst, res);

  } while (to_assign == NULL_EVENT &&
           printf("Qualcosa è andato storto durante la ricerca dell'evento\n"));
  print_room_list(conf->rooms);
  int pos = 0;
  do {
    printf("Inserisci numero sala: ");
    ResultInt res_room = read_int();
    if (res_room.error_code) {
      printf("Qualcosa è andato storto\n");
      return -2;
    }
    pos = res_room.value - 1;

  } while ((pos < 0 || pos >= get_size_room_list(conf->rooms)) &&
           printf("Numero sala inseriro non valido\n"));

  Room room = get_at_room_list(conf->rooms, pos);
  if (room == NULL_ROOM) {
    printf("Qualcosa è andato storto durante la ricerca della sala\n");
    return -3;
  }
  if (!event_bst_every(conf->bst, are_events_compatible, to_assign, room,
                       conf->rooms)) {
    printf("Non è possible assegnare la sala all'evento\n");
    return 2;
  }

  set_event_room_id(to_assign, get_room_id(room));
  printf("Sala assegnata con successo\n");

  return 0;
}

// Function to free the memory allocated for a conference
void free_conference(Conference conf) {
  free_event_bst(conf->bst);
  free_room_list(conf->rooms);
  free(conf);
}

// Function to save conference data to a file
void save_conference_to_file(ConstConference conf, FILE *file) {
  if (conf == NULL_CONFERENCE || file == NULL) {
    log_error("Invalid conference or file pointer");
    return;
  }

  // Save event ID counter and room ID counter
  fprintf(file, "%u %u\n", conf->event_id_counter, conf->room_id_counter);

  // Save events
  save_event_bst_to_file(conf->bst, file);

  // Save rooms
  save_room_list_to_file(conf->rooms, file);
}

// Function to save conference data to a file in a sorted manner
void save_conference_to_file_sorted(ConstConference conf, FILE *file) {
  if (conf == NULL_CONFERENCE || file == NULL) {
    log_error("Invalid conference or file pointer");
    return;
  }

  // Save event ID counter and room ID counter
  fprintf(file, "%u %u\n", conf->event_id_counter, conf->room_id_counter);

  // Save events
  save_event_bst_to_file_sorted(conf->bst, file);

  // Save rooms
  save_room_list_to_file(conf->rooms, file);
}

// Function to read conference data from a file
Conference read_conference_from_file(FILE *file) {
  if (file == NULL) {
    log_error("Invalid file pointer");
    return NULL_CONFERENCE;
  }

  // Read event ID counter and room ID counter
  unsigned int event_id_counter = 0;
  unsigned int room_id_counter = 0;
  if (fscanf(file, "%u %u", &event_id_counter, &room_id_counter) != 2) {
    log_error("Error reading event ID counter and room ID counter");
    return NULL_CONFERENCE;
  }
  clean_file(file);

  // Create a new conference
  Conference conf = new_conference();
  if (conf == NULL_CONFERENCE) {
    log_error("Error creating new conference");
    return NULL_CONFERENCE;
  }

  conf->event_id_counter = event_id_counter;
  conf->room_id_counter = room_id_counter;

  // Read events
  conf->bst = read_event_bst_from_file(file);
  if (conf->bst == NULL_EVENT_BST) {
    log_error("Error reading events");
    free_conference(conf);
    return NULL_CONFERENCE;
  }

  // Read rooms
  conf->rooms = read_room_list_from_file(file);
  if (conf->rooms == NULL_ROOM_LIST) {
    log_error("Error reading rooms");
    free_conference(conf);
    return NULL_CONFERENCE;
  }

  return conf;
}
