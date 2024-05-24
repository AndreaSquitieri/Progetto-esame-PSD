#ifndef DATE_H_
#define DATE_H_

#include <stdio.h>

#define NULL_DATE NULL

/*
  Structure representing a date .
*/
typedef struct DateStruct *Date;
typedef const struct DateStruct *ConstDate;

/*
  Syntax Specification:
  - new_date(unsigned char, unsigned char, unsigned char, unsigned char,
             unsigned short) -> Date
  - types: unsigned char, unsigned short
  - internal types: Date

  Semantic Specification:
  - Function: new_date(minutes, hour, day, month, year) -> return_date
  - Description: Creates a new Date object with the specified components.
  - Preconditions: None.
  - Postconditions: Returns a pointer to the newly created Date object, or NULL
                    if the date is invalid. The caller is responsible for
  freeing the allocated memory using free_date().
*/
Date new_date(unsigned char minutes, unsigned char hour, unsigned char day,
              unsigned char month, unsigned short year);

/*
  Syntax Specification:
  - copy_date(ConstDate) -> Date
  - types: ConstDate
  - internal types: Date

  Semantic Specification:
  - Function: copy_date(date) -> return_date
  - Description: Creates a copy of the given Date object.
  - Preconditions: 'date' is a valid Date object.
  - Postconditions: Returns a pointer to the newly created Date object, which
                    is a copy of 'date'. The caller is responsible for freeing
                    the allocated memory using free_date().
*/
Date copy_date(ConstDate date);

/*
  Syntax Specification:
  - cmp_date(ConstDate, ConstDate) -> int
  - types: ConstDate
  - internal types: int

  Semantic Specification:
  - Function: cmp_date(date_a, date_b) -> res
  - Description: Compares two Date objects.
  - Preconditions: 'date_a' and 'date_b' are valid Date objects.
  - Postconditions: Returns an integer less than, equal to, or greater than zero
                    if 'date_a' is found to be less than, equal to, or greater
                    than 'date_b', respectively.
*/
int cmp_date(ConstDate date_a, ConstDate date_b);

// IO functions

/*
  Syntax Specification:
  - save_date_to_file(ConstDate, FILE*)
  - types: ConstDate, FILE*
  - internal types: none

  Semantic Specification:
  - Function: save_date_to_file(date, file)
  - Description: Saves the given Date object to a file stream.
  - Preconditions: 'date' is a valid Date object. 'file' is a valid FILE stream.
  - Postconditions: The components of 'date' are written to the file stream
  'file'.
*/
void save_date_to_file(ConstDate date, FILE *file);

/*
  Syntax Specification:
  - read_date_from_file(FILE*) -> Date
  - types: FILE*
  - internal types: Date

  Semantic Specification:
  - Function: read_date_from_file(file) -> return_date
  - Description: Reads a Date object from a file stream.
  - Preconditions: 'file' is a valid FILE stream.
  - Postconditions: Returns a pointer to the newly created Date object read
                    from the file stream 'file', or NULL if reading fails.
                    The caller is responsible for freeing the allocated memory
                    using free_date().
*/
Date read_date_from_file(FILE *file);

/*
  Syntax Specification:
  - print_date(ConstDate)
  - types: ConstDate
  - internal types: none

  Semantic Specification:
  - Function: print_date(date)
  - Description: Prints the given Date object to stdout.
  - Preconditions: 'date' is a valid Date object.
  - Postconditions: The components of 'date' are printed to stdout in a
  human-readable format.
*/
void print_date(ConstDate date);

/*
  Syntax Specification:
  - read_date(void) -> Date
  - types: none
  - internal types: Date

  Semantic Specification:
  - Function: read_date() -> return_date
  - Description: Reads a Date object from stdin.
  - Preconditions: None.
  - Postconditions: Returns a pointer to the newly created Date object read
                    from stdin, or NULL if reading fails.
                    The caller is responsible for freeing the allocated memory
                    using free_date().
*/
Date read_date(void);

/*
  Syntax Specification:
  - free_date(Date)
  - types: Date
  - internal types: none

  Semantic Specification:
  - Function: free_date(date)
  - Description: Frees the memory allocated for a Date object.
  - Preconditions: 'date' is a valid Date object.
  - Postconditions: The memory allocated for 'date' is deallocated.
*/
void free_date(Date date);

#endif // DATE_H_
