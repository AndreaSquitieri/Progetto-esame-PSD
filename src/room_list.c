#include "room_list.h"
#include "logging.h"
#include "room.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

#define INIT_CAPACITY 8 // Capacità iniziale della lista
#define GROWTH_FACTOR 2 // Fattore di crescita per ridimensionare l'array

// Struttura che rappresenta una lista di stanze
struct RoomListStruct {
  Room *array;  // Array dinamico di stanze
  int capacity; // Capacità corrente dell'array
  int size;     // Numero di stanze attualmente nella lista
};

// Funzione statica per aumentare la capacità della lista
static void room_list_increase_capacity(RoomList list) {
  list->capacity *= GROWTH_FACTOR; // Raddoppia la capacità
  list->array = my_realloc(list->array, list->capacity, sizeof(Room));
}

// Funzione per creare una nuova lista di stanze
RoomList new_room_list(void) {
  RoomList new_list = my_alloc(
      1, sizeof(*new_list)); // Alloca memoria per la struttura della lista
  new_list->array = my_alloc(
      INIT_CAPACITY, sizeof(Room));   // Alloca memoria per l'array di stanze
  new_list->capacity = INIT_CAPACITY; // Imposta la capacità iniziale
  new_list->size = 0;                 // Inizializza la dimensione a 0
  return new_list;
}

// Funzione per verificare se la lista è vuota
bool is_room_list_empty(ConstRoomList list) {
  return list == NULL ||
         list->size == 0; // Controlla se la lista è NULL o vuota
}

// Funzione per ottenere la dimensione della lista
int get_size_room_list(ConstRoomList list) {
  if (list == NULL_ROOM_LIST) { // Verifica se la lista è NULL
    log_error("Attempt to get size of a NULL room list.");
    return 0;
  }
  return list->size; // Ritorna la dimensione della lista
}

// Funzione per aggiungere una stanza alla lista
void cons_room_list(RoomList list, Room room) {
  if (list == NULL_ROOM_LIST ||
      room == NULL_ROOM) { // Verifica se la lista o la stanza sono NULL
    log_error("Attempt to add a room to a NULL room list or add a NULL room.");
    return;
  }
  if (list->capacity == list->size) {  // Verifica se la capacità è esaurita
    room_list_increase_capacity(list); // Aumenta la capacità della lista
  }
  list->array[list->size] = room; // Aggiungi la stanza alla lista
  list->size += 1;                // Incrementa la dimensione della lista
}

// Funzione per rimuovere l'ultima stanza dalla lista e ritornarla
Room tail_room_list(RoomList list) {
  if (is_room_list_empty(list)) { // Verifica se la lista è vuota
    log_error("Attempt to remove a room from an empty or NULL room list.");
    return NULL_ROOM;
  }
  list->size -= 1;                // Decrementa la dimensione della lista
  return list->array[list->size]; // Ritorna l'ultima stanza
}

// Funzione per ottenere la prima stanza della lista
Room get_first_room_list(RoomList list) {
  return get_at_room_list(
      list, 0); // Usa get_at_room_list per ottenere la prima stanza
}

// Funzione per ottenere una stanza in una posizione specifica della lista
Room get_at_room_list(RoomList list, int pos) {
  if (list == NULL_ROOM_LIST) { // Verifica se la lista è NULL
    log_error("Attempt to get a room from a NULL room list.");
    return NULL_ROOM;
  }
  if (pos >= list->size || pos < 0) { // Verifica se la posizione è valida
    log_error("Attempt to get a room at an invalid position.");
    return NULL_ROOM;
  }
  return list->array[pos]; // Ritorna la stanza alla posizione specificata
}

// Funzione per ottenere una stanza per ID dalla lista
Room get_room_by_id(RoomList list, unsigned int room_id) {
  if (list == NULL_ROOM_LIST) { // Verifica se la lista è NULL
    log_error("Attempt to get a room by ID from a NULL room list.");
    return NULL_ROOM;
  }
  for (int i = 0; i < list->size; i++) { // Scorri le stanze nella lista
    Room current_room = list->array[i];
    if (get_room_id(current_room) == room_id) { // Confronta gli ID delle stanze
      return current_room;                      // Ritorna la stanza trovata
    }
  }
  return NULL_ROOM; // Ritorna NULL_ROOM se la stanza non viene trovata
}

// Funzione per rimuovere una stanza in una posizione specifica della lista
Room remove_at_room_list(RoomList list, int pos) {
  if (list == NULL_ROOM_LIST) { // Verifica se la lista è NULL
    log_error("Attempt to remove a room from a NULL room list.");
    return NULL_ROOM;
  }
  if (pos >= list->size || pos < 0) { // Verifica se la posizione è valida
    log_error("Attempt to remove a room at an invalid position.");
    return NULL_ROOM;
  }
  Room temp = list->array[pos]; // Salva temporaneamente la stanza da rimuovere
  list->size -= 1;              // Decrementa la dimensione della lista
  for (int i = pos; i < list->size; i++) { // Sposta le stanze successive
    list->array[i] = list->array[i + 1];
  }
  return temp; // Ritorna la stanza rimossa
}

// Funzione per ottenere la posizione di una stanza nella lista
int get_pos_room_list(ConstRoomList list, ConstRoom to_search) {
  if (list == NULL_ROOM_LIST ||
      to_search == NULL_ROOM) { // Verifica se la lista o la stanza sono NULL
    log_error(
        "Attempt to search in a NULL room list or search for a NULL room.");
    return -1;
  }
  for (int i = 0; i < list->size; i++) { // Scorri le stanze nella lista
    if (are_rooms_equal(list->array[i], to_search)) { // Confronta le stanze
      return i; // Ritorna la posizione trovata
    }
  }
  return -1; // Ritorna -1 se la stanza non viene trovata
}

// Funzione per stampare tutte le stanze nella lista
void print_room_list(ConstRoomList list) {
  if (list == NULL_ROOM_LIST) { // Verifica se la lista è NULL
    log_error("Attempt to print a NULL room list.");
    return;
  }
  for (int i = 0; i < list->size; i++) { // Scorri le stanze nella lista
    printf("[Sala %d]\n", i + 1);        // Stampa l'indice della stanza
    print_room(list->array[i]);          // Stampa la stanza
    puts("");                            // Aggiunge una riga vuota
  }
}

// Funzione per salvare la lista di stanze in un file
void save_room_list_to_file(ConstRoomList list, FILE *file) {
  if (file == NULL) { // Verifica se il file è NULL
    log_error("Attempt to save a room list to a NULL file.");
    return;
  }
  if (list == NULL_ROOM_LIST) { // Verifica se la lista è NULL
    log_error("Attempt to save a NULL room list to a file.");
    return;
  }

  fprintf(file, "%d\n", list->size); // Salva la dimensione della lista nel file

  for (int i = 0; i < list->size; i++) {     // Scorri le stanze nella lista
    save_room_to_file(list->array[i], file); // Salva ogni stanza nel file
  }
}

// Funzione per leggere una lista di stanze da un file
RoomList read_room_list_from_file(FILE *file) {
  if (file == NULL) { // Verifica se il file è NULL
    log_error("Attempt to read a room list from a NULL file.");
    return NULL_ROOM_LIST;
  }

  int num_rooms = 0;

  if (fscanf(file, "%d", &num_rooms) !=
      1) { // Legge il numero di stanze dal file
    log_error("Failed to read the number of rooms from the file.");
    clean_file(file);
    return NULL_ROOM_LIST;
  }

  RoomList list = new_room_list(); // Crea una nuova lista di stanze
  if (list == NULL_ROOM_LIST) {    // Verifica se la lista è NULL
    log_error("Failed to create a new room list.");
    return NULL_ROOM_LIST;
  }

  for (int i = 0; i < num_rooms; i++) {    // Scorri il numero di stanze
    Room room = read_room_from_file(file); // Legge ogni stanza dal file
    if (room == NULL_ROOM) {               // Verifica se la stanza è NULL
      log_error("Failed to read a room from the file.");
      free_room_list(list); // Libera la memoria della lista
      return NULL_ROOM_LIST;
    }
    cons_room_list(list, room); // Aggiunge la stanza alla lista
  }

  return list; // Ritorna la lista letta
}

// Funzione per liberare la memoria della lista di stanze
void free_room_list(RoomList list) {
  if (list == NULL) { // Verifica se la lista è NULL
    log_error("Attempt to free a NULL room list.");
    return;
  }
  for (int i = 0; i < list->size; i++) { // Scorri le stanze nella lista
    free_room(list->array[i]);           // Libera la memoria di ogni stanza
  }
  free(list->array); // Libera la memoria dell'array di stanze
  free(list);        // Libera la memoria della struttura della lista
}
