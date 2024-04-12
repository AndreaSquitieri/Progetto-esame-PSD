#include "evento.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum c_tipo_evento { WORKSHOP = 0, KEYNOTE, PANEL } tipo_evento;

static const char *stringhe_tipo_evento[] = {"Workshop", "Sessione di keynote",
                                             "Panel di discussione"};

typedef struct c_evento {
  tipo_evento tipo;
  char *nome;
  data data;
} evento_t;

evento nuovo_evento(tipo_evento tipo, char *nome, data data) {
  evento nevento = calloc(1, sizeof(evento_t));
  if (nevento == NULL) {
    fprintf(stderr, "[ERRORE]: Allocazione oggetto 'evento' fallita.\n");
    return NULL;
  }
  nevento->data = copia_data(data);
  nevento->nome = strdup(nome);
  nevento->tipo = tipo;
  return nevento;
}

void set_tipo_evento(evento ev, tipo_evento tipo) { ev->tipo = tipo; }
void set_data(evento ev, data d) { ev->data = copia_data(d); }
void set_nome(evento ev, char *nome) { ev->nome = strdup(nome); }

char *stringa_evento(evento ev) {
  char *str_data = stringa_data(ev->data);
  char *str_tipo = stringhe_tipo_evento[ev->tipo];
  // TODO
}

void free_evento(evento ev) {
  free_data(ev->data);
  free(ev->nome);
  free(ev);
}
