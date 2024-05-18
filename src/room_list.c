#include "room_list.h"
#include "room.h"
#include "utils.h"
#include <stdio.h>
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
Room remove_at_room_list(RoomList list, int pos) {
  if (pos >= list->size || pos < 0) {
    return NULL_ROOM;
  }
  Room temp = list->array[pos];
  list->size -= 1;
  for (int i = pos; i < list->size; i++) {
    list->array[i] = list->array[i + 1];
  }
  return temp;
}

void print_room_list(RoomList list) {
  for (int i = 0; i < list->size; i++) {
    printf("[Sala %d]\n"
           "Nome: ",
           i + 1);
    print_room(list->array[i]);
    puts("");
  }
}

void free_room_list(RoomList list) {
  for (int i = 0; i < list->size; i++) {
    free_room(list->array[i]);
  }
  free(list->array);
  free(list);
}

// Function to save a room list to a file
void save_room_list_to_file(ConstRoomList list, FILE *file) {
  if (file == NULL) {
    perror("File pointer is NULL");
    return;
  }

  // Write the number of rooms in the list to the file
  fprintf(file, "%d\n", list->size);

  // Write each room in the list to the file
  for (int i = 0; i < list->size; i++) {
    save_room_to_file(list->array[i], file);
  }
}

// Function to read a room list from a file
RoomList read_room_list_from_file(FILE *file) {
  if (file == NULL) {
    perror("File pointer is NULL");
    return NULL;
  }

  int num_rooms = 0;

  if (fscanf(file, "%d", &num_rooms) != 1) {
    clean_file(file);
    return NULL;
  }

  RoomList list = new_room_list();
  if (list == NULL) {
    return NULL;
  }

  for (int i = 0; i < num_rooms; i++) {
    Room room = read_room_from_file(file);
    if (room == NULL_ROOM) {
      free_room_list(list);
      return NULL;
    }
    cons_room_list(list, room);
  }

  return list;
}

Room get_room_by_id(RoomList list, unsigned int room_id) {
  if (list == NULL_ROOM_LIST) {
    return NULL_ROOM;
  }
  for (int i = 0; i < list->size; i++) {
    Room current_room = list->array[i];
    if (get_room_id(current_room) == room_id) {
      return current_room;
    }
  }
  return NULL_ROOM;
}
