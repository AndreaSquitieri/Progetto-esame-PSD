#include "event_bst.h"
#include "utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WELCOME_MESSAGE "Benvenuto nel gestore di eventi per conferenze!"
#define MAXSIZE 101

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

int read_choice(void) {
  int choice = 0;
  char temp[MAXSIZE] = {0};
  if (fgets(temp, sizeof(temp), stdin) == NULL) {
    return -1;
  }
  char *endptr = NULL;
  errno = 0;
  choice = strtol(temp, &endptr, 10);
  if ((errno == ERANGE && (choice < 1 || choice > EXIT)) ||
      (errno != 0 && choice == 0)) {
    perror("strtol");
    return -1;
  }
  if (endptr == temp) {
    return -1;
  }
  return choice;
}

int main(void) {
  EventBst bst = new_event_bst();
  puts(WELCOME_MESSAGE);
  MenuChoice choice = 0;
  do {

    printf(MENU);
    int temp = read_choice();
    if (temp == -1) {
      continue;
    }
    choice = temp;

    puts("");

    switch (choice) {
    case ADD_EVENT:
      Event event = read_event();
      if (event == NULL) {
        continue;
      }
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
