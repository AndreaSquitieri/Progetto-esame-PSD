#ifndef QUEUE_EVENTI_H_
#define QUEUE_EVENTI_H_
#include "evento.h"
#include <stddef.h>

typedef struct QueueEventiStruct *QueueEventi;
typedef const struct QueueEventiStruct *ConstQueueEventi;

QueueEventi new_queue_eventi(void);
int empty_queue_eventi(ConstQueueEventi queue);
Evento dequeue_evento(QueueEventi queue);
int enqueue_evento(QueueEventi queue, Evento evento);
Evento get_evento_at(QueueEventi queue, size_t index);
Evento remove_evento_at(QueueEventi queue, size_t index);
void free_queue(QueueEventi queue);
char *to_string_queue_eventi(ConstQueueEventi queue);

#endif // QUEUE_EVENTI_H_
