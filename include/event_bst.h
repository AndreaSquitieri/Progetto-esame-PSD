#ifndef EVENT_BST_H_
#define EVENT_BST_H_

#include "mevent.h"
#include "room_list.h"
#include <stdarg.h>
#include <stdlib.h>

#define NULL_EVENT_BST NULL
// Represents a pointer to a binary search tree (BST) containing
// events.
typedef struct EventBstStruct *EventBst;
// Represents a constant pointer to a BST containing events.
typedef struct EventBstStruct *ConstEventBst;
// Represents a pointer to a function that can be used as a
// predicate to evaluate events in the BST.
typedef bool (*EventPredicate)(Event, va_list);

/*
  Syntax Specification:
  - new_event_bst(void) -> EventBst
  - types: none
  - internal types: EventBst

  Semantic Specification:
  - Function: new_event_bst() -> bst
  - Description: Creates a new empty binary search tree (BST) to store events.
  - Preconditions: None.
  - Postconditions: Returns a pointer to the newly created empty EventBst
  object.
*/

EventBst new_event_bst(void);

/*
  Syntax Specification:
  - bst_insert_event(EventBst, Event) -> int
  - types: EventBst, Event
  - internal types: EventBstNode

  Semantic Specification:
  - Function: bst_insert_event(bst, event) -> result
  - Description: Inserts an event into the binary search tree (BST).
  - Preconditions:
    - 'bst' must point to a valid EventBst object.
    - 'event' must point to a valid Event object.
  - Postconditions:
    - If successful, the event is inserted into the BST.
    - Returns 0 on success, -1 on failure.
*/

int bst_insert_event(EventBst bst, Event event);

/*
  Syntax Specification:
  - bst_remove_event(EventBst, ConstEvent) -> Event
  - types: EventBst, ConstEvent
  - internal types: EventBstNode

  Semantic Specification:
  - Function: bst_remove_event(bst, event) -> removed_event
  - Description: Removes the specified event from the binary search tree (BST).
  - Preconditions:
    - 'bst' must point to a valid EventBst object.
    - 'event' must point to a valid ConstEvent object.
  - Postconditions:
    - If successful, the event is removed from the BST.
    - Returns the removed Event object, or NULL_EVENT if the event was not
  found.
*/

Event bst_remove_event(EventBst bst, ConstEvent event);

/*
  Syntax Specification:
  - bst_remove_event_by_id(EventBst, unsigned int) -> Event
  - types: EventBst, unsigned int
  - internal types: EventBstNode

  Semantic Specification:
  - Function: bst_remove_event_by_id(bst, id) -> removed_event
  - Description: Removes the event with the specified ID from the binary search
  tree (BST).
  - Preconditions:
    - 'bst' must point to a valid EventBst object.
  - Postconditions:
    - If successful, the event with the specified ID is removed from the BST.
    - Returns the removed Event object, or NULL_EVENT if the event was not
  found.
*/

Event bst_remove_event_by_id(EventBst bst, unsigned int id);

/*
  Syntax Specification:
  - bst_get_event_by_id(EventBst, unsigned int) -> Event
  - types: EventBst, unsigned int
  - internal types: EventBstNode

  Semantic Specification:
  - Function: bst_get_event_by_id(bst, id) -> event
  - Description: Retrieves the event with the specified ID from the binary
  search tree (BST).
  - Preconditions:
    - 'bst' must point to a valid EventBst object.
  - Postconditions:
    - Returns the Event object with the specified ID, or NULL_EVENT if the event
  was not found.
*/

Event bst_get_event_by_id(EventBst bst, unsigned int id);

/*
  Syntax Specification:
  - get_bst_size(ConstEventBst) -> size_t
  - types: ConstEventBst
  - internal types: EventBst

  Semantic Specification:
  - Function: get_bst_size(bst) -> size
  - Description: Returns the number of events stored in the binary search tree
  (BST).
  - Preconditions:
    - 'bst' must point to a valid ConstEventBst object.
  - Postconditions: Returns the number of events stored in the BST.
*/

size_t get_bst_size(ConstEventBst bst);

/*
  Syntax Specification:
  - print_event_bst(ConstEventBst, ConstRoomList) -> void
  - types: ConstEventBst, ConstRoomList
  - internal types: EventBstNode

  Semantic Specification:
  - Function: print_event_bst(bst, room_list)
  - Description: Prints the events stored in the binary search tree (BST) along
  with their assigned rooms.
  - Preconditions:
    - 'bst' must point to a valid ConstEventBst object.
    - 'room_list' must point to a valid ConstRoomList object.
  - Postconditions: Prints the events and their assigned rooms to the standard
  output.
*/

void print_event_bst(ConstEventBst bst, ConstRoomList room_list);

/*
  Syntax Specification:
  - event_bst_every(EventBst, EventPredicate, ...) -> bool
  - types: EventBst, EventPredicate
  - internal types: EventBstNode

  Semantic Specification:
  - Function: event_bst_every(bst, predicate, ...)
  - Description: Checks if a given predicate holds true for every event in the
  binary search tree (BST).
  - Preconditions:
    - 'bst' must point to a valid EventBst object.
    - 'predicate' must be a valid function pointer to a predicate function that
  takes variable arguments.
  - Postconditions:
    - Returns true if the predicate holds true for every event in the BST, false
  otherwise.
*/
bool event_bst_every(EventBst bst, EventPredicate predicate, ...);

/*
  Syntax Specification:
  - read_event_bst_from_file(FILE*) -> EventBst
  - types: FILE*
  - internal types: EventBstNode

  Semantic Specification:
  - Function: read_event_bst_from_file(file) -> bst
  - Description: Reads event data from a file and constructs a binary search
  tree (BST) to store the events.
  - Preconditions: 'file' must point to a valid FILE object.
  - Postconditions: Returns a pointer to the newly created EventBst object
  containing the events read from the file.
*/

EventBst read_event_bst_from_file(FILE *file);

/*
  Syntax Specification:
  - save_event_bst_to_file(ConstEventBst, FILE*) -> void
  - types: ConstEventBst, FILE*
  - internal types: EventBstNode

  Semantic Specification:
  - Function: save_event_bst_to_file(bst, file)
  - Description: Saves the events stored in the binary search tree (BST) to a
  file.
  - Preconditions:
    - 'bst' must point to a valid ConstEventBst object.
    - 'file' must point to a valid FILE object opened in write mode.
  - Postconditions: Writes the events stored in the BST to the specified file.
*/
void save_event_bst_to_file(ConstEventBst bst, FILE *file);

/*
  Syntax Specification:
  - save_event_bst_to_file_sorted(ConstEventBst, FILE*) -> void
  - types: ConstEventBst, FILE*
  - internal types: EventBstNode

  Semantic Specification:
  - Function: save_event_bst_to_file_sorted(bst, file)
  - Description: Saves the events stored in the binary search tree (BST) to a
  file in sorted order.
  - Preconditions:
    - 'bst' must point to a valid ConstEventBst object.
    - 'file' must point to a valid FILE object opened in write mode.
  - Postconditions: Writes the events stored in the BST to the specified file in
  sorted order.
*/
void save_event_bst_to_file_sorted(ConstEventBst bst, FILE *file);

/*
  Syntax Specification:
  - free_event_bst(EventBst) -> void
  - types: EventBst
  - internal types: EventBstNode

  Semantic Specification:
  - Function: free_event_bst(bst)
  - Description: Frees the memory allocated for the binary search tree (BST) and
  its nodes.
  - Preconditions: 'bst' must point to a valid EventBst object.
  - Postconditions: Frees the memory allocated for the BST and its nodes.
*/

void free_event_bst(EventBst bst);

#endif // EVENT_BST_H_
