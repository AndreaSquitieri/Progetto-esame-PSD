#ifndef ROOM_H_
#define ROOM_H_

#include "mevent.h"
#include <stdbool.h>

#define NULL_ROOM NULL

typedef struct RoomStruct *Room;

Room new_room(const char *name);
const char *get_room_name(Room room);
int room_assign_event(Room room, Event event);

Event room_remove_event(Room room, Event event);

bool is_room_free_for_event(Room room, Event event);
void free_room(Room room);

#endif // ROOM_H_