#include "room_list.h"
#include "logging.h"
#include "room.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

#define INIT_CAPACITY 8 // Initial capacity of the list
#define GROWTH_FACTOR 2 // Growth factor for resizing the array

// Structure representing a list of rooms
struct RoomListStruct {
  Room *array;  // Dynamic array of rooms
  int capacity; // Current capacity of the array
  int size;     // Number of rooms currently in the list
};

// Static function to increase the capacity of the list
static void room_list_increase_capacity(RoomList list) {
  list->capacity *= GROWTH_FACTOR; // Double the capacity
  list->array = my_realloc(list->array, list->capacity, sizeof(Room));
}

// Function to create a new list of rooms
RoomList new_room_list(void) {
  RoomList new_list =
      my_alloc(1, sizeof(*new_list)); // Allocate memory for the list structure
  new_list->array = my_alloc(
      INIT_CAPACITY, sizeof(Room));   // Allocate memory for the array of rooms
  new_list->capacity = INIT_CAPACITY; // Set the initial capacity
  new_list->size = 0;                 // Initialize the size to 0
  return new_list;
}

// Function to check if the list is empty
bool is_room_list_empty(ConstRoomList list) {
  return list == NULL || list->size == 0; // Check if the list is NULL or empty
}

// Function to get the size of the list
int get_size_room_list(ConstRoomList list) {
  if (list == NULL_ROOM_LIST) { // Check if the list is NULL
    log_error("Attempt to get size of a NULL room list.");
    return 0;
  }
  return list->size; // Return the size of the list
}

// Function to add a room to the list
void cons_room_list(RoomList list, Room room) {
  if (list == NULL_ROOM_LIST ||
      room == NULL_ROOM) { // Check if the list or the room is NULL
    log_error("Attempt to add a room to a NULL room list or add a NULL room.");
    return;
  }
  if (list->capacity == list->size) {  // Check if the capacity is exhausted
    room_list_increase_capacity(list); // Increase the capacity of the list
  }
  list->array[list->size] = room; // Add the room to the list
  list->size += 1;                // Increment the size of the list
}

// Function to remove the last room from the list and return it
Room tail_room_list(RoomList list) {
  if (is_room_list_empty(list)) { // Check if the list is empty
    log_error("Attempt to remove a room from an empty or NULL room list.");
    return NULL_ROOM;
  }
  list->size -= 1;                // Decrement the size of the list
  return list->array[list->size]; // Return the last room
}

// Function to get the first room of the list
Room get_first_room_list(RoomList list) {
  return get_at_room_list(list,
                          0); // Use get_at_room_list to get the first room
}

// Function to get a room at a specific position in the list
Room get_at_room_list(RoomList list, int pos) {
  if (list == NULL_ROOM_LIST) { // Check if the list is NULL
    log_error("Attempt to get a room from a NULL room list.");
    return NULL_ROOM;
  }
  if (pos >= list->size || pos < 0) { // Check if the position is valid
    log_error("Attempt to get a room at an invalid position.");
    return NULL_ROOM;
  }
  return list->array[pos]; // Return the room at the specified position
}

// Function to get a room by ID from the list
Room get_room_by_id(RoomList list, unsigned int room_id) {
  if (list == NULL_ROOM_LIST) { // Check if the list is NULL
    log_error("Attempt to get a room by ID from a NULL room list.");
    return NULL_ROOM;
  }
  for (int i = 0; i < list->size; i++) { // Iterate over the rooms in the list
    Room current_room = list->array[i];
    if (get_room_id(current_room) == room_id) { // Compare the IDs of the rooms
      return current_room;                      // Return the found room
    }
  }
  return NULL_ROOM; // Return NULL_ROOM if the room is not found
}

// Function to remove a room at a specific position in the list
Room remove_at_room_list(RoomList list, int pos) {
  if (list == NULL_ROOM_LIST) { // Check if the list is NULL
    log_error("Attempt to remove a room from a NULL room list.");
    return NULL_ROOM;
  }
  if (pos >= list->size || pos < 0) { // Check if the position is valid
    log_error("Attempt to remove a room at an invalid position.");
    return NULL_ROOM;
  }
  Room temp = list->array[pos]; // Save the room to be removed temporarily
  list->size -= 1;              // Decrement the size of the list
  for (int i = pos; i < list->size; i++) { // Move the subsequent rooms
    list->array[i] = list->array[i + 1];
  }
  return temp; // Return the removed room
}

// Function to get the position of a room in the list
int get_pos_room_list(ConstRoomList list, ConstRoom to_search) {
  if (list == NULL_ROOM_LIST ||
      to_search == NULL_ROOM) { // Check if the list or the room is NULL
    log_error(
        "Attempt to search in a NULL room list or search for a NULL room.");
    return -1;
  }
  for (int i = 0; i < list->size; i++) { // Iterate over the rooms in the list
    if (are_rooms_equal(list->array[i], to_search)) { // Compare the rooms
      return i; // Return the found position
    }
  }
  return -1; // Return -1 if the room is not found
}

// Function to print all rooms in the list
void print_room_list(ConstRoomList list) {
  if (list == NULL_ROOM_LIST) { // Check if the list is NULL
    log_error("Attempt to print a NULL room list.");
    return;
  }
  for (int i = 0; i < list->size; i++) { // Iterate over the rooms in the list
    printf("[Room %d]\n", i + 1);        // Print the index of the room
    print_room(list->array[i]);          // Print the room
    puts("");                            // Add a blank line
  }
}

// Function to save the list of rooms to a file
void save_room_list_to_file(ConstRoomList list, FILE *file) {
  if (file == NULL) { // Check if the file is NULL
    log_error("Attempt to save a room list to a NULL file.");
    return;
  }
  if (list == NULL_ROOM_LIST) { // Check if the list is NULL
    log_error("Attempt to save a NULL room list to a file.");
    return;
  }

  fprintf(file, "%d\n", list->size); // Save the size of the list to the file

  for (int i = 0; i < list->size; i++) { // Iterate over the rooms in the list
    save_room_to_file(list->array[i], file); // Save each room to the file
  }
}

// Function to read a list of rooms from a file
RoomList read_room_list_from_file(FILE *file) {
  if (file == NULL) { // Check if the file is NULL
    log_error("Attempt to read a room list from a NULL file.");
    return NULL_ROOM_LIST;
  }

  int num_rooms = 0;

  if (fscanf(file, "%d", &num_rooms) !=
      1) { // Read the number of rooms from the file
    log_error("Failed to read the number of rooms from the file.");
    clean_file(file);
    return NULL_ROOM_LIST;
  }

  RoomList list = new_room_list(); // Create a new list of rooms
  if (list == NULL_ROOM_LIST) {    // Check if the list is NULL
    log_error("Failed to create a new room list.");
    return NULL_ROOM_LIST;
  }

  for (int i = 0; i < num_rooms; i++) {    // Iterate over the number of rooms
    Room room = read_room_from_file(file); // Read each room from the file
    if (room == NULL_ROOM) {               // Check if the room is NULL
      log_error("Failed to read a room from the file.");
      free_room_list(list); // Free the memory of the list
      return NULL_ROOM_LIST;
    }
    cons_room_list(list, room); // Add the room to the list
  }

  return list; // Return the read list
}

// Function to free the memory of the list of rooms
void free_room_list(RoomList list) {
  if (list == NULL) { // Check if the list is NULL
    log_error("Attempt to free a NULL room list.");
    return;
  }
  for (int i = 0; i < list->size; i++) { // Iterate over the rooms in the list
    free_room(list->array[i]);           // Free the memory of each room
  }
  free(list->array); // Free the memory of the array of rooms
  free(list);        // Free the memory of the list structure
}
