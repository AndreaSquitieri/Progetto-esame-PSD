#ifndef ROOM_H_
#define ROOM_H_

#include <stdbool.h>

#define NULL_ROOM NULL

typedef struct RoomStruct *Room;
typedef const struct RoomStruct *ConstRoom;

Room new_room(const char *name);

Room copy_room(ConstRoom room);
bool is_room_equal(ConstRoom room_a, ConstRoom room_b);

const char *get_room_name(ConstRoom room);

Room read_room(void);

void print_room(ConstRoom room);

void free_room(Room room);

void init_room_id_counter(unsigned int id);
unsigned int get_room_id_counter(void);

#endif // ROOM_H_
