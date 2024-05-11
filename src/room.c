#include "room.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 102

struct RoomStruct {
  unsigned int id;
  char *name;
};

Room new_room(const char *name, unsigned int id) {
  Room room = my_alloc(1, sizeof(*room));
  room->name = my_strdup(name);
  room->id = id;

  return room;
}

Room copy_room(ConstRoom room) {
  Room room_copy = my_alloc(1, sizeof(*room));
  room_copy->name = my_strdup(room->name);
  room_copy->id = room->id;
  return room_copy;
}

bool is_room_equal(ConstRoom room_a, ConstRoom room_b) {
  if (room_a == room_b) {
    return true;
  }
  return room_a != NULL_ROOM && room_b != NULL_ROOM && room_a->id == room_b->id;
}

Room read_room(unsigned int id) {

  printf("Inserisci nome sala [Max 100 caratteri]: ");
  char name[MAXSIZE] = {0};
  if (read_line(name, MAXSIZE)) {
    return NULL_ROOM;
  }
  Room room = new_room(name, id);
  return room;
}

const char *get_room_name(ConstRoom room) { return room->name; }

#define FORMAT_ROOM "%s"
void print_room(ConstRoom room) { printf(FORMAT_ROOM, room->name); }

void free_room(Room room) {
  free(room->name);
  free(room);
}

// Function to save a Room structure to a file
void save_room_to_file(ConstRoom room, FILE *file) {
  if (room == NULL || file == NULL) {
    return;
  }

  // Write Room data to the file
  fprintf(file, "%u\n", room->id);   // Write room ID
  fprintf(file, "%s\n", room->name); // Write room name
}

// Function to read a Room structure from a file
Room read_room_from_file(FILE *file) {
  if (file == NULL) {
    return NULL_ROOM;
  }

  // Read room ID from the file
  unsigned int id;
  if (fscanf(file, "%u", &id) != 1) {
    clean_file(file); // Clean the file buffer
    return NULL_ROOM;
  }

  clean_file(file); // Clean the file buffer

  // Read room name from the file
  char name[MAXSIZE];
  if (read_line_from_file(name, MAXSIZE, file) != 0) {
    return NULL_ROOM;
  }

  // Create and return a new Room structure
  return new_room(name, id);
}

unsigned int get_room_id(ConstRoom room) { return room->id; }
