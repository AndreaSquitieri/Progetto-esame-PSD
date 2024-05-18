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
  unsigned int capacity;
};

Room new_room(const char *name, unsigned int id, unsigned int capacity) {
  Room room = my_alloc(1, sizeof(*room));
  room->name = my_strdup(name);
  room->id = id;
  room->capacity = capacity;

  return room;
}

Room copy_room(ConstRoom room) {
  Room room_copy = my_alloc(1, sizeof(*room));
  room_copy->name = my_strdup(room->name);
  room_copy->id = room->id;
  room_copy->capacity = room->capacity;
  return room_copy;
}

bool is_room_equal(ConstRoom room_a, ConstRoom room_b) {
  if (room_a == room_b) {
    return true;
  }
  return room_a != NULL_ROOM && room_b != NULL_ROOM && room_a->id == room_b->id;
}

Room read_room(unsigned int id) {

  char name[MAXSIZE] = {0};
  while (1) {
    char temp[MAXSIZE] = {0};
    printf("Inserisci nome sala [Max 100 caratteri]: ");
    if (read_line(temp, MAXSIZE)) {
      printf("Nome sala troppo lungo.\n");
      continue;
    }
    // trims leading whitespaces

    trim_whitespaces(name, temp, MAXSIZE);
    if (strlen(name) == 0) {

      continue;
    }
    break;
  }

  printf("Inserisci numero posti sala: ");
  ResultInt res = read_int();
  if (res.error_code || res.value < 0) {
    return NULL_ROOM;
  }
  Room room = new_room(name, id, res.value);
  return room;
}

const char *get_room_name(ConstRoom room) { return room->name; }

#define FORMAT_ROOM                                                            \
  "Nome: %s\n"                                                                 \
  "Posti: %u"
void print_room(ConstRoom room) {
  printf(FORMAT_ROOM, room->name, room->capacity);
}

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
  fprintf(file, "%u\n", room->id);       // Write room ID
  fprintf(file, "%s\n", room->name);     // Write room name
  fprintf(file, "%u\n", room->capacity); // Write room capacity
}

// Function to read a Room structure from a file
Room read_room_from_file(FILE *file) {
  if (file == NULL) {
    return NULL_ROOM;
  }

  // Read room ID from the file
  unsigned int id = 0;
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

  // Read room capacity from the file
  unsigned int capacity = 0;
  if (fscanf(file, "%u", &capacity) != 1) {
    clean_file(file); // Clean the file buffer
    return NULL_ROOM;
  }

  // Create and return a new Room structure
  return new_room(name, id, capacity);
}

unsigned int get_room_id(ConstRoom room) { return room->id; }
