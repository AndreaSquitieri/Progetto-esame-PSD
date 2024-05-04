#include "event_list.h"
#include "mevent.h"
#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <sys/cdefs.h>

#define INIT_CAPACITY 16
#define GROWTH_FACTOR 2

struct EventListStruct {
  Event *array;
  int capacity;
  int size;
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

bool is_event_list_empty(EventList list) {
  return list == NULL || list->size == 0 || list->array == NULL;
}

void cons_event_list(EventList list, Event value) {
  if (list->capacity == list->size) {
    event_list_increase_capacity(list);
  }
  list->array[list->size] = value;
  list->size += 1;
}

Event tail_event_list(EventList list) {
  if (is_event_list_empty(list)) {
    return NULL_EVENT;
  }
  list->size -= 1;
  return list->array[list->size];
}

Event get_first_event_list(EventList list) {
  return get_at_event_list(list, 0);
}

int get_size_event_list(EventList list) { return list->size; }

int get_pos_event_list(EventList list, Event to_search) {
  for (int i = 0; i < list->size; i++) {
    if (is_event_equal(list->array[i], to_search)) {
      return i;
    }
  }
  return -1;
}

Event get_at_event_list(EventList list, int pos) {
  if (pos >= list->size || pos < 0) {
    return NULL_EVENT;
  }
  return list->array[pos];
}

int insert_event_list(EventList list, int pos, Event event) {
  if (pos > list->size || pos < 0) {
    return -1;
  }
  if (list->capacity == list->size) {
    event_list_increase_capacity(list);
  }
  for (int i = list->size; i > pos; i--) {
    list->array[i] = list->array[i - 1];
  }
  list->array[pos] = event;
  list->size += 1;
  return 0;
}

Event remove_event_list(EventList list, int pos) {
  if (pos >= list->size || pos < 0) {
    return NULL_EVENT;
  }
  Event to_remove = list->array[pos];
  list->size -= 1;
  for (int i = pos; i < list->size; i++) {
    list->array[i] = list->array[i + 1];
  }
  return to_remove;
}

void free_event_list(EventList list) {
  if (list != NULL) {
    free(list->array);
    free(list);
  }
}
