#ifndef EVENT_H_
#define EVENT_H_
#include "date.h"

#define NULL_EVENT NULL

typedef struct EventStruct *Event;
typedef const struct EventStruct *ConstEvent;

typedef enum { WORKSHOP = 0, KEYNOTE, PANEL } EventType;

Event new_event(EventType type, const char *name, Date date);
Event copy_event(ConstEvent event);
int is_same_instance_event(ConstEvent event_a, ConstEvent event_b);
int set_type_event(Event event, EventType type);
int set_event_date(Event event, Date date);
int set_event_name(Event event, const char *name);
int cmp_event(ConstEvent event_a, ConstEvent event_b);
EventType get_type_event(ConstEvent event);
ConstDate get_event_date(ConstEvent event);
char *get_event_name(ConstEvent event);
char *to_string_event(ConstEvent event);
void free_event(Event event);

#endif // EVENT_H_
