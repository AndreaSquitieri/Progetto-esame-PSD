#ifndef CONFERENCE_H_
#define CONFERENCE_H_
#include <stdio.h>
#include <stdlib.h>

#define NULL_CONFERENCE NULL

typedef struct ConferenceStruct *Conference;
typedef const struct ConferenceStruct *ConstConference;

/*
  Syntax Specification:
  - new_conference(void) -> Conference
  - types: none
  - internal types: Conference, EventBst, RoomList, unsigned int

  Semantic Specification:
  - Function: new_conference() -> conference
  - Description: Creates a new empty conference to store events and rooms
  - Preconditions: None.
  - Postconditions: Returns a pointer to the newly created empty Conference
    object.
*/
Conference new_conference(void);

/*
  Syntax Specification:
  - add_conference_event(Conference) -> int
  - types: Conference
  - internal types: Event

  Semantic Specification:
  - Function: add_conference_event(conf) -> result
  - Description: Adds a new event to the conference.
  - Preconditions:
    - 'conf' must point to a valid Conference object.
  - Postconditions: Returns 0 on success, -1 on failure.
*/

int add_conference_event(Conference conf);

/*
  Syntax Specification:
  - edit_conference_event(Conference) -> int
  - types: Conference
  - internal types: Event

  Semantic Specification:
  - Function: edit_conference_event(conf) -> result
  - Description: Edits an existing event in the conference.
  - Preconditions:
    - 'conf' must point to a valid Conference object.
  - Postconditions: Returns 0 on success, -1 on failure.
*/

int edit_conference_event(Conference conf);

/*
  Syntax Specification:
  - remove_conference_event(Conference) -> int
  - types: Conference
  - internal types: Event

  Semantic Specification:
  - Function: remove_conference_event(conf) -> result
  - Description: Removes an event from the conference.
  - Preconditions:
    - 'conf' must point to a valid Conference object.
  - Postconditions: Returns 0 on success, -1 on failure.
*/
int remove_conference_event(Conference conf);

/*
  Syntax Specification:
  - display_conference_schedule(ConstConference) -> void
  - types: ConstConference
  - internal types: Event, Room

  Semantic Specification:
  - Function: display_conference_schedule(conf)
  - Description: Displays the schedule of events in the conference.
  - Preconditions:
    - 'conf' must point to a valid ConstConference object.
  - Postconditions: Prints the schedule of events.
*/

void display_conference_schedule(ConstConference conf);

/*
  Syntax Specification:
  - display_conference_rooms(ConstConference) -> void
  - types: ConstConference
  - internal types: Room

  Semantic Specification:
  - Function: display_conference_rooms(conf)
  - Description: Displays the list of rooms available in the conference.
  - Preconditions:
    - 'conf' must point to a valid ConstConference object.
  - Postconditions: Prints the list of rooms.
*/

void display_conference_rooms(ConstConference conf);

/*
  Syntax Specification:
  - add_conference_room(Conference) -> int
  - types: Conference
  - internal types: Room

  Semantic Specification:
  - Function: add_conference_room(conf) -> result
  - Description: Adds a new room to the conference.
  - Preconditions:
    - 'conf' must point to a valid Conference object.
  - Postconditions: Returns 0 on success, -1 on failure.
*/

int add_conference_room(Conference conf);

/*
  Syntax Specification:
  - remove_conference_room(Conference) -> int
  - types: Conference
  - internal types: Room

  Semantic Specification:
  - Function: remove_conference_room(conf) -> result
  - Description: Removes a room from the conference.
  - Preconditions:
    - 'conf' must point to a valid Conference object.
  - Postconditions: Returns 0 on success, -1 on failure.
*/

int remove_conference_room(Conference conf);

/*
  Syntax Specification:
  - conference_assign_event_to_room(Conference) -> int
  - types: Conference
  - internal types: Event, Room

  Semantic Specification:
  - Function: conference_assign_event_to_room(conf) -> result
  - Description: Assigns an event to a room in the conference.
  - Preconditions:
    - 'conf' must point to a valid Conference object.
  - Postconditions: Returns 0 on success, -1 on failure.
*/

int conference_assign_event_to_room(Conference conf);

/*
  Syntax Specification:
  - conference_free_event_room(Conference) -> int
  - types: Conference
  - internal types: Event

  Semantic Specification:
  - Function: conference_free_event_room(conf) -> result
  - Description: Frees the assigned room for an event in the conference.
  - Preconditions:
    - 'conf' must point to a valid Conference object.
  - Postconditions: Returns 0 on success, -1 on failure.
*/

int conference_free_event_room(Conference conf);

/*
  Syntax Specification:
  - free_conference(Conference) -> void
  - types: Conference
  - internal types: Event, Room

  Semantic Specification:
  - Function: free_conference(conf)
  - Description: Frees the memory allocated for the conference and its events
    and rooms.
  - Preconditions:
    - 'conf' must point to a valid Conference object.
  - Postconditions: Frees the memory allocated for the conference.
*/

void free_conference(Conference conf);

/*
  Syntax Specification:
  - save_conference_to_file(ConstConference, FILE*) -> void
  - types: ConstConference, FILE*
  - internal types: Event, Room

  Semantic Specification:
  - Function: save_conference_to_file(conf, file)
  - Description: Saves the conference data to a file.
  - Preconditions:
    - 'conf' must point to a valid ConstConference object.
    - 'file' must point to a valid FILE object opened in write mode.
  - Postconditions: Writes the conference data to the specified file.
*/

void save_conference_to_file(ConstConference conf, FILE *file);

/*
  Syntax Specification:
  - save_conference_to_file_sorted(ConstConference, FILE*) -> void
  - types: ConstConference, FILE*
  - internal types: Event, Room

  Semantic Specification:
  - Function: save_conference_to_file_sorted(conf, file)
  - Description: Saves the conference data to a file in sorted order.
  - Preconditions:
    - 'conf' must point to a valid ConstConference object.
    - 'file' must point to a valid FILE object opened in write mode.
  - Postconditions: Writes the conference data to the specified file in sorted
    order.
*/

void save_conference_to_file_sorted(ConstConference conf, FILE *file);

/*
  Syntax Specification:
  - read_conference_from_file(FILE*) -> Conference
  - types: FILE*
  - internal types: Event, Room

  Semantic Specification:
  - Function: read_conference_from_file(file) -> conf
  - Description: Reads conference data from a file and constructs a new
    conference object.
  - Preconditions:
    - 'file' must point to a valid FILE object opened in read mode.
  - Postconditions: Returns a pointer to the newly created Conference object
    containing the conference data read from the file.
*/

Conference read_conference_from_file(FILE *file);

#endif // CONFERENCE_H_
