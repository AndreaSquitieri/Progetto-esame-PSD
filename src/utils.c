#include "utils.h"
#include "mevent.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 101
#define MAXINTSIZE 13

void clean_stdin(void) {
  int temp = 0;
  while ((temp = getchar()) != '\n' && temp != EOF)
    ;
}

int read_line(char *line, int size) {
  if (fgets(line, size, stdin) == NULL) {
    clean_stdin();
    return -1;
  }
  if (line[strlen(line) - 1] != '\n') {
    clean_stdin();
    return -2;
  }
  line[strcspn(line, "\n")] = '\0';
  return 0;
}

ResultInt read_int(void) {
  ResultInt res = {0};
  int choice = 0;
  char temp[MAXINTSIZE] = {0};
  if (read_line(temp, MAXINTSIZE)) {
    res.error_code = -1;
    return res;
  }
  char *endptr = NULL;
  errno = 0;
  choice = strtol(temp, &endptr, 10);
  if ((errno == ERANGE) || (errno != 0 && choice == 0)) {
    perror("strtol");
    res.error_code = -2;
    return res;
  }
  if (endptr == temp) {
    res.error_code = -3;
    return res;
  }
  res.value = choice;
  return res;
}

Event read_event(void) {
  printf("Inserisci nome evento [Max 100 caratteri]: ");
  fflush(stdout);
  char name[MAXSIZE] = {0};
  if (read_line(name, MAXSIZE)) {
    return NULL;
  }
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
