#ifndef EVENT_H_
#define EVENT_H_
#include "date.h"
#include <stdbool.h>

#define NULL_EVENT NULL

typedef struct EventStruct *Event;
typedef const struct EventStruct *ConstEvent;

typedef enum { WORKSHOP = 0, KEYNOTE, PANEL } EventType;
int is_valid_event_type(int type);
Event new_event(EventType type, const char *name, Date start_date,
                Date end_date);
Event copy_event(ConstEvent event);
int is_same_instance_event(ConstEvent event_a, ConstEvent event_b);
int is_event_equal(ConstEvent event_a, ConstEvent event_b);
int set_event_type(Event event, EventType type);
int set_event_start_date(Event event, Date start_date);
int set_event_end_date(Event event, Date end_date);
int set_event_name(Event event, const char *name);

// TODO
// This sucks
typedef struct RoomStruct *Room;
int set_event_room(Event event, Room room);

int cmp_event(ConstEvent event_a, ConstEvent event_b);
EventType get_type_event(ConstEvent event);
ConstDate get_event_start_date(ConstEvent event);
ConstDate get_event_end_date(ConstEvent event);
unsigned int get_event_id(ConstEvent event);
const char *get_event_name(ConstEvent event);
bool do_events_overlap(ConstEvent event_a, ConstEvent event_b);
void print_event(ConstEvent event);
void free_event(Event event);

#endif // EVENT_H_
