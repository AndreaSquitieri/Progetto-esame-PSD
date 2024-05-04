#ifndef EVENT_LIST_H_
#define EVENT_LIST_H_

#include <mevent.h>
#include <stdbool.h>
#include <sys/cdefs.h>

// Dichiarazione anticipata di EventListStruct per l'utilizzo di typedef
typedef struct EventListStruct *EventList;
typedef const struct EventListStruct *ConstEventList;

/**
 * @brief Alloca la memoria per una nuova lista di eventi (EventList) e la
 * inizializza con una capacità iniziale.
 *
 * @return Un puntatore alla nuova EventList appena allocata.
 *
 * Specifica Sintattica:
 * - new_event_list() -> EventList
 *
 * Specifica Semantica:
 * - new_event_list() -> lista
 *
 *   Questa funzione alloca la memoria per una nuova EventList e la inizializza
 * con una capacità predefinita.
 *
 *   Precondizioni:
 *     - Nessuna.
 *
 *   Postcondizioni:
 *     - La memoria è allocata per l'EventList, inizializzata con una capacità
 * predefinita.
 */
EventList new_event_list(void);

/**
 * @brief Verifica se la lista di eventi (EventList) data è vuota.
 *
 * @param list Un puntatore valido a una EventList.
 * @return true se l'EventList è vuota, false altrimenti.
 *
 * Specifica Sintattica:
 * - is_event_list_empty(EventList) -> bool
 *
 * Specifica Semantica:
 * - is_event_list_empty(list) -> vuota
 *
 *   Questa funzione determina se l'EventList è vuota.
 *
 *   Precondizioni:
 *     - 'list' punta a una EventList valido.
 *
 *   Postcondizioni:
 *     - Nessuna.
 */
bool is_event_list_empty(EventList list);

/**
 * @brief Aggiunge un evento alla fine della EventList.
 *
 * @param list Un puntatore valido a una EventList.
 * @param value L'evento da aggiungere.
 *
 * Specifica Sintattica:
 * - cons_event_list(EventList, Event) -> void
 *
 * Specifica Semantica:
 * - cons_event_list(list, value) -> void
 *
 *   Questa funzione aggiunge un evento alla fine della EventList.
 *
 *   Precondizioni:
 *     - 'list' punta a una EventList valido.
 *     - 'value' è un evento valido.
 *
 *   Postcondizioni:
 *     - L'evento 'value' viene aggiunto alla fine della EventList.
 */
void cons_event_list(EventList list, Event value);

/**
 * @brief Rimuove l'ultimo evento nella EventList.
 *
 * @param list Un puntatore valido a una EventList.
 * @return L'ultimo evento nella EventList, o NULL_EVENT se la EventList è
 * vuota.
 *
 * Specifica Sintattica:
 * - tail_event_list(EventList) -> Event
 *
 * Specifica Semantica:
 * - tail_event_list(list) -> ultimo_evento
 *   Questa funzione rimuove l'ultimo evento nella EventList.
 *
 *   Precondizioni:
 *     - 'list' punta a una EventList valido.
 *
 *   Postcondizioni:
 *     - La dimensione dell'EventList viene decrementata se non è vuota.
 */
Event tail_event_list(EventList list);

/**
 * @brief Recupera il primo evento nella EventList.
 *
 * @param list Un puntatore valido a una EventList.
 * @return Il primo evento nella EventList, o NULL_EVENT se la EventList è
 * vuota.
 *
 * Specifica Sintattica:
 * - get_first_event_list(EventList) -> Event
 *
 * Specifica Semantica:
 * - get_first_event_list(list) -> primo_evento
 *   Questa funzione recupera il primo evento nella EventList.
 *
 *   Precondizioni:
 *     - 'list' punta a una EventList valido.
 *
 *   Postcondizioni:
 *     - Nessuna.
 */
Event get_first_event_list(EventList list);

/**
 * @brief Restituisce la dimensione corrente della EventList.
 *
 * @param list Un puntatore valido a una EventList.
 * @return Il numero di eventi attualmente nella EventList.
 *
 * Specifica Sintattica:
 * - get_size_event_list(EventList) -> int
 *
 * Specifica Semantica:
 * - get_size_event_list(list) -> dimensione_corrente
 *   Questa funzione restituisce la dimensione corrente della EventList.
 *
 *   Precondizioni:
 *     - 'list' punta a una EventList valido.
 *
 *   Postcondizioni:
 *     - Nessuna.
 */
int get_size_event_list(EventList list);

/**
 * @brief Trova la posizione di un evento specifico nella EventList.
 *
 * @param list Un puntatore valido a una EventList.
 * @param to_search L'evento da cercare.
 * @return La posizione dell'evento nella EventList, o -1 se l'evento non è
 * trovato.
 *
 * Specifica Sintattica:
 * - get_pos_event_list(EventList, Event) -> int
 *
 * Specifica Semantica:
 * - get_pos_event_list(list, to_search) -> posizione
 *   Questa funzione cerca la posizione di un evento specifico nella EventList.
 *
 *   Precondizioni:
 *     - 'list' punta a una EventList valido.
 *     - 'to_search' è un evento valido.
 *
 *   Postcondizioni:
 *     - Nessuna.
 */
int get_pos_event_list(EventList list, Event to_search);

/**
 * @brief Recupera l'evento in una posizione specifica nella EventList.
 *
 * @param list Un puntatore valido a una EventList.
 * @param pos L'indice dell'evento da recuperare.
 * @return L'evento all'indice specificato, o NULL_EVENT se l'indice è fuori dai
 * limiti della EventList.
 *
 * Specifica Sintattica:
 * - get_at_event_list(EventList, int) -> Event
 *
 * Specifica Semantica:
 * - get_at_event_list(list, pos) -> evento_recuperato
 *   Questa funzione recupera l'evento in una posizione specifica nella
 * EventList.
 *
 *   Precondizioni:
 *     - 'list' punta a una EventList valido.
 *     - 'pos' è un indice valido.
 *
 *   Postcondizioni:
 *     - Nessuna.
 */
Event get_at_event_list(EventList list, int pos);

/**
 * @brief Inserisce un evento in una posizione specifica nella EventList.
 *
 * @param list Un puntatore valido a una EventList.
 * @param pos L'indice in cui inserire l'evento.
 * @param event L'evento da inserire.
 * @return 0 in caso di successo, -1 se la posizione è fuori dai limiti.
 *
 * Specifica Sintattica:
 * - insert_event_list(EventList, int, Event) -> int
 *
 * Specifica Semantica:
 * - insert_event_list(list, pos, event) -> risultato_inserimento
 *   Questa funzione inserisce un evento in una posizione specifica nella
 * EventList.
 *
 *   Precondizioni:
 *     - 'list' punta a una EventList valido.
 *     - 'pos' è un indice valido.
 *     - 'event' è un evento valido.
 *
 *   Postcondizioni:
 *     - L'evento 'event' è inserito nella posizione 'pos' nella EventList, o la
 * EventList rimane invariata se 'pos' è fuori dai limiti.
 */
int insert_event_list(EventList list, int pos, Event event);

/**
 * @brief Rimuove un evento da una posizione specifica nella EventList.
 *
 * @param list Un puntatore valido a una EventList.
 * @param pos L'indice dell'evento da rimuovere.
 * @return L'evento rimosso, o NULL_EVENT se la posizione è fuori dai limiti.
 *
 * Specifica Sintattica:
 * - remove_event_list(EventList, int) -> Event
 *
 * Specifica Semantica:
 * - remove_event_list(list, pos) -> evento_rimosso
 *   Questa funzione rimuove un evento da una posizione specifica nella
 * EventList.
 *
 *   Precondizioni:
 *     - 'list' punta a una EventList valido.
 *     - 'pos' è un indice valido.
 *
 *   Postcondizioni:
 *     - L'evento in posizione 'pos' è rimosso dalla EventList, o la EventList
 * rimane invariata se 'pos' è fuori dai limiti.
 */
Event remove_event_list(EventList list, int pos);

/**
 * @brief Libera la memoria allocata per l'EventList.
 *
 * Specifica Sintattica:
 * - free_event_list(EventList) -> void
 *
 * Specifica Semantica:
 * - free_event_list(list)
 *   Libera la memoria allocata per l'EventList.
 *
 *   Precondizioni:
 *     - 'list' punta a un EventList valido.
 *
 *   Postcondizioni:
 *     - La memoria allocata per l'EventList è liberata.
 */
void free_event_list(EventList list);

#endif // EVENT_LIST_H_
