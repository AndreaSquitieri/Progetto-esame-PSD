#include "evento.h"
#include "logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct EventoStruct {
  TipoEvento tipo;
  char *nome;
  Data data;
} Evento_t;

Evento new_evento(TipoEvento tipo, const char *nome, ConstData data) {
  Evento nuovo_evento = calloc(1, sizeof(*nuovo_evento));
  if (nuovo_evento == NULL) {
    log_error("Allocazione oggetto 'evento' fallita.");
    return NULL;
  }
  nuovo_evento->data = copy_data(data);
  if (nuovo_evento->data == NULL) {
    log_error("Allocazione oggetto 'nuovo_evento->data' fallita.");
    free(nuovo_evento);
    return NULL;
  }
  nuovo_evento->nome = strdup(nome);
  if (nuovo_evento->nome == NULL) {
    log_error("Allocazione oggetto 'nuovo_evento->nome' fallita.");
    free_data(nuovo_evento->data);
    free(nuovo_evento);
    return NULL;
  }
  nuovo_evento->tipo = tipo;
  return nuovo_evento;
}

Evento copy_evento(ConstEvento evento) {
  if (evento == NULL) {
    return NULL;
  }
  return new_evento(evento->tipo, evento->nome, evento->data);
}

Data get_data(ConstEvento evento) {
  if (evento == NULL) {
    return NULL;
  }
  return copy_data(evento->data);
}
char *get_nome(ConstEvento evento) {
  if (evento == NULL) {
    return NULL;
  }
  return strdup(evento->nome);
}
TipoEvento get_tipo_evento(ConstEvento evento) {
  if (evento == NULL) {
    return -1;
  }
  return evento->tipo;
}

int set_data(Evento evento, const Data data) {
  if (evento == NULL) {
    log_error("Passato puntatore NULL alla funzione 'set_data'.");
    return -1;
  }
  Data temp = copy_data(data);
  if (temp == NULL) {
    log_error("Copia di 'data' in 'set_data' fallita.");
    return -1;
  }
  evento->data = temp;
  return 0;
}
int set_nome(Evento evento, const char *nome) {
  if (evento == NULL) {
    log_error("Passato puntatore NULL alla funzione 'set_nome'.");
    return -1;
  }
  char *temp = strdup(nome);
  if (temp == NULL) {
    log_error("Copia di 'nome' in 'set_nome' fallita.");
    return -1;
  }
  evento->nome = temp;
  return 0;
}
int set_tipo_evento(Evento evento, TipoEvento tipo) {
  if (evento == NULL) {
    log_error("Passato puntatore NULL alla funzione 'qset_tipo_evento'.");
    return -1;
  }
  evento->tipo = tipo;
  return 0;
}

static const char *const stringhe_tipo_evento[] = {
    "Workshop", "Sessione di keynote", "Panel di discussione"};

#define FORMAT_EVENTO                                                          \
  "Evento: \"%s\"\n"                                                           \
  "Tipo: %s\n"                                                                 \
  "Data: %s"

char *to_string_evento(ConstEvento evento) {
  const char *str_tipo = stringhe_tipo_evento[evento->tipo];

  char *str_data = to_string_data(evento->data);
  if (str_data == NULL) {
    log_error("Allocazione oggetto 'str_data' fallita.");
    return NULL;
  }

  int len = snprintf(NULL, 0, FORMAT_EVENTO, evento->nome, str_tipo, str_data);

  char *str_res = calloc(len + 1, sizeof(char));
  if (str_res == NULL) {
    log_error("Allocazione oggetto 'str_res' fallita.");
    return NULL;
  }

  if (snprintf(str_res, len + 1, FORMAT_EVENTO, evento->nome, str_tipo,
               str_data) < 0) {
    log_error("Creazione 'stringa evento' fallita.");
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
