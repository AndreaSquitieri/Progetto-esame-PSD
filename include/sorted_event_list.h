#ifndef SORTED_EVENT_LIST_H_
#define SORTED_EVENT_LIST_H_

#include "mevent.h"
#include "room_list.h"

typedef struct SortedEventListStruct *SortedEventList;
typedef const struct SortedEventListStruct *ConstSortedEventList;

// Function prototypes

/**
 * @brief Crea e restituisce una nuova lista di eventi ordinata.
 *
 * @return Un puntatore alla nuova lista di eventi ordinata (SortedEventList), o
 * NULL in caso di errore.
 *
 * Specifica Sintattica:
 * - new_sorted_event_list() -> SortedEventList
 *
 * Specifica Semantica:
 * - new_sorted_event_list() -> lista_ordinata
 *   Questa funzione crea e restituisce una nuova lista di eventi ordinata.
 *
 *   Precondizioni:
 *     - Nessuna.
 *
 *   Postcondizioni:
 *     - Se la creazione della lista di eventi ordinata ha avuto successo, viene
 * restituito un puntatore ad essa.
 *     - Se si verifica un errore durante la creazione della lista, viene
 * restituito NULL.
 */
SortedEventList new_sorted_event_list(void);

/**
 * @brief Inserisce un evento ordinato nella lista di eventi ordinata.
 *
 * @param sorted_list La lista di eventi ordinata in cui inserire l'evento.
 * @param value L'evento da inserire.
 * @return 0 in caso di successo, -1 se si verifica un errore durante
 * l'inserimento.
 *
 * Specifica Sintattica:
 * - insert_sorted_event_list(SortedEventList, Event) -> int
 *
 * Specifica Semantica:
 * - insert_sorted_event_list(sorted_list, value) -> risultato_inserimento
 *   Questa funzione inserisce un evento ordinato nella lista di eventi
 * ordinata. Utilizza un approccio di ricerca binaria per trovare la posizione
 * corretta dell'evento all'interno della lista ordinata e quindi inserisce
 * l'evento. Se l'inserimento ha successo, restituisce 0, altrimenti restituisce
 * -1.
 *
 *   Precondizioni:
 *     - 'sorted_list' punta a una lista di eventi ordinata valida.
 *     - 'value' è un evento valido.
 *
 *   Postcondizioni:
 *     - L'evento 'value' è inserito nella lista di eventi ordinata mantenendo
 * l'ordinamento, o la lista rimane invariata in caso di errore durante
 * l'inserimento.
 */
int insert_sorted_event_list(SortedEventList sorted_list, Event value);

/**
 * @brief Rimuove l'evento dalla posizione specificata nella lista di eventi
 * ordinata.
 *
 * @param sorted_list La lista di eventi ordinata da cui rimuovere l'evento.
 * @param pos La posizione dell'evento da rimuovere.
 * @return L'evento rimosso, o NULL_EVENT se la posizione è fuori dai limiti.
 *
 * Specifica Sintattica:
 * - remove_at_sorted_event_list(SortedEventList, int) -> Event
 *
 * Specifica Semantica:
 * - remove_at_sorted_event_list(sorted_list, pos) -> evento_rimosso
 *   Questa funzione rimuove l'evento dalla posizione specificata nella lista di
 * eventi ordinata.
 *
 *   Precondizioni:
 *     - 'sorted_list' punta a una lista di eventi ordinata valida.
 *     - 'pos' è un indice valido all'interno della lista di eventi ordinata.
 *
 *   Postcondizioni:
 *     - L'evento in posizione 'pos' è rimosso dalla lista di eventi ordinata.
 *     - Se 'pos' è fuori dai limiti della lista, la lista rimane invariata e
 * viene restituito NULL_EVENT.
 */
Event remove_at_sorted_event_list(SortedEventList sorted_list, int pos);

/**
 * @brief Restituisce l'evento alla posizione specificata nella lista di eventi
 * ordinata.
 *
 * @param sorted_list La lista di eventi ordinata da cui recuperare l'evento.
 * @param pos La posizione dell'evento da recuperare.
 * @return L'evento alla posizione specificata, o NULL_EVENT se la posizione è
 * fuori dai limiti.
 *
 * Specifica Sintattica:
 * - get_at_sorted_event_list(SortedEventList, int) -> Event
 *
 * Specifica Semantica:
 * - get_at_sorted_event_list(sorted_list, pos) -> evento_recuperato
 *   Questa funzione restituisce l'evento alla posizione specificata nella lista
 * di eventi ordinata.
 *
 *   Precondizioni:
 *     - 'sorted_list' punta a una lista di eventi ordinata valida.
 *     - 'pos' è un indice valido all'interno della lista di eventi ordinata.
 *
 *   Postcondizioni:
 *     - Se l'indice 'pos' è valido, viene restituito l'evento corrispondente.
 *     - Se 'pos' è fuori dai limiti della lista, viene restituito NULL_EVENT.
 */
Event get_at_sorted_event_list(SortedEventList sorted_list, int pos);

/**
 * @brief Restituisce la dimensione della lista di eventi ordinata.
 *
 * @param sorted_list La lista di eventi ordinata di cui calcolare la
 * dimensione.
 * @return La dimensione della lista di eventi ordinata.
 *
 * Specifica Sintattica:
 * - get_size_sorted_event_list(ConstSortedEventList) -> int
 *
 * Specifica Semantica:
 * - get_size_sorted_event_list(sorted_list) -> dimensione
 *   Questa funzione restituisce la dimensione della lista di eventi ordinata.
 *
 *   Precondizioni:
 *     - 'sorted_list' punta a una lista di eventi ordinata valida.
 *
 *   Postcondizioni:
 *     - Viene restituita la dimensione della lista di eventi ordinata.
 */
int get_size_sorted_event_list(ConstSortedEventList sorted_list);

/**
 * @brief Stampa la lista di eventi ordinata.
 *
 * @param sorted_list La lista di eventi ordinata da stampare.
 *
 * Specifica Sintattica:
 * - print_sorted_event_list(ConstSortedEventList) -> void
 *
 * Specifica Semantica:
 * - print_sorted_event_list(sorted_list) -> void
 *   Questa funzione stampa la lista di eventi ordinata.
 *
 *   Precondizioni:
 *     - 'sorted_list' punta a una lista di eventi ordinata valida.
 *
 *   Postcondizioni:
 *     - La lista di eventi ordinata viene stampata.
 */
void print_sorted_event_list(ConstSortedEventList sorted_list,
                             RoomList room_list);

/**
 * @brief Libera la memoria allocata per la lista di eventi ordinata.
 *
 * @param sorted_list La lista di eventi ordinata da liberare.
 *
 * Specifica Sintattica:
 * - free_sorted_event_list(SortedEventList) -> void
 *
 * Specifica Semantica:
 * - free_sorted_event_list(sorted_list)
 *   Questa funzione libera la memoria allocata per la lista di eventi ordinata.
 *
 *   Precondizioni:
 *     - 'sorted_list' punta a una lista di eventi ordinata valida.
 *
 *   Postcondizioni:
 *     - La memoria allocata per la lista di eventi ordinata viene liberata.
 */
void free_sorted_event_list(SortedEventList sorted_list);

#endif // SORTED_EVENT_LIST_H
