#include "room.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 102

struct RoomStruct {
  char *name;
};

Room new_room(const char *name) {
  Room room = my_alloc(1, sizeof(*room));
  room->name = my_strdup(name);

  return room;
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
