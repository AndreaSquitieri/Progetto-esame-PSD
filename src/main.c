#include "conference.h"
#include "logging.h"
#include "utils.h"
#include <stdio.h>

#define WELCOME_MESSAGE "Benvenuto nel gestore di eventi per conferenze!"

typedef enum {
  ADD_EVENT = 1,
  REMOVE_EVENT,
  EDIT_EVENT,
  DISPLAY_SCHEDULE,
  ADD_ROOM,
  DISPLAY_ROOMS,
  ASSIGN_ROOM,
  EXIT
} MenuChoice;

#define MENU                                                                   \
  "\nGestore di eventi per conferenze\n"                                       \
  "[1]: Aggiungi evento\n"                                                     \
  "[2]: Rimuovi evento\n"                                                      \
  "[3]: Modifica evento\n"                                                     \
  "[4]: Mostra eventi\n"                                                       \
  "[5]: Aggiungi sala\n"                                                       \
  "[6]: Mostra sale\n"                                                         \
  "[7]: Assegna sala ad evento\n"                                              \
  "[8]: Esci\n"                                                                \
  "Indicare l'operazione che si desidera effetuare: "

int read_menu_choice(void) {
  ResultInt res = read_int();
  if (res.error_code) {
    return -1;
  }
  if (res.value < 1 || res.value > EXIT) {
    return -1;
  }
  return res.value;
}

int main(int argc, char **argv) {
  char *filename = "conf.txt";
  if (argc > 1) {
    filename = argv[1];
  }

  FILE *conf_file = fopen(filename, "r");
  Conference conf = NULL_CONFERENCE;
  if (conf_file == NULL) {
    conf = new_conference();
  } else {
    conf = read_conference_from_file(conf_file);
    (void)fclose(conf_file);
  }
  if (conf == NULL_CONFERENCE) {
    conf = new_conference();
  }
  if (conf == NULL_CONFERENCE) {
    log_error("Creazione della conferenza fallita");
    return -1;
  }
  puts(WELCOME_MESSAGE);
  MenuChoice choice = 0;
  do {
    printf(MENU);
    int temp = read_menu_choice();
    if (temp == -1) {
      puts("Opzione inserita non valida");
      continue;
    }
    choice = temp;
    puts("");
    switch (choice) {
    case ADD_EVENT: {
      add_conference_event(conf);
    } break;
    case REMOVE_EVENT:
      remove_conference_event(conf);
      break;
    case EDIT_EVENT:
      edit_conference_event(conf);
      break;
    case DISPLAY_SCHEDULE:
      display_conference_schedule(conf);
      break;
    case ADD_ROOM:
      add_conference_room(conf);
      break;
    case DISPLAY_ROOMS: {
      display_conference_rooms(conf);
      break;
    }
    case ASSIGN_ROOM: {
      conference_assign_event_to_room(conf);
      break;
    }
    case EXIT:
      break;
    }
  } while (choice != EXIT);

  conf_file = fopen(filename, "w");
  if (conf_file == NULL) {
    log_error("Impossibile aprire il file in scrittura");
    return -2;
  }
  save_conference_to_file(conf, conf_file);
  (void)fclose(conf_file);

  free_conference(conf);
  return 0;
}
