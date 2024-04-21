#ifndef EVENT_BST_H_
#define EVENT_BST_H_

#include "mevent.h"

typedef struct EventBstStruct *EventBst;
typedef struct EventBstStruct *ConstEventBst;

EventBst new_event_bst(void);
int bst_insert_event(EventBst bst, Event event);
Event bst_remove_event(EventBst bst, ConstEvent event);
void print_event_bst(ConstEventBst bst);
char *to_string_event_bst(ConstEventBst bst);
void free_event_bst(EventBst bst);

#endif // EVENT_BST_H_
