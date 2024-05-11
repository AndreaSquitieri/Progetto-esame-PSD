#ifndef ROOM_H_
#define ROOM_H_

#include <stdbool.h>
#include <stdio.h>

#define NULL_ROOM NULL
#define NULL_ROOM_ID 0

typedef struct RoomStruct *Room;
typedef const struct RoomStruct *ConstRoom;

Room new_room(const char *name, unsigned int id);

Room copy_room(ConstRoom room);
bool is_room_equal(ConstRoom room_a, ConstRoom room_b);

const char *get_room_name(ConstRoom room);
unsigned int get_room_id(ConstRoom room);

Room read_room(unsigned int id);

void print_room(ConstRoom room);

void free_room(Room room);

void save_room_to_file(ConstRoom room, FILE *file);

Room read_room_from_file(FILE *file);

#endif // ROOM_H_
