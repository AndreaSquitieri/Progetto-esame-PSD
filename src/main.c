#include "event_bst.h"
#include "mevent.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WELCOME_MESSAGE "Benvenuto nel gestore di eventi per conferenze!"
#define MAXSIZE 101

typedef enum {
  ADD_EVENT = 1,
  REMOVE_EVENT,
  EDIT_EVENT,
  DISPLAY_SCHEDULE,
  ASSIGN_ROOM,
  EXIT
} MenuChoice;

#define MENU                                                                   \
  "\nGestore di eventi per conferenze\n"                                       \
  "[1]: Aggiungi evento\n"                                                     \
  "[2]: Rimuovi evento\n"                                                      \
  "[3]: Modifica evento\n"                                                     \
  "[4]: Mostra eventi\n"                                                       \
  "[5]: Assegna stanza\n"                                                      \
  "[6]: Esci\n"                                                                \
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

void helper_remove_event(EventBst bst) {
  print_event_bst(bst);
  // TODO
  // Alternatively I could make the user insert date and name of the event
  // but it doesn´t seem like good ux
  ResultInt res;
  while (1) {
    printf("Inserisci l'id dell'evento da rimuovere [inserire un numero "
           "negativo "
           "per annullare l'operazione]: ");
    res = read_int();
    if (res.error_code) {
      printf("Valore inserito non valido\n");
      continue;
    }
    break;
  }
  if (res.value < 0) {
    return;
  }
  Event removed = bst_remove_event_by_id(bst, res.value);
  if (removed == NULL) {
    printf("Qualcosa è andato storto durante la rimozione dell'evento\n");
    return;
  }
  free(removed);
  printf("Evento correttamente rimosso\n");
}

#define EDIT_MENU                                                              \
  "[1] Nome\n"                                                                 \
  "[2] Tipo\n"                                                                 \
  "[3] Data\n"                                                                 \
  "[4] Esci\n"                                                                 \
  "Selezionare cosa si desidera modificare: "

typedef enum {
  EDIT_EVENT_TITLE = 1,
  EDIT_EVENT_TYPE,
  EDIT_EVENT_DATE,
  EDIT_EVENT_EXIT
} EditMenuChoice;

void helper_edit_event(EventBst bst) {
  print_event_bst(bst);
  ResultInt res;
  while (1) {
    printf("Inserisci l'id dell'evento da modificare [inserire un numero "
           "negativo "
           "per annullare l'operazione]: ");
    res = read_int();
    if (res.error_code) {
      printf("Valore inserito non valido\n");
      continue;
    }
    break;
  }
  if (res.value < 0) {
    return;
  }
  Event to_edit = bst_remove_event_by_id(bst, res.value);
  if (to_edit == NULL) {
    printf("Qualcosa è andato storto durante la ricerca dell'evento\n");
    return;
  }
  // TODO
  // I have to actually implement the part where I edit the event
  while (1) {
    printf(EDIT_MENU);
    ResultInt res = read_int();
    if (res.error_code || res.value < 1 || res.value > 4) {
      puts("Valore inserito non valido");
      continue;
    }
    EditMenuChoice edit_choice = res.value;
    switch (edit_choice) {
    case EDIT_EVENT_TITLE: {
      char temp[MAXSIZE];
      if (read_line(temp, sizeof(temp))) {
        // TODO
        // IDK, check somewhere else to see what to do
        continue;
      }
      if (set_event_name(to_edit, temp)) {
        // TODO
        // Just tell the user that something went wrong, try to be consistent
      }
    } break;
    case EDIT_EVENT_TYPE: {
      int type = 0;
      while (1) {
        printf(EVENT_TYPE_MENU);
        ResultInt res = read_int();
        if (res.error_code || res.value < 1 || res.value > 3) {
          // TODO
          // Tell the user that something went wrong
          continue;
        }
        type -= 1;
      }
      if (set_type_event(to_edit, type)) {
        // TODO
        // tell the user that something went wrong
        continue;
      }
    } break;
    case EDIT_EVENT_DATE: {
      Date date = NULL;
      do {
        int day = 0;
        int month = 0;
        int year = 0;
        int hour = 0;
        int minutes = 0;
        printf("Inserisci data evento (DD/MM/AAAA hh:mm): ");
        // TODO
        // Improve this implementation
        scanf("%d/%d/%d %d:%d", &day, &month, &year, &hour, &minutes);
        while (getchar() != '\n')
          ;
        date = new_date(minutes, hour, day, month, year);
      } while (date == NULL && printf("Data inserita non valida\n"));
      set_event_date(to_edit, date);
      free(date);
    } break;
    case EDIT_EVENT_EXIT:
      // TODO
      // Don't really know what to do here, just make it better than it is now
      break;
    }
    // TODO
    // Yeah you have to do some more things, be careful
    break;
  }
  bst_insert_event(bst, to_edit);
  printf("Evento correttamente modificato\n");
}

int main(void) {
  EventBst bst = new_event_bst();
  puts(WELCOME_MESSAGE);
  MenuChoice choice = 0;
  do {

    printf(MENU);
    int temp = read_menu_choice();
    if (temp == -1) {
      continue;
    }
    choice = temp;

    puts("");

    switch (choice) {
    case ADD_EVENT: {
      Event event = read_event();
      if (event == NULL) {
        continue;
      }
      bst_insert_event(bst, event);
    } break;
    case REMOVE_EVENT:
      helper_remove_event(bst);
      break;
    case EDIT_EVENT:
      helper_edit_event(bst);
      break;
    case DISPLAY_SCHEDULE:
      print_event_bst(bst);
      break;
    case ASSIGN_ROOM:
      // TODO
      // I still don't know what I should do in this section, but I guess that
      // we'll find out
      break;
    case EXIT:
      break;
    }

  } while (choice != EXIT);
  free_event_bst(bst);
  return 0;
}
