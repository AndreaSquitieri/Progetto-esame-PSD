#include "room.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 102

static unsigned int room_id_counter = 0;

struct RoomStruct {
  unsigned int id;
  char *name;
};

void init_room_id_counter(unsigned int id) { room_id_counter = id; }

unsigned int get_room_id_counter(void) { return room_id_counter; }

Room new_room(const char *name) {
  Room room = my_alloc(1, sizeof(*room));
  room->name = my_strdup(name);
  room->id = room_id_counter;
  room_id_counter += 1;

  return room;
}

Room copy_room(ConstRoom room) {
  Room room_copy = my_alloc(1, sizeof(*room));
  room_copy->name = my_strdup(room->name);
  room_copy->id = room->id;
  return room_copy;
}

bool is_room_equal(ConstRoom room_a, ConstRoom room_b) {
  return room_a == room_b;
}

Room read_room(void) {

  printf("Inserisci nome sala [Max 100 caratteri]: ");
  char name[MAXSIZE] = {0};
  if (read_line(name, MAXSIZE)) {
    return NULL_ROOM;
  }
  Room room = new_room(name);
  return room;
}

const char *get_room_name(ConstRoom room) { return room->name; }

#define FORMAT_ROOM "%s"
void print_room(ConstRoom room) { printf(FORMAT_ROOM, room->name); }

void free_room(Room room) {
  free(room->name);
  free(room);
}
