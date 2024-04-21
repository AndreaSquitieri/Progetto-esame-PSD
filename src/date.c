#include "date.h"
#include "logging.h"
#include <stdio.h>
#include <stdlib.h>
#define MONTHS 12
#define MONTH_DAYS_INITIALIZER                                                 \
  { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }

#define MONTH_NAMES_INITIALIZER                                                \
  {                                                                            \
    "Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno", "Luglio",    \
        "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre"               \
  }
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
} MonthNames;

struct DateStruct {
  unsigned char minutes;
  unsigned char hour;
  unsigned char day;
  unsigned char month;
  unsigned short year;
};

static int const months[] = MONTH_DAYS_INITIALIZER;
static const char *const month_names[] = MONTH_NAMES_INITIALIZER;

static const char *get_month_name(ConstDate date) {
  return month_names[date->month - 1];
}

Date new_date(unsigned char minutes, unsigned char hour, unsigned char day,
              unsigned char month, unsigned short year) {
  Date date = malloc(sizeof(*date));
  if (date == NULL) {
    log_error("Allocazione oggetto 'Date' fallita.");
    return NULL;
  }
  date->minutes = minutes;
  date->hour = hour;
  date->day = day;
  date->month = month;
  date->year = year;

  if (!is_valid_date(date)) {
    log_error("Tentativo di creazione date non valida");
    free(date);
    return NULL;
  }
  return date;
}

static inline int cmp_date_component(unsigned int a, unsigned int b) {
  if (a < b) {
    return -1;
  }
  if (a == b) {
    return 0;
  }
  return 1;
}

int cmp_date(ConstDate date_a, ConstDate date_b) {
  // Compare 'year'
  int result = cmp_date_component(date_a->year, date_b->year);
  if (result != 0) {
    return result;
  }
  // Compare 'month'
  result = cmp_date_component(date_a->month, date_b->month);
  if (result != 0) {
    return result;
  }

  // Compare 'day'
  result = cmp_date_component(date_a->day, date_b->day);
  if (result != 0) {
    return result;
  }

  // Compare 'hour'
  result = cmp_date_component(date_a->hour, date_b->hour);
  if (result != 0) {
    return result;
  }

  // Compare 'minutes'
  return cmp_date_component(date_a->minutes, date_b->minutes);
}

#define FORMAT_DATE "%d %s %d, %02d:%02d"
char *to_string_date(ConstDate date) {
  int len = snprintf(NULL, 0, FORMAT_DATE, date->day, get_month_name(date),
                     date->year, date->hour, date->minutes);
  char *str_res = calloc(len + 1, sizeof(char));
  if (str_res == NULL) {
    log_error(
        "Allocazione oggetto 'str_res' in funzione 'to_string_date' fallita.");
    return NULL;
  }
  if (snprintf(str_res, len + 1, FORMAT_DATE, date->day, get_month_name(date),
               date->year, date->hour, date->minutes) < 0) {

    log_error("Creazione 'stringa date' in funzione 'to_string_date' fallita.");
    log_error(str_res);
    free(str_res);
    return NULL;
  }
  return str_res;
}

Date copy_date(ConstDate date) {
  if (date == NULL) {
    return NULL;
  }
  return new_date(date->minutes, date->hour, date->day, date->month,
                  date->year);
}

static void internal_copy(Date dest, ConstDate src) {
  dest->minutes = src->minutes;
  dest->hour = src->hour;
  dest->day = src->day;
  dest->month = src->month;
  dest->year = src->year;
}

#define LEAP_CHECK(A) (((A) % 4) == 0 && ((A) % 100) != 0) || ((A) % 400) == 0
int is_leap(ConstDate date) {
  if (date == NULL) {
    log_error("L'oggetto 'date' passato come parametro alla funzione 'is_leap' "
              "non risulta alloato");
    return -1;
  }

  return LEAP_CHECK(date->year);
}

#define MINUTES_IN_HOUR 60
#define HOURS_IN_DAY 24
int is_valid_date(ConstDate date) {
  if (date->minutes >= MINUTES_IN_HOUR) {
    return 0;
  }
  if (date->hour >= HOURS_IN_DAY) {
    return 0;
  }
  if (date->day == 0 || date->month == 0) {
    return 0;
  }
  if (is_leap(date) && date->month == FEBRUARY) {
    return date->day <= (months[date->month - 1] + 1);
  }
  return date->month <= MONTHS && date->day <= months[date->month - 1];
}

int get_hour(ConstDate date) {
  if (date == NULL) {
    log_error("Passato puntatore NULL alla funzione 'get_hour'.");
    return -1;
  }
  return date->hour;
}

int get_minutes(ConstDate date) {
  if (date == NULL) {
    log_error("Passato puntatore NULL alla funzione 'get_minutes'.");
    return -1;
  }
  return date->minutes;
}

int get_day(ConstDate date) {
  if (date == NULL) {
    log_error("Passato puntatore NULL alla funzione 'get_day'.");
    return -1;
  }
  return date->day;
}

int get_month(ConstDate date) {
  if (date == NULL) {
    log_error("Passato puntatore NULL alla funzione 'get_month'.");
    return -1;
  }
  return date->month;
}

int get_year(ConstDate date) {
  if (date == NULL) {
    log_error("Passato puntatore NULL alla funzione 'get_year'.");
    return -1;
  }
  return date->year;
}

void free_date(Date date) { free(date); }
