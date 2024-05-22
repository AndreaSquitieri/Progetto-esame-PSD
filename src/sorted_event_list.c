#include "sorted_event_list.h"
#include "event_list.h"
#include "room_list.h"
#include "utils.h"
#include <stdlib.h>

struct SortedEventListStruct {
  EventList events;
};

SortedEventList new_sorted_event_list(void) {
  SortedEventList sorted_list = my_alloc(1, sizeof(*sorted_list));
  sorted_list->events = new_event_list();
  return sorted_list;
}

/**
 * @brief Cerca la posizione di inserimento di un evento utilizzando la ricerca
 * binaria.
 *
 * @param sorted_list La lista di eventi ordinata in cui eseguire la ricerca.
 * @param value L'evento per cui cercare la posizione di inserimento.
 * @param low L'indice inferiore della ricerca.
 * @param high L'indice superiore della ricerca.
 * @return L'indice di inserimento dell'evento.
 */
static int binary_search_position(SortedEventList sorted_list, Event value,
                                  int low, int high) {
  while (low <= high) {
    int mid = low + (high - low) / 2;
    int cmp_result =
        cmp_event(get_at_event_list(sorted_list->events, mid), value);
    if (cmp_result == 0) {
      return mid + 1; // Insert after existing event if found
    }
    if (cmp_result < 0) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return low; // Insert at low if not found
}

int insert_sorted_event_list(SortedEventList sorted_list, Event value) {
  int low = 0;
  int high = get_size_event_list(sorted_list->events) - 1;
  int insertion_pos = binary_search_position(sorted_list, value, low, high);

  return insert_event_list(sorted_list->events, insertion_pos, value);
}

Event remove_at_sorted_event_list(SortedEventList sorted_list, int pos) {
  return remove_event_list(sorted_list->events, pos);
}

Event get_at_sorted_event_list(SortedEventList sorted_list, int pos) {
  return get_at_event_list(sorted_list->events, pos);
}

int get_size_sorted_event_list(ConstSortedEventList sorted_list) {
  return get_size_event_list(sorted_list->events);
}

void print_sorted_event_list(ConstSortedEventList sorted_list,
                             RoomList room_list) {
  for (int i = 0; i < get_size_event_list(sorted_list->events); i++) {
    Event event = get_at_event_list(sorted_list->events, i);
    print_event(event, get_room_by_id(room_list, get_event_room_id(event)));
  }
}

void free_sorted_event_list(SortedEventList sorted_list) {
  free_event_list(sorted_list->events);
  free(sorted_list);
}
