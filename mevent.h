#ifndef EVENT_H_
#define EVENT_H_
#include "date.h"

#define NULL_EVENT NULL

typedef struct EventStruct *Event;
typedef const struct EventStruct *ConstEvent;

typedef enum { WORKSHOP = 0, KEYNOTE, PANEL } EventType;

Event new_event(EventType type, const char *nome, ConstDate date);
Event copy_event(ConstEvent event);
int set_type_event(Event event, EventType type);
int set_event_date(Event event, Date date);
int set_event_name(Event event, const char *name);
EventType get_type_event(ConstEvent event);
ConstDate get_event_date(ConstEvent event);
char *get_event_nome(ConstEvent event);
char *to_string_event(ConstEvent event);
void free_event(Event event);

#endif // EVENT_H_
