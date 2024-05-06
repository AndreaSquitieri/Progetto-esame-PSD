#ifndef ROOM_LIST_H
#define ROOM_LIST_H
#define NULL_ROOM_LIST NULL

#include "room.h"
#include <stdbool.h>

typedef struct RoomListStruct *RoomList;

RoomList new_room_list(void);

bool is_room_list_empty(RoomList list);

void cons_room_list(RoomList list, Room room);

Room tail_room_list(RoomList list);

Room get_first_room_list(RoomList list);

int get_size_room_list(RoomList list);

int get_pos_room_list(RoomList list, Room to_search);

Room get_at_room_list(RoomList list, int pos);

void print_room_list(RoomList list);

void free_room_list(RoomList list);

#endif /* ROOM_LIST_H */
