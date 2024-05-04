#ifndef EVENT_LIST_H_
#define EVENT_LIST_H_
#include <sys/cdefs.h>
/// Put things here
///

typedef struct EventListStruct *EventList;
typedef const struct EventListStruct *ConstEventList;
__attribute_warn_unused_result__ EventList new_even_list(void);

#endif
