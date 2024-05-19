#ifndef EVENT_H_
#define EVENT_H_
#include "date.h"
#include "room.h"
#include <stdbool.h>

#define NULL_EVENT NULL

typedef struct EventStruct *Event;
typedef const struct EventStruct *ConstEvent;

typedef enum { WORKSHOP = 0, KEYNOTE, PANEL } EventType;
int is_valid_event_type(int type);

Event new_event(EventType type, const char *name, Date start_date,
                Date end_date, unsigned int id);

int are_events_equal(ConstEvent event_a, ConstEvent event_b);
int cmp_event(ConstEvent event_a, ConstEvent event_b);
bool do_events_overlap(ConstEvent event_a, ConstEvent event_b);

// Getters and setters
EventType get_event_type(ConstEvent event);
int set_event_type(Event event, EventType type);

ConstDate get_event_start_date(ConstEvent event);
int set_event_start_date(Event event, Date start_date);

ConstDate get_event_end_date(ConstEvent event);
int set_event_end_date(Event event, Date end_date);

const char *get_event_name(ConstEvent event);
int set_event_name(Event event, const char *name);

unsigned int get_event_room_id(ConstEvent event);
int set_event_room_id(Event event, unsigned int room_id);

unsigned int get_event_id(ConstEvent event);

// IO functions
void print_event(ConstEvent event, ConstRoom assigned_room);
Event read_event(unsigned int event_id);
void save_event_to_file(ConstEvent event, FILE *file);
Event read_event_from_file(FILE *file);

void free_event(Event event);

#endif // EVENT_H_
