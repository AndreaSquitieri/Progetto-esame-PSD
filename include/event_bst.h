#ifndef EVENT_BST_H_
#define EVENT_BST_H_

#include "mevent.h"
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
void print_event_bst(ConstEventBst bst);

bool bst_for_all(EventBst bst, EventPredicate predicate, ...);
void free_event_bst(EventBst bst);

#endif // EVENT_BST_H_
