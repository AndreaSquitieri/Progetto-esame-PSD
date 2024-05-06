#include "room.h"
#include "event_list.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 102

struct RoomStruct {
  char *name;
  EventList booked_events;
};

Room new_room(const char *name) {
  Room room = my_alloc(1, sizeof(*room));
  room->name = my_strdup(name);
  room->booked_events = new_event_list();

  return room;
}

bool is_room_equal(Room room_a, Room room_b) { return room_a == room_b; }

Room read_room(void) {

  printf("Inserisci nome sala [Max 100 caratteri]: ");
  char name[MAXSIZE] = {0};
  if (read_line(name, MAXSIZE)) {
    return NULL_ROOM;
  }
  Room room = new_room(name);
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

#define FORMAT_ROOM "Nome: %s"
void print_room(Room room) { printf(FORMAT_ROOM, room->name); }

void free_room(Room room) {
  free(room->name);

  // TODO
  // I think that this should be good enough
  // But keep in mind that it isn't freeing the events stored
  free(room->booked_events);
  free(room);
}
