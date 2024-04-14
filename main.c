#include "queue_eventi.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  QueueEventi queue = new_queue_eventi();
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
  Data data = new_data(minuti, ora, giorno, mese, anno);
  if (data == NULL) {
    printf("Errore data\n");
  }
  for (int i = 0; i < 5; i++) {
    Evento event = new_evento(tipo, temp, data);
    if (event == NULL) {
      printf("Errore evento\n");
    }
    enqueue_evento(queue, event);
  }
  free_data(data);
  char *printable = to_string_queue_eventi(queue);
  if (printable != NULL) {
    printf("%s\n", printable);
    free(printable);
  }
  puts("");
  puts("I love you from the bottom of my heart.");
  puts("");
  remove_evento_at(queue, 3);

  printable = to_string_queue_eventi(queue);
  if (printable != NULL) {
    printf("%s\n", printable);
    free(printable);
  }

  free_queue(queue);
  return 0;
}
