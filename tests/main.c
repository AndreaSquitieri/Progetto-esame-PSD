#include "conference.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  TEST_ADD_EVENT = 1,
  TEST_REMOVE_EVENT = 2,
  TEST_EDIT_EVENT = 3
  // Add more test types here if needed
} TestType;

int main(int argc, char **argv) {
  if (argc < 3) {
    return EXIT_FAILURE;
  }
  FILE *test_suite = fopen(argv[1], "r");
  if (test_suite == NULL) {
    perror("Error opening test_suite.txt");
    return EXIT_FAILURE;
  }

  FILE *results_file = fopen(argv[2], "w");
  if (results_file == NULL) {
    perror("Error creating results.txt");
    fclose(test_suite);
    return EXIT_FAILURE;
  }

  TestType test_type = 0;
  char test_id[50];
  char temp[100];

  char param[100];
  while (fscanf(test_suite, "%d %s %s", (int *)&test_type, test_id, param) ==
         3) {
    printf("%d %s %s\n", test_type, test_id, param);

    (void)sprintf(temp, "%s/conference.txt", test_id);
    FILE *conference_file = fopen(temp, "r");
    (void)sprintf(temp, "%s/oracle.txt", test_id);
    FILE *oracle = fopen(temp, "r");
    (void)sprintf(temp, "%s/output.txt", test_id);
    FILE *output = fopen(temp, "w+");

    (void)sprintf(temp, "%s/input.txt", test_id);
		if (freopen(temp, "r", stdin) == NULL || oracle == NULL || output == NULL) {
      fprintf(results_file, "Tests skipped!\n");
			continue;
		}

    int test_result = 1; // Flag to track if all tests for this case passed
    switch (test_type) {
    case TEST_ADD_EVENT: {
      Conference conf = read_conference_from_file(conference_file);
      if (conf == NULL_CONFERENCE) {
        conf = new_conference();
      }
      if (conf == NULL_CONFERENCE) {
        return EXIT_FAILURE;
      }
      add_conference_event(conf);
      save_conference_to_file(conf, output);
      fflush(output);
      rewind(output);
      int temp1 = 0, temp2 = 0;
      while ((temp1 = fgetc(oracle)) != EOF && (temp2 = fgetc(output)) != EOF) {
        if (temp1 != temp2) {
          test_result = 0;
        }
      }
      if (temp1 == EOF && fgetc(output) != EOF) {
        test_result = 0;
      } else if (temp1 != EOF) {
        test_result = 0;
      }
      break;
    }
    case TEST_EDIT_EVENT: {
      Conference conf = read_conference_from_file(conference_file);
      if (conf == NULL_CONFERENCE) {
        conf = new_conference();
      }
      if (conf == NULL_CONFERENCE) {
        return EXIT_FAILURE;
      }
      edit_conference_event(conf);
      save_conference_to_file(conf, output);
      break;
    }
    case TEST_REMOVE_EVENT: {
      Conference conf = read_conference_from_file(conference_file);
      if (conf == NULL_CONFERENCE) {
        conf = new_conference();
      }
      if (conf == NULL_CONFERENCE) {
        return EXIT_FAILURE;
      }
      remove_conference_event(conf);
      save_conference_to_file(conf, output);
      break;
    }
    // Add more cases for other test types if needed
    default:
      printf("Unknown test type: %d\n", test_type);
      break;
    }

    if (conference_file != NULL) {
      fclose(conference_file);
    }
    fclose(oracle);
    fclose(output);

    if (test_result) {
      fprintf(results_file, "Tests passed!\n");
    } else {
      fprintf(results_file, "Tests failed!\n");
    }
    fflush(results_file);
  }

  fclose(test_suite);
  fclose(results_file);
  return EXIT_SUCCESS;
}
