#ifndef EVENT_BST_H_
#define EVENT_BST_H_

#include "mevent.h"

typedef struct BstEventStruct *BstEvent;
typedef struct BstEventStruct *ConstBstEvent;

BstEvent new_event_bst();
void bst_insert_event(BstEvent bst, Event event);
Event bst_remove_event(BstEvent bst, Event event);
char *to_string_event_bst(ConstBstEvent bst);
void free_event_bst(BstEvent bst);

#endif // BST_EVENTI_H_
