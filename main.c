#include "event_bst.h"
#include <stdio.h>

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

int main(void) {
  BstEvent bst = new_event_bst();
  puts(WELCOME_MESSAGE);
  MenuChoice choice = 0;
  do {
    printf(MENU);
    (void)scanf("%d", &choice);
    switch (choice) {
    case ADD_EVENT:
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
