#ifndef EVENT_QUEUE_H_
#define EVENT_QUEUE_H_
#include "mevent.h"
#include "room_list.h"
#include <stddef.h>

typedef struct EventQueueStruct *EventQueue;
typedef const struct EventQueueStruct *ConstEventQueue;

EventQueue new_event_queue(void);
int empty_event_queue(ConstEventQueue queue);
Event dequeue_event(EventQueue queue);
int enqueue_event(EventQueue queue, Event event);
Event get_event_at(EventQueue queue, size_t index);
Event remove_event_at(EventQueue queue, size_t index);
void free_queue(EventQueue queue);
void print_event_queue(ConstEventQueue queue, RoomList room_list);

#endif // EVENT_QUEUE_H_
