#ifndef DATE_H_
#define DATE_H_

#include <stdio.h>

#define NULL_DATE NULL

typedef struct DateStruct *Date;
typedef const struct DateStruct *ConstDate;

Date new_date(unsigned char minutes, unsigned char hour, unsigned char day,
              unsigned char month, unsigned short year);
Date copy_date(ConstDate date);

int cmp_date(ConstDate date_a, ConstDate date_b);

// IO functions
void save_date_to_file(ConstDate date, FILE *file);
Date read_date_from_file(FILE *file);
void print_date(ConstDate date);
Date read_date(void);

void free_date(Date date);

#endif // DATE_H_
