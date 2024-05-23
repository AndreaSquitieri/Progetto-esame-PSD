#include "room.h"
#include "logging.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOM_NAME_SIZE 100 // Define the maximum size of the room name
#define FORMAT_ROOM                                                            \
  "Nome: %s\n"                                                                 \
  "Posti: %u"

// Definition of the structure to represent a room
struct RoomStruct {
  unsigned int id;       // ID of the room
  char *name;            // Name of the room
  unsigned int capacity; // Capacity of the room (number of seats)
};

// Function to create a new room
Room new_room(const char *name, unsigned int id, unsigned int capacity) {
  // Check if the room name is valid
  if (name == NULL || strlen(name) == 0) {
    log_error("Attempt to create a room with invalid name.");
    return NULL_ROOM;
  }
  // Allocate memory for the new room
  Room room = my_alloc(1, sizeof(*room));
  // Copy the room name into the room structure
  room->name = my_strdup(name);
  // Set the ID and capacity of the room
  room->id = id;
  room->capacity = capacity;

  return room;
}

// Function to copy a room
Room copy_room(ConstRoom room) {
  // Check if the room is valid
  if (are_rooms_equal(room, NULL_ROOM)) {
    log_error("Attempt to copy a NULL room.");
    return NULL_ROOM;
  }
  // Allocate memory for the room copy
  Room room_copy = my_alloc(1, sizeof(*room));
  // Copy the name, ID, and capacity of the room into the new room structure
  room_copy->name = my_strdup(room->name);
  room_copy->id = room->id;
  room_copy->capacity = room->capacity;
  return room_copy;
}

// Function to check equality between two rooms
bool are_rooms_equal(ConstRoom room_a, ConstRoom room_b) {
  // Check if the two rooms are identical or have the same ID
  if (room_a == room_b) {
    return true;
  }
  return room_a != NULL_ROOM && room_b != NULL_ROOM && room_a->id == room_b->id;
}

// Function to get the ID of a room
unsigned int get_room_id(ConstRoom room) {
  // Check if the room is valid and return its ID
  if (are_rooms_equal(room, NULL_ROOM)) {
    log_error("Attempt to get ID of a NULL room.");
    return NULL_ROOM_ID;
  }
  return room->id;
}

// Function to get the name of a room
const char *get_room_name(ConstRoom room) {
  // Check if the room is valid and return its name
  if (are_rooms_equal(room, NULL_ROOM)) {
    log_error("Attempt to get name of a NULL room.");
    return NULL;
  }
  return room->name;
}

// Function to print the details of a room
void print_room(ConstRoom room) {
  // Check if the room is valid and print its name and capacity
  if (are_rooms_equal(room, NULL_ROOM)) {
    log_error("Attempt to print a NULL room.");
    return;
  }
  printf(FORMAT_ROOM, room->name, room->capacity);
}

// Function to read a new room from input
Room read_room(unsigned int id) {
  // Variable to store the room name read from input
  char name[MAX_ROOM_NAME_SIZE + 2] = {0};
  // Loop until a valid name for the room is read
  while (1) {
    char temp[MAX_ROOM_NAME_SIZE + 2] = {0};
    printf("Inserisci nome sala [Max %d caratteri]: ", MAX_ROOM_NAME_SIZE);
    // Read the room name from input
    if (read_line(temp, MAX_ROOM_NAME_SIZE + 2)) {
      printf("Errore durante la lettura del nome.\n");
      continue;
    }
    // Remove leading and trailing whitespaces from the name read
    trim_whitespaces(name, temp, MAX_ROOM_NAME_SIZE + 2);
    // If the name is empty, request new input
    if (strlen(name) == 0) {
      continue;
    }
    break;
  }
  // Read the capacity of the room from input
  ResultInt res = {0};
  do {
    printf("Inserisci numero posti sala: ");
    res = read_int();

  } while (res.error_code || res.value < 0);
  // Create a new room with the name and capacity read from input
  Room room = new_room(name, id, res.value);
  return room;
}

// Function to save the details of a room to a file
void save_room_to_file(ConstRoom room, FILE *file) {
  // Check if the room and file are valid
  if (are_rooms_equal(room, NULL_ROOM)) {
    log_error("Attempt to save NULL room to file.");
    return;
  }

  if (file == NULL) {
    log_error("Attempt to write room to NULL file.");
    return;
  }

  // Write the ID, name, and capacity of the room to the file
  fprintf(file, "%u\n", room->id);
  fprintf(file, "%s\n", room->name);
  fprintf(file, "%u\n", room->capacity);
}

// Function to read the details of a room from a file
Room read_room_from_file(FILE *file) {
  // Check if the file is valid
  if (file == NULL) {
    log_error("Attempt to read room from NULL file.");
    return NULL_ROOM;
  }

  // Declare and initialize variables to store the ID, name, and capacity of
  // the room read from the file
  unsigned int id = 0;
  if (fscanf(file, "%u", &id) != 1) {
    log_error("Failed to read room ID from file.");
    clean_file(file);
    return NULL_ROOM;
  }

  clean_file(file);

  char name[MAX_ROOM_NAME_SIZE + 2];
  if (read_line_from_file(name, MAX_ROOM_NAME_SIZE + 2, file) != 0) {
    log_error("Failed to read room name from file.");
    return NULL_ROOM;
  }

  unsigned int capacity = 0;
  if (fscanf(file, "%u", &capacity) != 1) {
    log_error("Failed to read room capacity from file.");
    clean_file(file);
    return NULL_ROOM;
  }

  // Create a new room with the ID, name, and capacity read from the file
  return new_room(name, id, capacity);
}

// Function to free the memory allocated for a room
void free_room(Room room) {
  if (are_rooms_equal(room, NULL_ROOM)) {
    log_error("Attempt to free a NULL room.");
    return;
  }
  // Free the memory allocated for the room name and then for the room itself
  free(room->name);
  free(room);
}
