#ifndef DATE_H_
#define DATE_H_

typedef struct DateStruct *Date;
typedef const struct DateStruct *ConstDate;

Date new_date(unsigned char minutes, unsigned char hour, unsigned char day,
              unsigned char month, unsigned short year);
int is_valid_date(ConstDate date);
int is_leap(ConstDate date);
int cmp_date(ConstDate date_a, ConstDate date_b);
char *to_string_date(ConstDate);
Date copy_date(ConstDate);
void free_date(Date);

#endif // DATE_H_
