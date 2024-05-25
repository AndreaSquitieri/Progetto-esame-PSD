#ifndef EVENT_H_
#define EVENT_H_
#include "date.h"
#include "room.h"
#include <stdbool.h>

#define NULL_EVENT NULL
#define NULL_EVENT_ID 0

typedef struct EventStruct *Event;
typedef const struct EventStruct *ConstEvent;

// Enum defining different types of events
typedef enum {
  WORKSHOP = 0, // Workshop event
  KEYNOTE,      // Keynote event
  PANEL         // Panel discussion event
} EventType;

/*
  Syntax Specification:
  - is_valid_event_type(int type) -> int
  - types: int
  - internal types: none

  Semantic Specification:
  - Function: is_valid_event_type(type) -> result
  - Description: Checks if the given event type is valid.
  - Preconditions: None.
  - Postconditions: Returns 1 if the event type is valid, 0 otherwise.
*/
int is_valid_event_type(int type);

/*
  Syntax Specification:
  - new_event(EventType type, const char *name, Date start_date, Date end_date,
              unsigned int id) -> Event
  - types: EventType, const char *, Date, Date, unsigned int
  - internal types: Event

  Semantic Specification:
  - Function: new_event(type, name, start_date, end_date, id) -> event
  - Description: Creates a new event with the specified type, name, start date,
                 end date, and ID.
  - Preconditions: None.
  - Postconditions: Returns a pointer to the newly created Event object.
*/
Event new_event(EventType type, const char *name, Date start_date,
                Date end_date, unsigned int id);

/*
  Syntax Specification:
  - are_events_equal(ConstEvent event_a, ConstEvent event_b) -> int
  - types: ConstEvent, ConstEvent
  - internal types: none

  Semantic Specification:
  - Function: are_events_equal(event_a, event_b) -> result
  - Description: Checks if two events are equal based on their IDs.
  - Preconditions: None.
  - Postconditions: Returns 1 if the events are equal, 0 otherwise.
*/
int are_events_equal(ConstEvent event_a, ConstEvent event_b);

/*
  Syntax Specification:
  - cmp_event(ConstEvent event_a, ConstEvent event_b) -> int
  - types: ConstEvent, ConstEvent
  - internal types: none

  Semantic Specification:
  - Function: cmp_event(event_a, event_b) -> result
  - Description: Compares two events for sorting based on start date and name.
  - Preconditions: None.
  - Postconditions: Returns a negative value if event_a should come before
                    event_b, a positive value if event_a should come after
                    event_b, and 0 if they are equal.
*/
int cmp_event(ConstEvent event_a, ConstEvent event_b);

/*
  Syntax Specification:
  - do_events_overlap(ConstEvent event_a, ConstEvent event_b) -> bool
  - types: ConstEvent, ConstEvent
  - internal types: none

  Semantic Specification:
  - Function: do_events_overlap(event_a, event_b) -> result
  - Description: Checks if two events overlap in time.
  - Preconditions: None.
  - Postconditions: Returns true if the events overlap, false otherwise.
*/
bool do_events_overlap(ConstEvent event_a, ConstEvent event_b);

/* Getters and Setters */

/*
  Syntax Specification:
  - get_event_type(ConstEvent event) -> EventType
  - types: ConstEvent
  - internal types: none

  Semantic Specification:
  - Function: get_event_type(event) -> type
  - Description: Retrieves the type of the event.
  - Preconditions: None.
  - Postconditions: Returns the EventType of the event.
*/
EventType get_event_type(ConstEvent event);

/*
  Syntax Specification:
  - set_event_type(Event event, EventType type) -> int
  - types: Event, EventType
  - internal types: none

  Semantic Specification:
  - Function: set_event_type(event, type) -> result
  - Description: Sets the type of the event.
  - Preconditions: None.
  - Postconditions: Returns 0 if successful, -1 otherwise.
*/
int set_event_type(Event event, EventType type);

/*
  Syntax Specification:
  - get_event_start_date(ConstEvent event) -> ConstDate
  - types: ConstEvent
  - internal types: none

  Semantic Specification:
  - Function: get_event_start_date(event) -> start_date
  - Description: Retrieves the start date of the event.
  - Preconditions: None.
  - Postconditions: Returns a pointer to the start Date object of the event.
*/
ConstDate get_event_start_date(ConstEvent event);

/*
  Syntax Specification:
  - set_event_start_date(Event event, Date start_date) -> int
  - types: Event, Date
  - internal types: none

  Semantic Specification:
  - Function: set_event_start_date(event, start_date) -> result
  - Description: Sets the start date of the event.
  - Preconditions: None.
  - Postconditions: Returns 0 if successful, -1 otherwise.
*/
int set_event_start_date(Event event, Date start_date);

/*
  Syntax Specification:
  - get_event_end_date(ConstEvent event) -> ConstDate
  - types: ConstEvent
  - internal types: none

  Semantic Specification:
  - Function: get_event_end_date(event) -> end_date
  - Description: Retrieves the end date of the event.
  - Preconditions: None.
  - Postconditions: Returns a pointer to the end Date object of the event.
*/
ConstDate get_event_end_date(ConstEvent event);

/*
  Syntax Specification:
  - set_event_end_date(Event event, Date end_date) -> int
  - types: Event, Date
  - internal types: none

  Semantic Specification:
  - Function: set_event_end_date(event, end_date) -> result
  - Description: Sets the end date of the event.
  - Preconditions: None.
  - Postconditions: Returns 0 if successful, -1 otherwise.
*/
int set_event_end_date(Event event, Date end_date);

/*
  Syntax Specification:
  - get_event_name(ConstEvent event) -> const char *
  - types: ConstEvent
  - internal types: none

  Semantic Specification:
  - Function: get_event_name(event) -> name
  - Description: Retrieves the name of the event.
  - Preconditions: None.
  - Postconditions: Returns a pointer to the name string of the event.
*/
const char *get_event_name(ConstEvent event);

/*
  Syntax Specification:
  - set_event_name(Event event, const char *name) -> int
  - types: Event, const char *
  - internal types: none

  Semantic Specification:
  - Function: set_event_name(event, name) -> result
  - Description: Sets the name of the event.
  - Preconditions: None.
  - Postconditions: Returns 0 if successful, -1 otherwise.
*/
int set_event_name(Event event, const char *name);

/*
  Syntax Specification:
  - get_event_room_id(ConstEvent event) -> unsigned int
  - types: ConstEvent
  - internal types: none

  Semantic Specification:
  - Function: get_event_room_id(event) -> room_id
  - Description: Retrieves the assigned room ID of the event.
  - Preconditions: None.
  - Postconditions: Returns the room ID of the event.
*/
unsigned int get_event_room_id(ConstEvent event);

/*
  Syntax Specification:
  - set_event_room_id(Event event, unsigned int room_id) -> int
  - types: Event, unsigned int
  - internal types: none

  Semantic Specification:
  - Function: set_event_room_id(event, room_id) -> result
  - Description: Sets the assigned room ID of the event.
  - Preconditions: None.
  - Postconditions: Returns 0 if successful, -1 otherwise.
*/
int set_event_room_id(Event event, unsigned int room_id);

/*
  Syntax Specification:
  - get_event_id(ConstEvent event) -> unsigned int
  - types: ConstEvent
  - internal types: none

  Semantic Specification:
  - Function: get_event_id(event) -> id
  - Description: Retrieves the ID of the event.
  - Preconditions: None.
  - Postconditions: Returns the ID of the event.
*/
unsigned int get_event_id(ConstEvent event);

/*
  Syntax Specification:
  - print_event(ConstEvent event, ConstRoom assigned_room) -> void
  - types: ConstEvent, ConstRoom
  - internal types: none

  Semantic Specification:
  - Function: print_event(event, assigned_room)
  - Description: Prints the details of the event to stdout, including assigned
                 room information if available.
  - Preconditions: None.
  - Postconditions: None.
*/
void print_event(ConstEvent event, ConstRoom assigned_room);

/*
  Syntax Specification:
  - read_event(unsigned int event_id) -> Event
  - types: unsigned int
  - internal types: none

  Semantic Specification:
  - Function: read_event(event_id) -> event
  - Description: Reads event details from user input.
  - Preconditions: None.
  - Postconditions: Returns a pointer to the newly created Event object.
*/
Event read_event(unsigned int event_id);

/*
  Syntax Specification:
  - save_event_to_file(ConstEvent event, FILE *file) -> void
  - types: ConstEvent, FILE
  - internal types: none

  Semantic Specification:
  - Function: save_event_to_file(event, file)
  - Description: Saves event details to a file.
  - Preconditions: None.
  - Postconditions: None.
*/
void save_event_to_file(ConstEvent event, FILE *file);

/*
  Syntax Specification:
  - read_event_from_file(FILE *file) -> Event
  - types: FILE
  - internal types: none

  Semantic Specification:
  - Function: read_event_from_file(file) -> event
  - Description: Reads event details from a file.
  - Preconditions: None.
  - Postconditions: Returns a pointer to the newly created Event object.
*/
Event read_event_from_file(FILE *file);

/*
  Syntax Specification:
  - free_event(Event event) -> void
  - types: Event
  - internal types: none

  Semantic Specification:
  - Function: free_event(event)
  - Description: Frees memory allocated for the event.
  - Preconditions: None.
  - Postconditions: None.
*/
void free_event(Event event);

#endif // EVENT_H_
