#ifndef EVENT_BST_H_
#define EVENT_BST_H_

#include "mevent.h"
#include <stdlib.h>

typedef struct EventBstStruct *EventBst;
typedef struct EventBstStruct *ConstEventBst;

EventBst new_event_bst(void);
int bst_insert_event(EventBst bst, Event event);
Event bst_remove_event(EventBst bst, ConstEvent event);
Event bst_remove_event_by_id(EventBst bst, unsigned int id);
size_t get_bst_size(ConstEventBst bst);
void print_event_bst(ConstEventBst bst);
char *to_string_event_bst(ConstEventBst bst);
void free_event_bst(EventBst bst);

#endif // EVENT_BST_H_
