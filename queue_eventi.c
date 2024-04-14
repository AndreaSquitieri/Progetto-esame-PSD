#include "queue_eventi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_QUEUE_CAPACITY 16
#define GROWTH_FACTOR 2
#define CALC_POS(A, B) (A->head + B) % A->capacity
#define AT(A, B) A->vet[CALC_POS(A, B)]

typedef struct QueueEventiStruct {
  Evento *vet;
  size_t size;
  size_t capacity;
  size_t head, tail;
} QueueEventi_t;

QueueEventi new_queue_eventi(void) {
  QueueEventi queue = calloc(1, sizeof(*queue));

  if (queue == NULL) {
    return NULL;
  }
  queue->vet = calloc(INIT_QUEUE_CAPACITY, sizeof(Evento));

  if (queue->vet == NULL) {
    free(queue);
    return NULL;
  }

  queue->capacity = INIT_QUEUE_CAPACITY;
  queue->size = 0;
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

int enqueue_evento(QueueEventi queue, Evento val) {
  if (queue == NULL) {
    return -1;
  }

  if (queue->size == queue->capacity) {
    if (resize_buffer(queue, queue->capacity * GROWTH_FACTOR)) {
      return -2;
    }
  }

  queue->vet[queue->tail] = val;
  queue->tail = (queue->tail + 1) % queue->capacity;
  queue->size += 1;
  return 0;
}

Evento dequeue_evento(QueueEventi queue) {
  if (queue == NULL || queue->size == 0) {
    return NULL_EVENTO;
  }

  Evento result = AT(queue, 0);
  queue->head = (queue->head + 1) % queue->capacity;
  queue->size -= 1;
  return result;
}

Evento get_evento_at(QueueEventi queue, size_t index) {
  if (queue == NULL) {
    return NULL_EVENTO;
  }
  if (index >= queue->size) {
    return NULL_EVENTO;
  }
  // TODO -- Consideration
  // Should I return a copy or the original one?
  return AT(queue, index);
}

Evento remove_evento_at(QueueEventi queue, size_t index) {
  if (queue == NULL) {
    return NULL_EVENTO;
  }
  if (index >= queue->size) {
    return NULL_EVENTO;
  }
  Evento res = AT(queue, index);
  if (index <= queue->size / 2) {
    for (size_t i = index; i > 0; i--) {
      AT(queue, i) = AT(queue, i - 1);
    }
    queue->head = (queue->head + 1) % queue->capacity;
  } else {
    for (size_t i = index; i < (queue->size - 1); i++) {
      AT(queue, i) = AT(queue, i + 1);
    }
    queue->tail = (queue->tail + queue->capacity - 1) % queue->capacity;
  }
  queue->size -= 1;
  return res;
}

char *to_string_queue_eventi(ConstQueueEventi queue) {
  if (queue == NULL || queue->size == 0) {
    return NULL;
  }
  char *res = to_string_evento(AT(queue, 0));
  if (res == NULL) {
    return NULL;
  }
  size_t size = strlen(res);
  for (size_t i = 1; i < queue->size; i++) {
    char *to_cat = to_string_evento(AT(queue, i));
    if (to_cat == NULL) {
      free(res);
      return NULL;
    }
    size += strlen(to_cat) + 1;
    char *temp = realloc(res, (size + 1) * sizeof(char));
    if (temp == NULL) {
      free(res);
      free(to_cat);
      return NULL;
    }
    res = temp;
    strcat(strcat(res, "\n\n"), to_cat);
    free(to_cat);
  }
  return res;
}

void free_queue(QueueEventi queue) {
  while (!empty_queue_eventi(queue)) {
    free_evento(dequeue_evento(queue));
  }
  free(queue->vet);
  free(queue);
}
