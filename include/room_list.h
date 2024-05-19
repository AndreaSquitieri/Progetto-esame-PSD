#ifndef ROOM_LIST_H
#define ROOM_LIST_H
#define NULL_ROOM_LIST NULL

#include "room.h"
#include <stdbool.h>

typedef struct RoomListStruct *RoomList;
typedef const struct RoomListStruct *ConstRoomList;

RoomList new_room_list(void);

bool is_room_list_empty(ConstRoomList list);
int get_size_room_list(ConstRoomList list);

void cons_room_list(RoomList list, Room room);
Room tail_room_list(RoomList list);

Room get_first_room_list(RoomList list);
Room get_at_room_list(RoomList list, int pos);
Room get_room_by_id(RoomList list, unsigned int room_id);
Room remove_at_room_list(RoomList list, int pos);

int get_pos_room_list(ConstRoomList list, ConstRoom to_search);

void print_room_list(ConstRoomList list);
void save_room_list_to_file(ConstRoomList list, FILE *file);
RoomList read_room_list_from_file(FILE *file);

void free_room_list(RoomList list);

#endif /* ROOM_LIST_H */
