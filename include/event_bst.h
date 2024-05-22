#ifndef EVENT_BST_H_
#define EVENT_BST_H_

#include "mevent.h"
#include "room_list.h"
#include <stdarg.h>
#include <stdlib.h>

#define NULL_EVENT_BST NULL

typedef struct EventBstStruct *EventBst;
typedef struct EventBstStruct *ConstEventBst;
typedef bool (*EventPredicate)(Event, va_list);

EventBst new_event_bst(void);
int bst_insert_event(EventBst bst, Event event);
Event bst_remove_event(EventBst bst, ConstEvent event);
Event bst_remove_event_by_id(EventBst bst, unsigned int id);
Event bst_get_event_by_id(EventBst bst, unsigned int id);
size_t get_bst_size(ConstEventBst bst);

void print_event_bst(ConstEventBst bst, ConstRoomList room_list);

bool bst_every(EventBst bst, EventPredicate predicate, ...);
void free_event_bst(EventBst bst);

EventBst read_event_bst_from_file(FILE *file);

void save_event_bst_to_file(ConstEventBst bst, FILE *file);
void save_event_bst_to_file_sorted(ConstEventBst bst, FILE *file);

#endif // EVENT_BST_H_
