#ifndef EVENTO_H_
#define EVENTO_H_
#include "data.h"

#define NULL_EVENTO NULL

typedef struct EventoStruct *Evento;
typedef const struct EventoStruct *ConstEvento;

typedef enum { WORKSHOP = 0, KEYNOTE, PANEL } TipoEvento;

Evento new_evento(TipoEvento tipo, const char *nome, Data data);
Evento copy_evento(ConstEvento evento);
int set_tipo_evento(Evento evento, TipoEvento tipo);
int set_data(Evento evento, Data data);
int set_nome(Evento evento, const char *nome);
TipoEvento get_tipo_evento(ConstEvento evento);
Data get_data(ConstEvento evento);
char *get_nome(ConstEvento evento);
char *to_string_evento(ConstEvento evento);
void free_evento(Evento evento);

#endif // EVENTO_H_
