#include "room_list.h"
#include "room.h"
#include "utils.h"
#include <stdlib.h>

#define INIT_CAPACITY 16
#define GROWTH_FACTOR 2

struct RoomListStruct {
  Room *array;
  int capacity;
  int size;
};

static void room_list_increase_capacity(RoomList list) {
  list->capacity *= GROWTH_FACTOR;
  list->array = my_realloc(list->array, list->capacity, sizeof(Room));
}

RoomList new_room_list(void) {
  RoomList new_list = my_alloc(1, sizeof(*new_list));
  new_list->array = my_alloc(INIT_CAPACITY, sizeof(Room));
  new_list->capacity = INIT_CAPACITY;
  new_list->size = 0;
  return new_list;
}

bool is_room_list_empty(RoomList list) {
  return list == NULL || list->size == 0 || list->array == NULL;
}

void cons_room_list(RoomList list, Room room) {
  if (list->capacity == list->size) {
    room_list_increase_capacity(list);
  }
  list->array[list->size] = room;
  list->size += 1;
}

Room tail_room_list(RoomList list) {
  if (is_room_list_empty(list)) {
    return NULL_ROOM;
  }
  list->size -= 1;
  return list->array[list->size];
}

Room get_first_room_list(RoomList list) { return get_at_room_list(list, 0); }

int get_size_room_list(RoomList list) { return list->size; }

int get_pos_room_list(RoomList list, Room to_search) {
  for (int i = 0; i < list->size; i++) {
    if (is_room_equal(list->array[i], to_search)) {
      return i;
    }
  }
  return -1;
}

Room get_at_room_list(RoomList list, int pos) {
  if (pos >= list->size || pos < 0) {
    return NULL_ROOM;
  }
  return list->array[pos];
}

void free_room_list(RoomList list) {
  for (int i = 0; i < list->size; i++) {
    free_room(list->array[i]);
  }
  free(list->array);
  free(list);
}
