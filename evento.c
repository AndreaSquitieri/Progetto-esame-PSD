#include "evento.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct EventoStruct {
  TipoEvento tipo;
  char *nome;
  Data data;
} Evento_t;

Evento nuovo_evento(TipoEvento tipo, char *nome, Data data) {
  Evento nuovo_evento = calloc(1, sizeof(Evento_t));
  if (nuovo_evento == NULL) {
    (void)fprintf(stderr, "[ERRORE]: Allocazione oggetto 'evento' fallita.\n");
    return NULL;
  }
  nuovo_evento->data = copia_data(data);
  nuovo_evento->nome = strdup(nome);
  nuovo_evento->tipo = tipo;
  return nuovo_evento;
}

void set_tipo_evento(Evento evento, TipoEvento tipo) { evento->tipo = tipo; }
void set_data(Evento evento, Data data) { evento->data = copia_data(data); }
void set_nome(Evento evento, char *nome) { evento->nome = strdup(nome); }

#define FORMAT_EVENTO                                                          \
  "Evento: \"%s\"\n"                                                           \
  "Tipo: %s\n"                                                                 \
  "Data: %s"

static const char *const stringhe_tipo_evento[] = {
    "Workshop", "Sessione di keynote", "Panel di discussione"};

char *stringa_evento(Evento evento) {
  const char *str_tipo = stringhe_tipo_evento[evento->tipo];

  char *str_data = stringa_data(evento->data);
  if (str_data == NULL) {
    (void)fprintf(stderr,
                  "[ERRORE]: Allocazione oggetto 'str_data' fallita.\n");
    return NULL;
  }

  int len = snprintf(NULL, 0, FORMAT_EVENTO, evento->nome, str_tipo, str_data);

  char *str_res = calloc(len + 1, sizeof(char));
  if (str_res == NULL) {
    (void)fprintf(stderr, "[ERRORE]: Allocazione oggetto 'str_res' fallita.\n");
    return NULL;
  }

  if (snprintf(str_res, len, FORMAT_EVENTO, evento->nome, str_tipo, str_data) <
      0) {
    (void)fprintf(stderr, "[ERRORE]: Creazione 'stringa evento' fallita.\n");
    free(str_data);
    free(str_res);
    return NULL;
  }

  free(str_data);
  return str_res;
}

void free_evento(Evento evento) {
  free_data(evento->data);
  free(evento->nome);
  free(evento);
}
