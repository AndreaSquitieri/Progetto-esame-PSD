#include "utils.h"
#include "mevent.h"
#include <stdio.h>
#include <string.h>

#define MAXSIZE 101

#define EVENT_TYPE_MENU                                                        \
  "\nTipologie Evento\n"                                                       \
  "[1]: Workshop\n"                                                            \
  "[2]: Sessione di keynote\n"                                                 \
  "[3]: Panel di discussione\n"                                                \
  "Seleziona tipologia evento (1, 2 o 3): "

Event read_event() {
  printf("Inserisci nome evento [Max 100 caratteri]: ");
  char name[MAXSIZE] = {0};
  // TODO
  // Handle better this thing
  if (fgets(name, MAXSIZE, stdin) == NULL) {
    return NULL;
  }
  name[strcspn(name, "\n")] = '\0';
  int type = 0;
  do {
    printf(EVENT_TYPE_MENU);
    scanf("%d", &type);
    while (getchar() != '\n')
      ;
    type -= 1;
  } while ((type < 0 || type > 2) && printf("Valore inserito non valido\n"));
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
  return event;
}
