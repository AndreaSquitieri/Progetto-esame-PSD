#ifndef ROOM_H_
#define ROOM_H_

#include <stdbool.h>

#define NULL_ROOM NULL

typedef struct RoomStruct *Room;
typedef const struct RoomStruct *ConstRoom;

Room new_room(const char *name);

bool is_room_equal(ConstRoom room_a, ConstRoom room_b);

const char *get_room_name(ConstRoom room);

Room read_room(void);

void print_room(ConstRoom room);

void free_room(Room room);

#endif // ROOM_H_
