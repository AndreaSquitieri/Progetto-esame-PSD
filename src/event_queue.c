#include "event_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_QUEUE_CAPACITY 16
#define GROWTH_FACTOR 2

#define CALC_POS(A, B) ((A)->head + (B)) % (A)->capacity
#define AT(A, B) (A)->vet[CALC_POS(A, B)]

struct EventQueueStruct {
  Event *vet;
  size_t size;
  size_t capacity;
  size_t head, tail;
};

/// Enlarges the buffer contained in the queue
static int resize_buffer(EventQueue queue, size_t new_size) {
  if (new_size < queue->capacity) {
    return -1;
  }
  Event *new_buffer = calloc(new_size, sizeof(Event));
  if (new_buffer == NULL) {
    return -2;
  }
  for (size_t j = 0; j < queue->size; j++) {
    new_buffer[j] = AT(queue, j);
  }

  queue->capacity = new_size;
  queue->head = 0;
  queue->tail = queue->size;

  free(queue->vet);
  queue->vet = new_buffer;

  return 0;
}

EventQueue new_event_queue(void) {
  EventQueue queue = calloc(1, sizeof(*queue));

  if (queue == NULL) {
    return NULL;
  }
  queue->vet = calloc(INIT_QUEUE_CAPACITY, sizeof(Event));

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

int empty_event_queue(ConstEventQueue queue) {
  if (queue == NULL) {
    return -1;
  }
  return (queue->size == 0);
}

int enqueue_event(EventQueue queue, Event event) {
  if (queue == NULL) {
    return -1;
  }
  if (event == NULL) {
    return -2;
  }
  if (queue->size == queue->capacity) {
    if (resize_buffer(queue, queue->capacity * GROWTH_FACTOR)) {
      return -3;
    }
  }

  queue->vet[queue->tail] = event;
  queue->tail = (queue->tail + 1) % queue->capacity;
  queue->size += 1;
  return 0;
}

Event dequeue_event(EventQueue queue) {
  if (queue == NULL || queue->size == 0) {
    return NULL_EVENT;
  }

  Event result = AT(queue, 0);
  queue->head = (queue->head + 1) % queue->capacity;
  queue->size -= 1;
  return result;
}

Event get_event_at(EventQueue queue, size_t index) {
  if (queue == NULL) {
    return NULL_EVENT;
  }
  if (index >= queue->size) {
    return NULL_EVENT;
  }
  // TODO -- Consideration
  // Should I return a copy or the original one?
  return AT(queue, index);
}

Event remove_event_at(EventQueue queue, size_t index) {
  if (queue == NULL) {
    return NULL_EVENT;
  }
  if (index >= queue->size) {
    return NULL_EVENT;
  }
  Event res = AT(queue, index);
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

#define SEPARATOR "\n\n"
void print_event_queue(ConstEventQueue queue) {
  if (queue == NULL || queue->size == 0) {
    return;
  }
  for (size_t i = 0; i < queue->size; i++) {
    print_event(AT(queue, 0));
    printf(SEPARATOR);
  }
}

void free_queue(EventQueue queue) {
  while (!empty_event_queue(queue)) {
    free_event(dequeue_event(queue));
  }
  free(queue->vet);
  free(queue);
}
