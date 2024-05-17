#include "date.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enum for test types
typedef enum {
  TEST_NEW_DATE = 1,
  TEST_CMP_DATE = 2,
  TEST_COPY_DATE = 3
  // Add more test types here if needed
} TestType;

// Function prototypes
int test_new_date(FILE *input, FILE *oracle, FILE *output);
int test_cmp_date(FILE *input, FILE *oracle, FILE *output);
int test_copy_date(FILE *input, FILE *oracle, FILE *output);
// Add more test functions for other functions in the Date module if needed

int main() {
  FILE *test_suite = fopen("test_suite.txt", "r");
  if (test_suite == NULL) {
    perror("Error opening test_suite.txt");
    return EXIT_FAILURE;
  }

  FILE *results_file = fopen("results.txt", "w");
  if (results_file == NULL) {
    perror("Error creating results.txt");
    fclose(test_suite);
    return EXIT_FAILURE;
  }

  TestType test_type;
  char test_id[50];
  char temp[100];

  char param[100];
  while (fscanf(test_suite, "%d %s %s", (int *)&test_type, test_id, param) ==
         3) {
    printf("%d %s %s\n", test_type, test_id, param);
    sprintf(temp, "%s_input.txt", test_id);
    FILE *input = fopen(temp, "r");
    sprintf(temp, "%s_oracle.txt", test_id);
    FILE *oracle = fopen(temp, "r");
    sprintf(temp, "%s_output.txt", test_id);
    FILE *output = fopen(temp, "w");

    int test_result = 0; // Flag to track if all tests for this case passed
    switch (test_type) {
    case TEST_NEW_DATE:
      test_result = test_new_date(input, oracle, output);
      break;
    case TEST_CMP_DATE:
      test_result = test_cmp_date(input, oracle, output);
      break;
    case TEST_COPY_DATE:
      test_result = test_copy_date(input, oracle, output);
      break;
    // Add more cases for other test types if needed
    default:
      printf("Unknown test type: %d\n", test_type);
      break;
    }

    fclose(input);
    fclose(oracle);
    fclose(output);

    if (test_result) {
      fprintf(results_file, "Tests passed!\n");
    } else {
      fprintf(results_file, "Tests failed!\n");
    }
  }

  fclose(test_suite);
  fclose(results_file);
  return EXIT_SUCCESS;
}

int test_new_date(FILE *input, FILE *oracle, FILE *output) {
  unsigned char minutes = 0;
  unsigned char hour = 0;
  unsigned char day = 0;
  unsigned char month = 0;
  unsigned short year = 0;
  int all_tests_passed = 1; // Flag to track if all tests passed
  while (fscanf(input, "%hhu %hhu %hhu %hhu %hu", &minutes, &hour, &day, &month,
                &year) == 5) {
    Date date = new_date(minutes, hour, day, month, year);
    save_date_to_file(date, output);

    Date expected_date = read_date_from_file(oracle);

    if (cmp_date(date, expected_date) != 0) {
      all_tests_passed = 0;
    }

    free_date(date);
    free_date(expected_date);
  }
  return all_tests_passed;
}

int test_cmp_date(FILE *input, FILE *oracle, FILE *output) {
  int all_tests_passed = 1; // Flag to track if all tests passed

  unsigned char minutes1 = 0;
  unsigned char hour1 = 0;
  unsigned char day1 = 0;
  unsigned char month1 = 0;
  unsigned short year1 = 0;

  unsigned char minutes2 = 0;
  unsigned char hour2 = 0;
  unsigned char day2 = 0;
  unsigned char month2 = 0;
  unsigned short year2 = 0;

  while (fscanf(input, "%hhu %hhu %hhu %hhu %hu %hhu %hhu %hhu %hu", &minutes1,
                &hour1, &day1, &month1, &year1, &minutes2, &hour2, &day2,
                &month2, &year2) == 10) {
    Date date1 = new_date(minutes1, hour1, day1, month1, year1);
    Date date2 = new_date(minutes2, hour2, day2, month2, year2);

    int result = cmp_date(date1, date2);
    fprintf(output, "Comparison result: %d\n", result);

    int expected_result;
    fscanf(oracle, "%d", &expected_result);
    if (result != expected_result) {
      all_tests_passed = 0;
    }

    free_date(date1);
    free_date(date2);
  }
  return all_tests_passed;
}

int test_copy_date(FILE *input, FILE *oracle, FILE *output) {
  int all_tests_passed = 1; // Flag to track if all tests passed

  unsigned char minutes, hour, day, month;
  unsigned short year;
  while (fscanf(input, "%hhu %hhu %hhu %hhu %hu", &minutes, &hour, &day, &month,
                &year) == 5) {
    Date date = new_date(minutes, hour, day, month, year);

    Date copied_date = copy_date(date);
    save_date_to_file(copied_date, output);

    Date expected_date = read_date_from_file(oracle);
    if (cmp_date(copied_date, expected_date) != 0) {
      all_tests_passed = 0;
    }

    free_date(date);
    free_date(copied_date);
    free_date(expected_date);
  }
  return all_tests_passed;
}
