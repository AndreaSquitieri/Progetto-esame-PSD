#include "duration.h"
#include "logging.h"
#include "utils.h"
#include <stdlib.h>

#define MINUTES_PER_HOUR 60

struct DurationStruct {
  unsigned int hours;
  unsigned int minutes;
};

Duration new_duration(unsigned int hours, unsigned int minutes) {
  if (minutes >= MINUTES_PER_HOUR) {
    log_error("Numero minuti in duration non valido");
    return NULL_DURATION;
  }
  Duration duration = malloc(sizeof(*duration));
  if (duration == NULL) {
    log_error("Allocazione duration fallita");
    return NULL_DURATION;
  }
  duration->hours = hours;
  duration->minutes = minutes;
  return duration;
}

Duration copy_duration(Duration duration) {
  return new_duration(duration->hours, duration->minutes);
}

unsigned int get_duration_hours(Duration duration) { return duration->hours; }
unsigned int get_duration_minutes(Duration duration) {
  return duration->minutes;
}

#define FORMAT_DURATION "%02u:%02u"
void print_duration(Duration duration) {
  printf(FORMAT_DURATION, duration->hours, duration->minutes);
}

#define MAXSIZE 102
Duration read_duration(void) {
  char temp[MAXSIZE] = {0};
  if (read_line(temp, MAXSIZE)) {
    return NULL_DURATION;
  }
  unsigned int hours = 0;
  unsigned int minutes = 0;
  if (sscanf(temp, "%u:%u", &hours, &minutes) != 2) {
    return NULL_DURATION;
  }
  return new_duration(hours, minutes);
}
void free_duration(Duration duration) { free(duration); }
