#include "room.h"
#include "logging.h" // Includi la libreria per il logging
#include "utils.h"   // Includi la libreria per le utility
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOM_NAME_SIZE                                                     \
  100 // Definisci la dimensione massima del nome della stanza
#define FORMAT_ROOM                                                            \
  "Nome: %s\n"                                                                 \
  "Posti: %u"

// Definizione della struttura per rappresentare una stanza
struct RoomStruct {
  unsigned int id;       // ID della stanza
  char *name;            // Nome della stanza
  unsigned int capacity; // Capacità della stanza (numero di posti)
};

// Funzione per creare una nuova stanza
Room new_room(const char *name, unsigned int id, unsigned int capacity) {
  // Verifica se il nome della stanza è valido
  if (name == NULL || strlen(name) == 0) {
    log_error("Attempt to create a room with invalid name.");
    return NULL_ROOM;
  }
  // Alloca memoria per la nuova stanza
  Room room = my_alloc(1, sizeof(*room));
  // Copia il nome della stanza nella struttura della stanza
  room->name = my_strdup(name);
  // Imposta l'ID e la capacità della stanza
  room->id = id;
  room->capacity = capacity;

  return room;
}

// Funzione per copiare una stanza
Room copy_room(ConstRoom room) {
  // Verifica se la stanza è valida
  if (room == NULL_ROOM) {
    log_error("Attempt to copy a NULL room.");
    return NULL_ROOM;
  }
  // Alloca memoria per la copia della stanza
  Room room_copy = my_alloc(1, sizeof(*room));
  // Copia il nome, l'ID e la capacità della stanza nella nuova struttura della
  // stanza
  room_copy->name = my_strdup(room->name);
  room_copy->id = room->id;
  room_copy->capacity = room->capacity;
  return room_copy;
}

// Funzione per verificare l'uguaglianza tra due stanze
bool are_rooms_equal(ConstRoom room_a, ConstRoom room_b) {
  // Verifica se le due stanze sono identiche o se hanno lo stesso ID
  if (room_a == room_b) {
    return true;
  }
  return room_a != NULL_ROOM && room_b != NULL_ROOM && room_a->id == room_b->id;
}

// Funzione per ottenere l'ID di una stanza
unsigned int get_room_id(ConstRoom room) {
  // Verifica se la stanza è valida e restituisce il suo ID
  if (room == NULL_ROOM) {
    log_error("Attempt to get ID of a NULL room.");
    return NULL;
  }
  return room->id;
}

// Funzione per ottenere il nome di una stanza
const char *get_room_name(ConstRoom room) {
  // Verifica se la stanza è valida e restituisce il suo nome
  if (room == NULL_ROOM) {
    log_error("Attempt to get name of a NULL room.");
    return NULL;
  }
  return room->name;
}

// Funzione per stampare i dettagli di una stanza
void print_room(ConstRoom room) {
  // Verifica se la stanza è valida e stampa il suo nome e la sua capacità
  if (room == NULL_ROOM) {
    log_error("Attempt to print a NULL room.");
    return;
  }
  printf(FORMAT_ROOM, room->name, room->capacity);
}

// Funzione per leggere una nuova stanza da input
Room read_room(unsigned int id) {
  // Variabile per memorizzare il nome della stanza letto da input
  char name[MAX_ROOM_NAME_SIZE + 2] = {0};
  // Loop fino a quando non viene letto un nome valido per la stanza
  while (1) {
    char temp[MAX_ROOM_NAME_SIZE + 2] = {0};
    printf("Inserisci nome sala [Max %d caratteri]: ", MAX_ROOM_NAME_SIZE);
    // Leggi il nome della stanza da input
    if (read_line(temp, MAX_ROOM_NAME_SIZE + 2)) {
      printf("Errore durante la lettura del nome.\n");
      continue;
    }
    // Rimuovi gli spazi vuoti dal nome letto
    trim_whitespaces(name, temp, MAX_ROOM_NAME_SIZE + 2);
    // Se il nome è vuoto, richiedi un nuovo input
    if (strlen(name) == 0) {
      continue;
    }
    break;
  }
  // Leggi la capacità della stanza da input
  ResultInt res = {0};
  do {
    printf("Inserisci numero posti sala: ");
    res = read_int();

  } while (res.error_code || res.value < 0);
  // Crea una nuova stanza con il nome e la capacità letti da input
  Room room = new_room(name, id, res.value);
  return room;
}

// Funzione per salvare i dettagli di una stanza su file
void save_room_to_file(ConstRoom room, FILE *file) {
  // Verifica se la stanza e il file sono validi
  if (room == NULL_ROOM) {
    log_error("Attempt to save NULL room to file.");
    return;
  }

  if (file == NULL) {
    log_error("Attempt to write room to NULL file.");
    return;
  }

  // Scrivi l'ID, il nome e la capacità della stanza sul file
  fprintf(file, "%u\n", room->id);
  fprintf(file, "%s\n", room->name);
  fprintf(file, "%u\n", room->capacity);
}

// Funzione per leggere i dettagli di una stanza da file
Room read_room_from_file(FILE *file) {
  // Verifica se il file è valido
  if (file == NULL) {
    log_error("Attempt to read room from NULL file.");
    return NULL_ROOM;
  }

  // Dichiara e inizializza variabili per memorizzare l'ID, il nome e la
  // capacità della stanza letti da file
  unsigned int id = 0;
  if (fscanf(file, "%u", &id) != 1) {
    log_error("Failed to read room ID from file.");
    clean_file(file);
    return NULL_ROOM;
  }

  clean_file(file);

  char name[MAX_ROOM_NAME_SIZE + 2];
  if (read_line_from_file(name, MAX_ROOM_NAME_SIZE + 2, file) != 0) {
    log_error("Failed to read room name from file.");
    return NULL_ROOM;
  }

  unsigned int capacity = 0;
  if (fscanf(file, "%u", &capacity) != 1) {
    log_error("Failed to read room capacity from file.");
    clean_file(file);
    return NULL_ROOM;
  }

  // Crea una nuova stanza con l'ID, il nome e la capacità letti da file
  return new_room(name, id, capacity);
}

// Funzione per liberare la memoria allocata per una stanza
void free_room(Room room) {
  if (room == NULL_ROOM) {
    log_error("Attempt to free a NULL room.");
    return;
  }
  // Libera la memoria allocata per il nome della stanza e poi per la stanza
  // stessa
  free(room->name);
  free(room);
}
