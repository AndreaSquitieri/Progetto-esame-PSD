#include "conference.h"
#include "event_bst.h"
#include "mevent.h"
#include "room.h"
#include "room_list.h"
#include "utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 102

struct ConferenceStruct {
  unsigned int event_id_counter;
  unsigned int room_id_counter;
  EventBst bst;
  RoomList rooms;
};

Conference new_conference(void) {
  EventBst bst = new_event_bst();
  if (bst == NULL_EVENT_BST) {
    return NULL_CONFERENCE;
  }
  RoomList room_list = new_room_list();
  if (room_list == NULL_ROOM_LIST) {
    return NULL_CONFERENCE;
  }
  Conference conf = my_alloc(1, sizeof(*conf));
  conf->bst = bst;
  conf->rooms = room_list;
  conf->event_id_counter = 0;
  conf->room_id_counter = NULL_ROOM_ID + 1;
  return conf;
}

int add_conference_event(Conference conf) {
  Event event = read_event(conf->event_id_counter);
  if (event == NULL_EVENT) {
    return -1;
  }
  if (bst_insert_event(conf->bst, event)) {
    free_event(event);
    return -2;
  }
  conf->event_id_counter += 1;
  return 0;
}

int add_conference_room(Conference conf) {
  Room room = read_room(conf->room_id_counter);
  if (room == NULL_ROOM) {
    return -1;
  }
  cons_room_list(conf->rooms, room);
  conf->room_id_counter += 1;
  return 0;
}

static int conference_select_event(Conference conf, const char *to_print) {
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

int remove_conference_event(Conference conf) {
  int res = conference_select_event(
      conf, "Inserisci l'id dell'evento da rimuovere [inserire un numero "
            "negativo "
            "per annullare l'operazione]: ");
  if (res < 0) {
    return 1; // Action aborted by the user
  }
  Event removed = bst_remove_event_by_id(conf->bst, res);
  if (removed == NULL_EVENT) {
    puts("Qualcosa è andato storto durante la rimozione dell'evento");
    return -1;
  }
  free_event(removed);
  printf("Evento correttamente rimosso\n");
  return 0;
}

static int edit_conference_event_title(Conference conf, Event to_edit) {
  char temp[MAXSIZE];
  printf("Inserisci nome evento [Max 100 caratteri]: ");
  if (read_line(temp, sizeof(temp))) {
    puts("Nome inserito non valido");
    return -1;
  }
  if (set_event_name(to_edit, temp)) {
    puts("Qualcosa è andato storto durante l'inserimento del nome dell'evento");
    return -1;
  }
  return 0;
}

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

static int edit_conference_event_start_date(Conference conf, Event to_edit) {
  Date date = NULL_DATE;
  do {
    printf("Inserisci data inizio evento (DD/MM/AAAA hh:mm): ");
    date = read_date();
  } while (date == NULL_DATE && printf("Data inserita non valida\n"));
  return set_event_start_date(to_edit, date);
}

static int edit_conference_event_end_date(Conference conf, Event to_edit) {
  Date date = NULL_DATE;
  do {
    printf("Inserisci data fine evento (DD/MM/AAAA hh:mm): ");
    date = read_date();
  } while (date == NULL_DATE && printf("Data inserita non valida\n"));
  return set_event_end_date(to_edit, date);
}

#define EDIT_MENU                                                              \
  "[1] Nome\n"                                                                 \
  "[2] Tipo\n"                                                                 \
  "[3] Data inizio\n"                                                          \
  "[4] Data fine\n"                                                            \
  "[5] Esci\n"                                                                 \
  "Selezionare cosa si desidera modificare: "

typedef enum {
  EDIT_EVENT_TITLE = 1,
  EDIT_EVENT_TYPE,
  EDIT_EVENT_START_DATE,
  EDIT_EVENT_END_DATE,
  EDIT_EVENT_EXIT
} EditMenuChoice;

int edit_conference_event(Conference conf) {
  int res = conference_select_event(
      conf, "Inserisci l'id dell'evento da modificare [inserire un numero "
            "negativo "
            "per annullare l'operazione]: ");
  if (res < 0) {
    return 1; // Action aborted by the user
  }
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
  if (bst_insert_event(conf->bst, to_edit)) {
    free_event(to_edit);
    puts("Qualcosa è andato storto durante la modifica dell'evento");
    return -1;
  }
  puts("Evento correttamente modificato");
  return 0;
}

int display_conference_schedule(ConstConference conf) {
  print_event_bst(conf->bst, conf->rooms);
  return 0;
}
int display_conference_rooms(ConstConference conf) {
  print_room_list(conf->rooms);
  return 0;
}

static bool are_events_compatible(Event event, va_list args) {
  Event second_event = va_arg(args, Event);
  Room room = va_arg(args, Room);
  RoomList room_list = va_arg(args, RoomList);
  if (is_event_equal(event, second_event)) {
    return true;
  }
  if (!is_room_equal(room,
                     get_room_by_id(room_list, get_event_room_id(event)))) {
    return true;
  }
  return !do_events_overlap(event, second_event);
}

int conference_assign_event_to_room(Conference conf) {
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
  if (!bst_for_all(conf->bst, are_events_compatible, to_assign, room,
                   conf->rooms)) {
    printf("Non è possible assegnare la sala all'evento\n");
    return 2;
  }

  set_event_room_id(to_assign, get_room_id(room));
  printf("Sala assegnata con successo\n");

  return 0;
}

void free_conference(Conference conf) {
  free_event_bst(conf->bst);
  free_room_list(conf->rooms);
  free(conf);
}

void save_conference_to_file(ConstConference conf, FILE *file) {
  if (conf == NULL_CONFERENCE || file == NULL) {
    perror("Invalid conference or file pointer");
    return;
  }

  // Save event ID counter and room ID counter
  fprintf(file, "%u %u\n", conf->event_id_counter, conf->room_id_counter);

  // Save events
  save_event_bst_to_file(conf->bst, file);

  // Save rooms
  save_room_list_to_file(conf->rooms, file);
}

Conference read_conference_from_file(FILE *file) {
  if (file == NULL) {
    perror("Invalid file pointer");
    return NULL_CONFERENCE;
  }

  // Read event ID counter and room ID counter
  unsigned int event_id_counter = 0;
  unsigned int room_id_counter = 0;
  if (fscanf(file, "%u %u", &event_id_counter, &room_id_counter) != 2) {
    perror("Error reading event ID counter and room ID counter");
    return NULL_CONFERENCE;
  }
  clean_file(file);

  // Create a new conference
  Conference conf = new_conference();
  if (conf == NULL_CONFERENCE) {
    perror("Error creating new conference");
    return NULL_CONFERENCE;
  }

  conf->event_id_counter = event_id_counter;
  conf->room_id_counter = room_id_counter;

  // Read events
  conf->bst = read_event_bst_from_file(file);
  if (conf->bst == NULL_EVENT_BST) {
    perror("Error reading events");
    free_conference(conf);
    return NULL_CONFERENCE;
  }

  // Read rooms
  conf->rooms = read_room_list_from_file(file);
  if (conf->rooms == NULL_ROOM_LIST) {
    perror("Error reading rooms");
    free_conference(conf);
    return NULL_CONFERENCE;
  }

  return conf;
}
