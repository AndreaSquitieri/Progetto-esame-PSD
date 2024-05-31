#include "date.h"
#include "logging.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Constants for time
#define MINUTES_IN_HOUR 60
#define HOURS_IN_DAY 24
#define MONTHS_IN_YEAR 12

// Date print format
#define FORMAT_DATE "%d %s %d, %02d:%02d"
#define DATE_BUFFER_SIZE 32

// Number of days in each month
#define DAYS_IN_MONTHS_INITIALIZER                                             \
  { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
#define MONTH_NAMES_INITIALIZER                                                \
  {                                                                            \
    "Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno", "Luglio",    \
        "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre"               \
  }

// Array of days in each month and month names
static const unsigned char days_in_months[] = DAYS_IN_MONTHS_INITIALIZER;
static const char *const month_names[] = MONTH_NAMES_INITIALIZER;

// Enumeration of months
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

// Date structure
struct DateStruct {
  unsigned char minutes;
  unsigned char hour;
  unsigned char day;
  unsigned char month;
  unsigned short year;
};

// Function to check if a date is null
static bool is_date_null(ConstDate date) { return date == NULL_DATE; }

// Function to check if a year is a leap year
static bool is_leap_year(unsigned short year) {
  return (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
}

// Function to check if a date is valid
static bool is_valid_date(ConstDate date) {
  if (is_date_null(date)) {
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

// Function to create a new date
// Allocates memory for the date and initializes its fields
Date new_date(unsigned char minutes, unsigned char hour, unsigned char day,
              unsigned char month, unsigned short year) {

  // Memory allocation for the date
  Date date = my_alloc(1, sizeof(*date));

  // Initialization of the date fields
  date->minutes = minutes;
  date->hour = hour;
  date->day = day;
  date->month = month;
  date->year = year;

  // Check if the date is valid, otherwise log an error and return NULL
  if (!is_valid_date(date)) {
    log_error("Attempt to create an invalid date.");
    free(date);
    return NULL_DATE;
  }
  return date;
}

// Function to create a copy of the date
// Returns a new date with the same values as the input date
Date copy_date(ConstDate date) {
  if (is_date_null(date)) {
    log_error("Attempt to copy a NULL date.");
    return NULL_DATE;
  }
  return new_date(date->minutes, date->hour, date->day, date->month,
                  date->year);
}

// Function to compare date components
// Returns -1 if a < b, 0 if a == b, and 1 if a > b
static inline int cmp_date_component(unsigned int a, unsigned int b) {
  return (a > b) - (a < b);
}

// Function to compare dates
// Returns -1 if date_a < date_b, 0 if date_a == date_b, and 1 if date_a >
// date_b
int cmp_date(ConstDate date_a, ConstDate date_b) {
  if (is_date_null(date_a) && is_date_null(date_b)) {
    return 0;
  }
  if (is_date_null(date_a)) {
    return -1;
  }
  if (is_date_null(date_b)) {
    return 1;
  }

  // Comparison of date components in order
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

// Function to get the month name
static const char *get_month_name(ConstDate date) {
  return month_names[date->month - 1];
}

// Function to print the date to stdout
void print_date(ConstDate date) {
  if (is_date_null(date)) {
    log_error("Attempt to print a NULL date.");
    return;
  }
  printf(FORMAT_DATE, date->day, get_month_name(date), date->year, date->hour,
         date->minutes);
}

// Function to read a date from stdin
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
  // Parsing the string to obtain the date components
  if (sscanf(temp, "%d/%d/%d %d:%d", &day, &month, &year, &hour, &minutes) !=
      5) {
    return NULL_DATE;
  }
  // Check that the passed values are not negative
  if (day < 0 || month < 0 || year < 0 || hour < 0 || minutes < 0) {
    return NULL_DATE;
  }
  // Create the date
  Date date = new_date(minutes, hour, day, month, year);
  return date;
}

// Function to save the date to a file
void save_date_to_file(ConstDate date, FILE *file) {
  if (is_date_null(date)) {
    log_error("Attempt to save NULL date to file");
    return;
  }
  if (file == NULL) {
    log_error("Attempt to write date to NULL file");
    return;
  }

  // Write the date components to the file
  if (fprintf(file, "%d %d %d %d %d\n", date->minutes, date->hour, date->day,
              date->month, date->year) < 0) {
    log_error("Failed to write date components to file.");
  }
}

// Function to read a date from a file
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

  // Read the date components from the file
  if (fscanf(file, "%d %d %d %d %d", &minutes, &hour, &day, &month, &year) !=
      5) {
    log_error("Failed to read date components from file.");
    return NULL_DATE;
  }

  // Create the date
  Date date = new_date(minutes, hour, day, month, year);

  return date;
}

// Function to free the memory allocated for the date
void free_date(Date date) {
  if (is_date_null(date)) {
    log_error("Attempt to free a NULL date.");
    return;
  }
  free(date);
}
