#include "conference.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _WIN32
#define NULL_DEVICE "NUL:"
#define TTY_DEVICE "COM1:"
#else
#define NULL_DEVICE "/dev/null"
#define TTY_DEVICE "/dev/tty"
#endif

typedef enum {
  TEST_ADD_EVENT = 1,
  TEST_REMOVE_EVENT = 2,
  TEST_EDIT_EVENT = 3,
  TEST_DISPLAY_EVENTS = 4,
  // Add more test types here if needed
} TestType;

int cmp_file(FILE *oracle, FILE *output) {
  int temp1 = 0, temp2 = 0;
  while ((temp1 = fgetc(oracle)) != EOF && (temp2 = fgetc(output)) != EOF) {
    if (temp1 != temp2) {
      return 0;
    }
  }
  if (temp1 == EOF && fgetc(output) != EOF) {
    return 0;
  } else if (temp1 != EOF) {
    return 0;
  }
  return 1;
}

int run_test_case(TestType test_type, FILE *oracle, FILE *output,
                  FILE *conference) {
  int test_result = 1; // Flag to track if all tests for this case passed
  switch (test_type) {
  case TEST_ADD_EVENT: {
    Conference conf = read_conference_from_file(conference);
    if (conf == NULL_CONFERENCE) {
      conf = new_conference();
    }
    if (conf == NULL_CONFERENCE) {
      return 0;
    }

    freopen(NULL_DEVICE, "w", stdout);
    freopen(NULL_DEVICE, "w", stderr);

    add_conference_event(conf);
    save_conference_to_file(conf, output);

    freopen(TTY_DEVICE, "w", stdout);
    freopen(TTY_DEVICE, "w", stderr);

    fflush(output);
    rewind(output);

    test_result = cmp_file(oracle, output);
    break;
  }
  case TEST_EDIT_EVENT: {
    Conference conf = read_conference_from_file(conference);
    if (conf == NULL_CONFERENCE) {
      conf = new_conference();
    }
    if (conf == NULL_CONFERENCE) {
      return 0;
    }
    freopen(NULL_DEVICE, "w", stdout);
    freopen(NULL_DEVICE, "w", stderr);

    edit_conference_event(conf);
    save_conference_to_file(conf, output);

    freopen(TTY_DEVICE, "w", stdout);
    freopen(TTY_DEVICE, "w", stderr);

    test_result = cmp_file(oracle, output);
    break;
  }
  case TEST_REMOVE_EVENT: {
    Conference conf = read_conference_from_file(conference);
    if (conf == NULL_CONFERENCE) {
      conf = new_conference();
    }
    if (conf == NULL_CONFERENCE) {
      return 0;
    }
    freopen(NULL_DEVICE, "w", stdout);
    freopen(NULL_DEVICE, "w", stderr);

    remove_conference_event(conf);
    save_conference_to_file(conf, output);

    freopen(TTY_DEVICE, "w", stdout);
    freopen(TTY_DEVICE, "w", stderr);

    test_result = cmp_file(oracle, output);
    break;
  }
  case TEST_DISPLAY_EVENTS: {
    Conference conf = read_conference_from_file(conference);
    if (conf == NULL_CONFERENCE) {
      return 0;
    }
    int fd_output = fileno(output);
    dup2(fd_output, STDOUT_FILENO);

    display_conference_schedule(conf);

    dup2(STDOUT_FILENO, fd_output);

    test_result = cmp_file(oracle, output);

    break;
  }
  }
  return test_result;
}

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

    (void)sprintf(temp, "%s/conference.txt", test_id);
    FILE *conference_file = fopen(temp, "r");
    (void)sprintf(temp, "%s/oracle.txt", test_id);
    FILE *oracle = fopen(temp, "r");
    (void)sprintf(temp, "%s/output.txt", test_id);
    FILE *output = fopen(temp, "w+");

    (void)sprintf(temp, "%s/input.txt", test_id);

    // TODO
    // Smettere di imbrogliare
    if (freopen(temp, "r", stdin) == NULL || output == NULL) {
      fprintf(results_file, "%s skip\n", test_id);
      continue;
    }

    int test_result = run_test_case(test_type, oracle, output, conference_file);

    if (conference_file != NULL) {
      fclose(conference_file);
    }
    if (oracle != NULL) {

      fclose(oracle);
    }
    fclose(output);

    if (test_result) {
      fprintf(results_file, "%s pass\n", test_id);
    } else {
      fprintf(results_file, "%s fail\n", test_id);
    }
    fflush(results_file);
  }

  fclose(test_suite);
  fclose(results_file);
  return EXIT_SUCCESS;
}
