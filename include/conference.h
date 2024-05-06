#ifndef CONFERENCE_H_
#define CONFERENCE_H_

#include <stdlib.h>
#define NULL_CONFERENCE NULL

typedef struct ConferenceStruct *Conference;
typedef const struct ConferenceStruct *ConstConference;

Conference new_conference(void);

int add_conference_event(Conference conf);
int edit_conference_event(Conference conf);
int remove_conference_event(Conference conf);
int display_conference_schedule(ConstConference conf);
int display_conference_rooms(ConstConference conf);
int add_conference_room(Conference conf);

void free_conference(Conference conf);

#endif // CONFERENCE_H_
