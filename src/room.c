#include "room.h"
#include "event_list.h"
#include <stdlib.h>
#include <string.h>

struct RoomStruct {
  char *name;
  EventList booked_events;
};

Room new_room(const char *name) {
  Room room = malloc(sizeof(*room));
  if (room == NULL) {
    return NULL_ROOM;
  }

  room->name = strdup(name);
  if (room->name == NULL) {
    free(room);
    return NULL_ROOM;
  }

  room->booked_events = new_event_list();
  if (room->booked_events == NULL) {
    free(room->name);
    free(room);
    return NULL_ROOM;
  }

  return room;
}

const char *get_room_name(Room room) { return room->name; }

int room_assign_event(Room room, Event event) {
  if (!is_room_free_for_event(room, event)) {
    return -1;
  }
  cons_event_list(room->booked_events, event);
  return 0;
}

Event room_remove_event(Room room, Event event) {
  int pos = get_pos_event_list(room->booked_events, event);
  if (pos < 0) {
    return NULL_EVENT;
  }
  return remove_event_list(room->booked_events, pos);
}

bool is_room_free_for_event(Room room, Event event) {
  int size = get_size_event_list(room->booked_events);
  for (int i = 0; i < size; i++) {
    ConstEvent temp = get_at_event_list(room->booked_events, i);
    if (do_events_overlap(temp, event)) {
      return false;
    }
  }
  return true;
}

void free_room(Room room) {
  free(room->name);
  free(room);
}
