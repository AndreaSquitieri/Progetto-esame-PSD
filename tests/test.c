#include "conference.h"
#include <fcntl.h>
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
  int temp1 = 0;
  int temp2 = 0;
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

int run_test_case(TestType test_type, const char *oracle_fname,
                  const char *output_fname, const char *input_fname,
                  const char *conference_fname) {

  FILE *conference = fopen(conference_fname, "r");
  FILE *oracle = fopen(oracle_fname, "r");
  FILE *output = fopen(output_fname, "w+");

  // TODO
  // Smettere di imbrogliare
  if (freopen(input_fname, "r", stdin) == NULL || output == NULL) {
    return 0;
  }

  int test_result = 1; // Flag to track if all tests for this case passed
  switch (test_type) {
  case TEST_ADD_EVENT: {
    Conference conf = read_conference_from_file(conference);
    if (conf == NULL_CONFERENCE) {
      conf = new_conference();
    }
    if (conf == NULL_CONFERENCE) {
      test_result = 0;
      break;
    }

    add_conference_event(conf);
    save_conference_to_file(conf, output);

    fflush(output);
    rewind(output);

    test_result = cmp_file(oracle, output);
    break;
  }
  case TEST_REMOVE_EVENT: {
    Conference conf = read_conference_from_file(conference);
    if (conf == NULL_CONFERENCE) {
      conf = new_conference();
    }
    if (conf == NULL_CONFERENCE) {
      test_result = 0;
      break;
    }

    remove_conference_event(conf);
    save_conference_to_file(conf, output);

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
      test_result = 0;
      break;
    }

    edit_conference_event(conf);
    save_conference_to_file(conf, output);

    test_result = cmp_file(oracle, output);
    break;
  }
  case TEST_DISPLAY_EVENTS: {
    Conference conf = read_conference_from_file(conference);
    if (conf == NULL_CONFERENCE) {
      test_result = 0;
      break;
    }

    int fd_output = fileno(output);
    int stdout_fd = dup(STDOUT_FILENO);

    dup2(fd_output, STDOUT_FILENO);
    display_conference_schedule(conf);
    dup2(stdout_fd, STDOUT_FILENO);
    close(stdout_fd);

    fflush(output);
    rewind(output);

    test_result = cmp_file(oracle, output);

    break;
  }
  }
  if (conference != NULL) {
    fclose(conference);
  }
  if (oracle != NULL) {

    fclose(oracle);
  }
  fclose(output);
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
  char conference_fname[100];
  char oracle_fname[100];
  char output_fname[100];
  char input_fname[100];

  char param[100];
  while (fscanf(test_suite, "%d %s %[^\n]", (int *)&test_type, test_id,
                param) == 3) {
    (void)sprintf(conference_fname, "%s/conference.txt", test_id);
    (void)sprintf(oracle_fname, "%s/oracle.txt", test_id);
    (void)sprintf(output_fname, "%s/output.txt", test_id);
    (void)sprintf(input_fname, "%s/input.txt", test_id);
    int test_result = run_test_case(test_type, oracle_fname, output_fname,
                                    input_fname, conference_fname);
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
