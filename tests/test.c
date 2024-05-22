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
  TEST_REMOVE_EVENT,
  TEST_EDIT_EVENT,
  TEST_ASSIGN_ROOM_EVENT,
  TEST_FREE_ROOM_EVENT,
  TEST_DISPLAY_EVENTS,
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
void silence_stdout(void) {
  // Flush any existing stdout output
  fflush(stdout);

  // Save the current stdout file descriptor
  int stdout_fd = dup(STDOUT_FILENO);
  if (stdout_fd == -1) {
    perror("dup");
    exit(1);
  }

  // Open /dev/null for writing
  int devnull_fd = open("/dev/null", O_WRONLY);
  if (devnull_fd == -1) {
    perror("open");
    close(stdout_fd);
    exit(1);
  }

  // Redirect stdout to /dev/null
  if (dup2(devnull_fd, STDOUT_FILENO) == -1) {
    perror("dup2");
    close(stdout_fd);
    close(devnull_fd);
    exit(1);
  }

  // Close /dev/null file descriptor as it is no longer needed
  close(devnull_fd);

  // Save the stdout file descriptor into the environment
  // This uses snprintf to convert the file descriptor to a string
  char fd_str[16];
  snprintf(fd_str, sizeof(fd_str), "%d", stdout_fd);
  setenv("SAVED_STDOUT_FD", fd_str, 1);
}

void restore_stdout() {
  // Flush any output that might be in the buffer
  fflush(stdout);

  // Get the saved stdout file descriptor from the environment
  const char *fd_str = getenv("SAVED_STDOUT_FD");
  if (!fd_str) {
    fprintf(stderr, "No saved stdout file descriptor found.\n");
    exit(1);
  }

  // Convert the string back to an integer file descriptor
  int stdout_fd = atoi(fd_str);
  if (stdout_fd == 0 && fd_str[0] != '0') {
    fprintf(stderr, "Invalid saved stdout file descriptor: %s\n", fd_str);
    exit(1);
  }

  // Restore stdout using the saved file descriptor
  if (dup2(stdout_fd, STDOUT_FILENO) == -1) {
    perror("dup2");
    close(stdout_fd);
    exit(1);
  }

  // Close the saved stdout file descriptor as it is no longer needed
  close(stdout_fd);

  // Unset the environment variable
  unsetenv("SAVED_STDOUT_FD");
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

    silence_stdout();
    add_conference_event(conf);
    save_conference_to_file_sorted(conf, output);
    restore_stdout();

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

    silence_stdout();
    remove_conference_event(conf);
    save_conference_to_file_sorted(conf, output);
    restore_stdout();

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

    silence_stdout();
    edit_conference_event(conf);
    save_conference_to_file_sorted(conf, output);
    restore_stdout();

    fflush(output);
    rewind(output);
    test_result = cmp_file(oracle, output);
    break;
  }
  case TEST_ASSIGN_ROOM_EVENT: {
    Conference conf = read_conference_from_file(conference);
    if (conf == NULL_CONFERENCE) {
      conf = new_conference();
    }
    if (conf == NULL_CONFERENCE) {
      test_result = 0;
      break;
    }

    silence_stdout();

    conference_assign_event_to_room(conf);
    save_conference_to_file_sorted(conf, output);

    restore_stdout();

    fflush(output);
    rewind(output);
    test_result = cmp_file(oracle, output);
    break;
  }
  case TEST_FREE_ROOM_EVENT: {
    Conference conf = read_conference_from_file(conference);
    if (conf == NULL_CONFERENCE) {
      conf = new_conference();
    }
    if (conf == NULL_CONFERENCE) {
      test_result = 0;
      break;
    }

    silence_stdout();

    conference_free_event_room(conf);
    save_conference_to_file_sorted(conf, output);

    restore_stdout();

    fflush(output);
    rewind(output);
    test_result = cmp_file(oracle, output);
    break;
  }
  case TEST_DISPLAY_EVENTS: {
    Conference conf = read_conference_from_file(conference);
    if (conf == NULL_CONFERENCE) {
      test_result = 0;
      break;
    }

    fflush(stdout);
    int fd_output = fileno(output);
    int stdout_fd = dup(STDOUT_FILENO);
    dup2(fd_output, STDOUT_FILENO);

    display_conference_schedule(conf);

    fflush(stdout);
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
