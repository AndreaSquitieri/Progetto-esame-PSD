#ifndef EVENTO_H_
#define EVENTO_H_
#include "data.h"

typedef struct EventoStruct *Evento;

typedef enum { WORKSHOP = 0, KEYNOTE, PANEL } TipoEvento;

Evento nuovo_evento(TipoEvento tipo, char *nome, Data data);
void set_tipo_evento(Evento evento, TipoEvento tipo);
void set_data(Evento evento, Data data);
void set_nome(Evento evento, char *nome);
char *stringa_evento(Evento evento);
void free_evento(Evento evento);

#endif // EVENTO_H_
