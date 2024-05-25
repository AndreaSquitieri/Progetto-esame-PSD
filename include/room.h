#ifndef ROOM_H_
#define ROOM_H_

#include <stdbool.h>
#include <stdio.h>

#define NULL_ROOM NULL
#define NULL_ROOM_ID 0

/*
  Structure representing a room.
  Contains an ID, a name, and a capacity.
*/
typedef struct RoomStruct *Room;
typedef const struct RoomStruct *ConstRoom;

/*
  Syntax Specification:
  - new_room(const char*, unsigned int, unsigned int) -> Room
  - types: const char*, unsigned int, unsigned int
  - internal types: Room

  Semantic Specification:
  - Function: new_room(name, id, capacity) -> return_room
  - Description: Creates a new Room object with the specified name, ID, and
  capacity.
  - Preconditions: 'name' is a valid string representing the name of the room.
                   'id' is a non-negative integer representing the ID of the
  room. 'capacity' is a non-negative integer representing the capacity of the
  room.
  - Postconditions: Returns a pointer to the newly created Room object, or NULL
  if an error occurs. The caller is responsible for freeing the allocated memory
  using free_room().
*/
Room new_room(const char *name, unsigned int id, unsigned int capacity);

/*
  Syntax Specification:
  - copy_room(ConstRoom) -> Room
  - types: ConstRoom
  - internal types: Room

  Semantic Specification:
  - Function: copy_room(room) -> return_room
  - Description: Creates a copy of the given Room object.
  - Preconditions: 'room' is a valid Room object.
  - Postconditions: Returns a pointer to the newly created copy of 'room'.
                    The caller is responsible for freeing the allocated memory
  using free_room().
*/
Room copy_room(ConstRoom room);

/*
  Syntax Specification:
  - are_rooms_equal(ConstRoom, ConstRoom) -> bool
  - types: ConstRoom, bool
  - internal types: none

  Semantic Specification:
  - Function: are_rooms_equal(room_a, room_b) -> result
  - Description: Checks if two Room objects are equal based on their IDs.
  - Preconditions: 'room_a' and 'room_b' are valid Room objects.
  - Postconditions: Returns true if 'room_a' and 'room_b' have the same ID,
  otherwise false.
*/
bool are_rooms_equal(ConstRoom room_a, ConstRoom room_b);

/*
  Syntax Specification:
  - get_room_name(ConstRoom) -> const char*
  - types: ConstRoom, const char*
  - internal types: none

  Semantic Specification:
  - Function: get_room_name(room) -> name
  - Description: Gets the name of the given Room object.
  - Preconditions: 'room' is a valid Room object.
  - Postconditions: Returns a pointer to the name of 'room'.
*/
const char *get_room_name(ConstRoom room);

/*
  Syntax Specification:
  - get_room_id(ConstRoom) -> unsigned int
  - types: ConstRoom, unsigned int
  - internal types: none

  Semantic Specification:
  - Function: get_room_id(room) -> id
  - Description: Gets the ID of the given Room object.
  - Preconditions: 'room' is a valid Room object.
  - Postconditions: Returns the ID of 'room'.
*/
unsigned int get_room_id(ConstRoom room);

/*
  Syntax Specification:
  - print_room(ConstRoom) -> void
  - types: ConstRoom
  - internal types: none

  Semantic Specification:
  - Function: print_room(room)
  - Description: Prints the details of the given Room object to stdout.
  - Preconditions: 'room' is a valid Room object.
  - Postconditions: The details of 'room' are printed to stdout.
*/
void print_room(ConstRoom room);

/*
  Syntax Specification:
  - read_room(unsigned int) -> Room
  - types: unsigned int, Room
  - internal types: char[], ResultInt, Room

  Semantic Specification:
  - Function: read_room(id) -> room
  - Description: Reads details of a Room object from stdin and creates a new
  Room object with id 'id'.
  - Preconditions: None.
  - Postconditions: Returns a pointer to the newly created Room object, or NULL
  if an error occurs. The caller is responsible for freeing the allocated memory
  using free_room().
*/
Room read_room(unsigned int id);

/*
  Syntax Specification:
  - save_room_to_file(ConstRoom, FILE*)
  - types: ConstRoom, FILE*
  - internal types: none

  Semantic Specification:
  - Function: save_room_to_file(room, file)
  - Description: Saves the details of the given Room object to a file stream.
  - Preconditions: 'room' is a valid Room object. 'file' is a valid FILE stream
  opened in write mode.
  - Postconditions: The details of 'room' are written to the file stream 'file'.
*/
void save_room_to_file(ConstRoom room, FILE *file);

/*
  Syntax Specification:
  - read_room_from_file(FILE*) -> Room
  - types: FILE*, Room
  - internal types: unsigned int, char[]

  Semantic Specification:
  - Function: read_room_from_file(file) -> room
  - Description: Reads details of a Room object from a file stream and creates a
  new Room object.
  - Preconditions: 'file' is a valid FILE stream opened in writing mode.
  - Postconditions: Returns a pointer to the newly created Room object, or NULL
  if an error occurs. The caller is responsible for freeing the allocated memory
  using free_room().
*/
Room read_room_from_file(FILE *file);

/*
  Syntax Specification:
  - free_room(Room)
  - types: Room
  - internal types: none

  Semantic Specification:
  - Function: free_room(room)
  - Description: Frees the memory allocated for a Room object.
  - Preconditions: 'room' is a valid Room object.
  - Postconditions: The memory allocated for 'room' is deallocated.
*/
void free_room(Room room);

#endif // ROOM_H_
