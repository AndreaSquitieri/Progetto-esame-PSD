#ifndef DATE_H_
#define DATE_H_

#define NULL_DATE NULL

typedef struct DateStruct *Date;
typedef const struct DateStruct *ConstDate;

Date new_date(unsigned char minutes, unsigned char hour, unsigned char day,
              unsigned char month, unsigned short year);
int is_valid_date(ConstDate date);
int is_leap(ConstDate date);
int cmp_date(ConstDate date_a, ConstDate date_b);
void print_date(ConstDate date);
Date read_date(void);

Date copy_date(ConstDate date);
void free_date(Date date);

#endif // DATE_H_
