#include "date.h"
#include "logging.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MINUTES_IN_HOUR 60
#define HOURS_IN_DAY 24
#define MONTHS_IN_YEAR 12
#define DAYS_IN_MONTHS_INITIALIZER                                             \
  { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
#define MONTH_NAMES_INITIALIZER                                                \
  {                                                                            \
    "Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno", "Luglio",    \
        "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre"               \
  }
#define FORMAT_DATE "%d %s %d, %02d:%02d"
#define DATE_BUFFER_SIZE 32

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

struct DateStruct {
  unsigned char minutes;
  unsigned char hour;
  unsigned char day;
  unsigned char month;
  unsigned short year;
};

static const unsigned char days_in_months[] = DAYS_IN_MONTHS_INITIALIZER;
static const char *const month_names[] = MONTH_NAMES_INITIALIZER;

static const char *get_month_name(ConstDate date) {
  return month_names[date->month - 1];
}

static bool is_leap_year(unsigned short year) {
  return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}

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

Date new_date(unsigned char minutes, unsigned char hour, unsigned char day,
              unsigned char month, unsigned short year) {

  Date date = my_alloc(1, sizeof(*date));

  date->minutes = minutes;
  date->hour = hour;
  date->day = day;
  date->month = month;
  date->year = year;

  if (!is_valid_date(date)) {
    log_error("Attempt to create an invalid date.");
    free(date);
    return NULL_DATE;
  }
  return date;
}

static inline int cmp_date_component(unsigned int a, unsigned int b) {
  return (a > b) - (a < b);
}

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

void print_date(ConstDate date) {
  printf(FORMAT_DATE, date->day, get_month_name(date), date->year, date->hour,
         date->minutes);
}

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
  if (sscanf(temp, "%d/%d/%d %d:%d", &day, &month, &year, &hour, &minutes) !=
      5) {
    return NULL_DATE;
  }
  if (day < 0 || month < 0 || year < 0 || hour < 0 || minutes < 0) {
    return NULL_DATE;
  }
  Date date = new_date(minutes, hour, day, month, year);
  return date;
}

Date copy_date(ConstDate date) {
  if (date == NULL_DATE) {
    return NULL_DATE;
  }
  return new_date(date->minutes, date->hour, date->day, date->month,
                  date->year);
}

void free_date(Date date) { free(date); }

// Function to save a date to a file
void save_date_to_file(ConstDate date, FILE *file) {
  if (date == NULL_DATE) {
    log_error("Date is NULL");
    return;
  }
  if (file == NULL) {
    log_error("File pointer is NULL");
    return;
  }

  // Write date components to the file
  if (fprintf(file, "%d %d %d %d %d\n", date->minutes, date->hour, date->day,
              date->month, date->year) < 0) {
    log_error("Failed to write date components to file.");
  }
}

// Function to read a date from a file
Date read_date_from_file(FILE *file) {
  if (file == NULL) {
    log_error("File pointer is NULL");
    return NULL_DATE;
  }

  int day = 0;
  int month = 0;
  int year = 0;
  int hour = 0;
  int minutes = 0;

  // Read date components from the file
  if (fscanf(file, "%d %d %d %d %d", &minutes, &hour, &day, &month, &year) !=
      5) {
    return NULL_DATE;
  }

  // Create a new date object with the read components
  Date date = new_date(minutes, hour, day, month, year);

  return date;
}
