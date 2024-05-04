#include "event_list.h"
#include "mevent.h"
#include "utils.h"
#include <stdlib.h>
#include <sys/cdefs.h>

#define INIT_CAPACITY 16
#define GROWTH_FACTOR 2

struct EventListStruct {
  Event *array;
  size_t capacity;
  size_t size;
};

static void event_list_increase_capacity(EventList list) {
  list->capacity *= GROWTH_FACTOR;
  list->array = my_realloc(list->array, list->capacity, sizeof(Event));
}

EventList new_event_list(void) {
  EventList new_list = my_alloc(1, sizeof(*new_list));
  new_list->array = my_alloc(INIT_CAPACITY, sizeof(Event));
  new_list->capacity = INIT_CAPACITY;
  new_list->size = 0;
  return new_list;
}

int is_event_list_empty(EventList list) {
  return list == NULL || list->size == 0 || list->array == NULL;
}

void cons_event_list(EventList list, Event value) {
  if (list == NULL) {
    return;
  }
  if (list->capacity == list->size) {
    event_list_increase_capacity(list);
  }
  list->array[list->size] = value;
  list->size += 1;
}

Event tail_event_list(EventList list) {
  if (is_event_list_empty(list)) {
    return NULL;
  }
  list->size -= 1;
  return list->array[list->size];
}

Event get_first_event_list(EventList list) {
  if (is_event_list_empty(list)) {
    return NULL_EVENT;
  }
  return list->array[list->size - 1];
}
