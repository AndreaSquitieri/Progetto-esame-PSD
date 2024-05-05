#ifndef DURATION_H_
#define DURATION_H_

#define NULL_DURATION NULL

typedef struct DurationStruct *Duration;

Duration new_duration(unsigned int hours, unsigned int minutes);
Duration copy_duration(Duration duration);
unsigned int get_duration_hours(Duration duration);
unsigned int get_duration_minutes(Duration duration);
void print_duration(Duration duration);
Duration read_duration(void);
void free_duration(Duration duration);

#endif // DURATION_H_
