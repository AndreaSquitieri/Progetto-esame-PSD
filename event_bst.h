#ifndef EVENT_BST_H_
#define EVENT_BST_H_

#include "mevent.h"

typedef struct BstEventStruct *BstEvent;
typedef struct BstEventStruct *ConstBstEvent;

BstEvent new_event_bst(void);
int bst_insert_event(BstEvent bst, Event event);
Event bst_remove_event(BstEvent bst, ConstEvent event);
void print_event_bst(ConstBstEvent bst);
char *to_string_event_bst(ConstBstEvent bst);
void free_event_bst(BstEvent bst);

#endif // EVENT_BST_H_
