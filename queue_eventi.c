#include "queue_eventi.h"
#include <stdio.h>
#include <stdlib.h>

#define INIT_QUEUE 16

typedef struct QueueEventiStruct {
  Evento *vet;
  size_t size;
  size_t capacity;
  size_t head, tail;
} QueueEventi_t;

QueueEventi new_queue_eventi(void) {
  QueueEventi queue = malloc(sizeof(*queue));

  if (queue == NULL) {
    return NULL;
  }
  queue->vet = malloc(INIT_QUEUE * sizeof(Evento));

  if (queue->vet == NULL) {
    free(queue);
    return NULL;
  }

  queue->size = 0;
  queue->capacity = INIT_QUEUE;
  queue->head = 0;
  queue->tail = 0;
  return queue;
}

int empty_queue_eventi(ConstQueueEventi queue) {
  if (queue == NULL) {
    return -1;
  }
  return (queue->size == 0);
}

static int resize_buffer(QueueEventi queue, size_t new_size) {
  if (new_size < queue->capacity) {
    return -1;
  }
  Evento *new_buffer = calloc(new_size, sizeof(Evento));
  if (new_buffer == NULL) {
    return -2;
  }
  for (size_t i = queue->head, j = 0; j < queue->size; i++, j++) {
    new_buffer[j] = queue->vet[i % queue->capacity];
  }

  queue->capacity = new_size;
  queue->head = 0;
  queue->tail = queue->size;

  free(queue->vet);
  queue->vet = new_buffer;

  return 0;
}

int enqueue_evento(QueueEventi queue, const Evento val) {
  if (queue == NULL) {
    return -1;
  }

  if (queue->size == queue->capacity) {
    if (resize_buffer(queue, queue->capacity * 2)) {
      return -2;
    }
  }

  queue->vet[queue->tail] = copy_evento(val);
  queue->tail = (queue->tail + 1) % queue->capacity;
  (queue->size)++;
  return 0;
}

Evento dequeue_evento(QueueEventi queue)

{
  if (queue == NULL || queue->size == 0) {
    return NULL_EVENTO;
  }

  Evento result = queue->vet[queue->head];
  queue->head = (queue->head + 1) % queue->capacity;
  queue->size -= 1;
  return result;
}

void free_queue(QueueEventi queue) {
  while (!empty_queue_eventi(queue)) {
    free_evento(dequeue_evento(queue));
  }
  free(queue);
}
