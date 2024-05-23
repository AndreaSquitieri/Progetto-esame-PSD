#ifndef ROOM_LIST_H
#define ROOM_LIST_H

#include "room.h"
#include <stdbool.h>
#include <stdio.h>

#define NULL_ROOM_LIST NULL

/*
  Structure representing a room list.
*/
typedef struct RoomListStruct *RoomList;
typedef const struct RoomListStruct *ConstRoomList;

/*
  Syntax Specification:
  - new_room_list(void) -> RoomList
  - types: none
  - internal types: RoomList

  Semantic Specification:
  - Function: new_room_list() -> list
  - Description: Creates a new empty list of rooms.
  - Preconditions: None.
  - Postconditions: Returns a pointer to the newly created empty RoomList
  object.
*/
RoomList new_room_list(void);

/*
  Syntax Specification:
  - is_room_list_empty(ConstRoomList) -> bool
  - types: ConstRoomList
  - internal types: bool

  Semantic Specification:
  - Function: is_room_list_empty(list) -> empty
  - Description: Checks if the room list is empty.
  - Preconditions: 'list' is a valid RoomList object or NULL.
  - Postconditions: Returns true if the list is empty, false otherwise.
*/
bool is_room_list_empty(ConstRoomList list);

/*
  Syntax Specification:
  - get_size_room_list(ConstRoomList) -> int
  - types: ConstRoomList
  - internal types: int

  Semantic Specification:
  - Function: get_size_room_list(list) -> size
  - Description: Gets the number of rooms in the list.
  - Preconditions: 'list' is a valid RoomList object or NULL.
  - Postconditions: Returns the number of rooms in the list.
*/
int get_size_room_list(ConstRoomList list);

/*
  Syntax Specification:
  - cons_room_list(RoomList, Room) -> void
  - types: RoomList, Room
  - internal types: none

  Semantic Specification:
  - Function: cons_room_list(list, room)
  - Description: Adds a room to the beginning of the list.
  - Preconditions: 'list' is a valid RoomList object, 'room' is a valid Room
                   object.
  - Postconditions: The room is added to the beginning of the list.
*/
void cons_room_list(RoomList list, Room room);

/*
  Syntax Specification:
  - tail_room_list(RoomList) -> Room
  - types: RoomList
  - internal types: Room

  Semantic Specification:
  - Function: tail_room_list(list) -> room
  - Description: Removes and returns the last room from the list.
  - Preconditions: 'list' is a valid RoomList object.
  - Postconditions: Returns the last room from the list. The size of the list
                    is decreased by one.
*/
Room tail_room_list(RoomList list);

/*
  Syntax Specification:
  - get_first_room_list(RoomList) -> Room
  - types: RoomList
  - internal types: Room

  Semantic Specification:
  - Function: get_first_room_list(list) -> room
  - Description: Gets the first room in the list.
  - Preconditions: 'list' is a valid RoomList object.
  - Postconditions: Returns the first room in the list.
*/
Room get_first_room_list(RoomList list);

/*
  Syntax Specification:
  - get_at_room_list(RoomList, int) -> Room
  - types: RoomList, int
  - internal types: Room

  Semantic Specification:
  - Function: get_at_room_list(list, pos) -> room
  - Description: Gets the room at the specified position in the list.
  - Preconditions: 'list' is a valid RoomList object, 'pos' is a valid index.
  - Postconditions: Returns the room at the specified position in the list.
*/
Room get_at_room_list(RoomList list, int pos);

/*
  Syntax Specification:
  - get_room_by_id(RoomList, unsigned int) -> Room
  - types: RoomList, unsigned int
  - internal types: Room

  Semantic Specification:
  - Function: get_room_by_id(list, room_id) -> room
  - Description: Gets the room with the specified ID from the list.
  - Preconditions: 'list' is a valid RoomList object.
  - Postconditions: Returns the room with the specified ID from the list, or
                    NULL if not found.
*/
Room get_room_by_id(RoomList list, unsigned int room_id);

/*
  Syntax Specification:
  - remove_at_room_list(RoomList, int) -> Room
  - types: RoomList, int
  - internal types: Room

  Semantic Specification:
  - Function: remove_at_room_list(list, pos) -> room
  - Description: Removes and returns the room at the specified position in the
                 list.
  - Preconditions: 'list' is a valid RoomList object, 'pos' is a valid index.
  - Postconditions: Returns the room removed from the list.
*/
Room remove_at_room_list(RoomList list, int pos);

/*
  Syntax Specification:
  - get_pos_room_list(ConstRoomList, ConstRoom) -> int
  - types: ConstRoomList, ConstRoom
  - internal types: int

  Semantic Specification:
  - Function: get_pos_room_list(list, to_search) -> pos
  - Description: Gets the position of the specified room in the list.
  - Preconditions: 'list' is a valid RoomList object, 'to_search' is a valid
                   Room object.
  - Postconditions: Returns the position of the room in the list, or -1 if not
                    found.
*/
int get_pos_room_list(ConstRoomList list, ConstRoom to_search);

/*
  Syntax Specification:
  - print_room_list(ConstRoomList) -> void
  - types: ConstRoomList
  - internal types: none

  Semantic Specification:
  - Function: print_room_list(list)
  - Description: Prints all the rooms in the list.
  - Preconditions: 'list' is a valid RoomList object.
  - Postconditions: Prints the details of each room in the list to stdout.
*/
void print_room_list(ConstRoomList list);

/*
  Syntax Specification:
  - save_room_list_to_file(ConstRoomList, FILE*) -> void
  - types: ConstRoomList, FILE*
  - internal types: none

  Semantic Specification:
  - Function: save_room_list_to_file(list, file)
  - Description: Saves the list of rooms to a file.
  - Preconditions: 'list' is a valid RoomList object, 'file' is a valid FILE
                   stream.
  - Postconditions: Writes the details of each room in the list to the file
                    stream.
*/
void save_room_list_to_file(ConstRoomList list, FILE *file);

/*
  Syntax Specification:
  - read_room_list_from_file(FILE*) -> RoomList
  - types: FILE*
  - internal types: RoomList

  Semantic Specification:
  - Function: read_room_list_from_file(file) -> list
  - Description: Reads a list of rooms from a file.
  - Preconditions: 'file' is a valid FILE stream.
  - Postconditions: Returns a pointer to the newly created RoomList object
                    containing the rooms read from the file.
*/
RoomList read_room_list_from_file(FILE *file);

/*
  Syntax Specification:
  - free_room_list(RoomList) -> void
  - types: RoomList
  - internal types: none

  Semantic Specification:
  - Function: free_room_list(list)
  - Description: Frees the memory allocated for the room list.
  - Preconditions: 'list' is a valid RoomList object.
  - Postconditions: Releases the memory allocated for the RoomList object and
                    all its contained rooms.
*/
void free_room_list(RoomList list);

#endif /* ROOM_LIST_H */
