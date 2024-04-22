#include "date.h"
#include "event_bst.h"
#include "mevent.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define WELCOME_MESSAGE "Benvenuto nel gestore di eventi per conferenze!"

typedef enum {
  ADD_EVENT = 1,
  REMOVE_EVENT,
  MODIFY_EVENT,
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

#define MAXSIZE 101

#define EVENT_TYPE_MENU                                                        \
  "\nTipologie Evento\n"                                                       \
  "[1]: Workshop\n"                                                            \
  "[2]: Sessione di keynote\n"                                                 \
  "[3]: Panel di discussione\n"                                                \
  "Seleziona tipologia evento (1, 2 o 3): "

int main(void) {
  EventBst bst = new_event_bst();
  puts(WELCOME_MESSAGE);
  MenuChoice choice = 0;
  do {
    printf(MENU);
    (void)scanf("%d", &choice);
    while (getchar() != '\n')
      ;
    puts("");

    switch (choice) {
    case ADD_EVENT:
      printf("Inserisci nome evento [Max 100 caratteri]: ");
      char name[MAXSIZE] = {0};
      // TODO
      // Handle better this thing
      if (fgets(name, MAXSIZE, stdin) == NULL) {
        return -1;
      }
      name[strcspn(name, "\n")] = '\0';
      int type = 0;
      do {
        printf(EVENT_TYPE_MENU);
        scanf("%d", &type);
        while (getchar() != '\n')
          ;
        type -= 1;
      } while ((type < 0 || type > 2) &&
               printf("Valore inserito non valido\n"));
      Date date = NULL;
      do {
        int day = 0;
        int month = 0;
        int year = 0;
        int hour = 0;
        int minutes = 0;
        printf("Inserisci data evento (DD/MM/AAAA hh:mm): ");
        scanf("%d/%d/%d %d:%d", &day, &month, &year, &hour, &minutes);
        while (getchar() != '\n')
          ;
        date = new_date(minutes, hour, day, month, year);
      } while (date == NULL && printf("Data inserita non valida\n"));
      Event event = new_event(type, name, date);
      bst_insert_event(bst, event);
      break;
    case REMOVE_EVENT:
      break;
    case MODIFY_EVENT:
      break;
    case DISPLAY_SCHEDULE:
      print_event_bst(bst);
      break;
    case ASSIGN_ROOM:
      break;
    case EXIT:
      break;
    }

  } while (choice != EXIT);
  free_event_bst(bst);
  return 0;
}
