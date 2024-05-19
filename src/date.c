#include "date.h"
#include "logging.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Costanti per il tempo
#define MINUTES_IN_HOUR 60
#define HOURS_IN_DAY 24
#define MONTHS_IN_YEAR 12

// Formato di stampa della data
#define FORMAT_DATE "%d %s %d, %02d:%02d"
#define DATE_BUFFER_SIZE 32

// Numero di giorni in ogni mese
#define DAYS_IN_MONTHS_INITIALIZER                                             \
  { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
#define MONTH_NAMES_INITIALIZER                                                \
  {                                                                            \
    "Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno", "Luglio",    \
        "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre"               \
  }

// Array dei giorni in ogni mese e nomi dei mesi
static const unsigned char days_in_months[] = DAYS_IN_MONTHS_INITIALIZER;
static const char *const month_names[] = MONTH_NAMES_INITIALIZER;

// Enumerazione dei mesi
typedef enum {
  JANUARY = 1,
  FEBRUARY,
  MARCH,
  APRIL,
  MAY,
  JUNE,
  JULY,
  AUGUST,
  SEPTEMBER,
  OCTOBER,
  NOVEMBER,
  DECEMBER
} Month;

// Struttura della data
struct DateStruct {
  unsigned char minutes;
  unsigned char hour;
  unsigned char day;
  unsigned char month;
  unsigned short year;
};

// Funzione per verificare se un anno è bisestile
static bool is_leap_year(unsigned short year) {
  return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}

// Funzione per verificare se una data è valida
static bool is_valid_date(ConstDate date) {
  if (date == NULL_DATE) {
    return false;
  }
  if (date->minutes >= MINUTES_IN_HOUR || date->hour >= HOURS_IN_DAY) {
    return false;
  }
  if (date->day == 0 || date->month == 0 || date->month > MONTHS_IN_YEAR) {
    return false;
  }
  if (date->month == FEBRUARY && is_leap_year(date->year)) {
    return date->day <= (days_in_months[FEBRUARY - 1] + 1);
  }
  return date->day <= days_in_months[date->month - 1];
}

// Funzione per creare una nuova data
Date new_date(unsigned char minutes, unsigned char hour, unsigned char day,
              unsigned char month, unsigned short year) {

  // Allocazione della memoria per la data
  Date date = my_alloc(1, sizeof(*date));

  // Inizializzazione dei campi della data
  date->minutes = minutes;
  date->hour = hour;
  date->day = day;
  date->month = month;
  date->year = year;

  // Verifica se la data è valida, altrimenti logga un errore e restituisce NULL
  if (!is_valid_date(date)) {
    log_error("Attempt to create an invalid date.");
    free(date);
    return NULL_DATE;
  }
  return date;
}

// Funzione per creare una copia della data
Date copy_date(ConstDate date) {
  if (date == NULL_DATE) {
    log_error("Attempt to copy a NULL date.");
    return NULL_DATE;
  }
  return new_date(date->minutes, date->hour, date->day, date->month,
                  date->year);
}

// Funzione per comparare i componenti di una data
static inline int cmp_date_component(unsigned int a, unsigned int b) {
  return (a > b) - (a < b);
}

// Funzione per comparare le date
int cmp_date(ConstDate date_a, ConstDate date_b) {
  if (date_a == NULL_DATE && date_b == NULL_DATE) {
    return 0;
  }
  if (date_a == NULL_DATE) {
    return -1;
  }
  if (date_b == NULL_DATE) {
    return 1;
  }

  // Comparazione dei componenti delle date in ordine
  int result = cmp_date_component(date_a->year, date_b->year);
  if (result != 0) {
    return result;
  }
  result = cmp_date_component(date_a->month, date_b->month);
  if (result != 0) {
    return result;
  }

  result = cmp_date_component(date_a->day, date_b->day);
  if (result != 0) {
    return result;
  }

  result = cmp_date_component(date_a->hour, date_b->hour);
  if (result != 0) {
    return result;
  }

  return cmp_date_component(date_a->minutes, date_b->minutes);
}

// Funzione per ottenere il nome del mese
static const char *get_month_name(ConstDate date) {
  return month_names[date->month - 1];
}

// Funzione per stampare la data su stdout
void print_date(ConstDate date) {
  if (date == NULL_DATE) {
    log_error("Attempt to print a NULL date.");
    return;
  }
  printf(FORMAT_DATE, date->day, get_month_name(date), date->year, date->hour,
         date->minutes);
}

// Funzione per leggere una data da stdin
Date read_date(void) {
  char temp[DATE_BUFFER_SIZE] = {0};
  if (read_line(temp, DATE_BUFFER_SIZE)) {
    return NULL_DATE;
  }
  int day = 0;
  int month = 0;
  int year = 0;
  int hour = 0;
  int minutes = 0;
  // Parsing della stringa per ottenere i componenti della data
  if (sscanf(temp, "%d/%d/%d %d:%d", &day, &month, &year, &hour, &minutes) !=
      5) {
    return NULL_DATE;
  }
  // Verifica che I valori passati non siano negativi
  if (day < 0 || month < 0 || year < 0 || hour < 0 || minutes < 0) {
    return NULL_DATE;
  }
  // Creazione della data
  Date date = new_date(minutes, hour, day, month, year);
  return date;
}

// Funzione per salvare la data su file
void save_date_to_file(ConstDate date, FILE *file) {
  if (date == NULL_DATE) {
    log_error("Attempt to save NULL date to file");
    return;
  }
  if (file == NULL) {
    log_error("Attempt to write date to NULL file");
    return;
  }

  // Scrittura dei componenti della data sul file
  if (fprintf(file, "%d %d %d %d %d\n", date->minutes, date->hour, date->day,
              date->month, date->year) < 0) {
    log_error("Failed to write date components to file.");
  }
}

// Funzione per leggere una data da file
Date read_date_from_file(FILE *file) {
  if (file == NULL) {
    log_error("Attempt to read date from NULL file");
    return NULL_DATE;
  }

  int day = 0;
  int month = 0;
  int year = 0;
  int hour = 0;
  int minutes = 0;

  // Lettura dei componenti della data dal file
  if (fscanf(file, "%d %d %d %d %d", &minutes, &hour, &day, &month, &year) !=
      5) {
    log_error("Failed to read date components from file.");
    return NULL_DATE;
  }

  // Creazione della data
  Date date = new_date(minutes, hour, day, month, year);

  return date;
}

// Funzione per liberare la memoria allocata per la data
void free_date(Date date) {
  if (date == NULL_DATE) {
    log_error("Attempt to free a NULL date.");
    return;
  }
  free(date);
}
