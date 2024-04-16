#include "event_queue.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  EventQueue queue = new_event_queue();
  char temp[100];
  printf("Inserire nuovo evento\n");
  printf("Inserire nome: ");
  (void)scanf("%s", temp);
  printf("Inserire tipo [0, 1, 2]: ");
  int tipo = 0;
  (void)scanf("%d", &tipo);
  printf("Inserire data (gg/mm/aaaa hh:mm): ");
  unsigned int giorno = 0;
  unsigned int mese = 0;
  unsigned int anno = 0;
  unsigned int ora = 0;
  unsigned int minuti = 0;
  (void)scanf("%d/%d/%d %d:%d", &giorno, &mese, &anno, &ora, &minuti);
  for (int i = 0; i < 5; i++) {
    Date date = new_date((minuti + i) % 60, ora, giorno, mese, anno);
    if (date == NULL) {
      printf("Errore data\n");
    }
    Event event = new_event(tipo, temp, date);
    if (event == NULL) {
      printf("Errore evento\n");
    }
    enqueue_event(queue, event);
    free_date(date);
  }
  char *printable = to_string_event_queue(queue);
  if (printable != NULL) {
    printf("%s\n", printable);
    free(printable);
  }
  puts("");
  puts("I love you from the bottom of my heart.");
  puts("");
  remove_event_at(queue, 3);

  printable = to_string_event_queue(queue);
  if (printable != NULL) {
    printf("%s\n", printable);
    free(printable);
  }

  free_queue(queue);
  return 0;
}
