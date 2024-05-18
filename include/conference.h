#ifndef CONFERENCE_H_
#define CONFERENCE_H_

#include <stdio.h>
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
int remove_conference_room(Conference conf);
int conference_assign_event_to_room(Conference conf);

void free_conference(Conference conf);

void save_conference_to_file(ConstConference conf, FILE *file);
Conference read_conference_from_file(FILE *file);

#endif // CONFERENCE_H_
