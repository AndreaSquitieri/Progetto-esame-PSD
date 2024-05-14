#include "room.h"
#include <stdio.h>
#include <string.h>

typedef enum {
  TEST_NEW_ROOM = 1,
  TEST_COPY_ROOM = 2,
  TEST_IS_ROOM_EQUAL = 3,
  TEST_GET_ROOM_NAME = 4,
  TEST_GET_ROOM_ID = 5
  // Add more test types here if needed
} TestType;

int test_new_room(FILE *input, FILE *oracle, FILE *output);
int test_copy_room(FILE *input, FILE *oracle, FILE *output);
int test_is_room_equal(FILE *input, FILE *oracle, FILE *output);
int test_get_room_name(FILE *input, FILE *oracle, FILE *output);
int test_get_room_id(FILE *input, FILE *oracle, FILE *output);

int main() {
  FILE *test_suite = fopen("test_suite.txt", "r");
  if (test_suite == NULL) {
    perror("Error opening test_suite.txt");
    return 1;
  }

  FILE *results_file = fopen("results.txt", "w");
  if (results_file == NULL) {
    perror("Error creating results.txt");
    fclose(test_suite);
    return 1;
  }

  int all_tests_passed = 1; // Flag to track if all tests passed

  TestType test_type;
  char test_id[50];
  while (fscanf(test_suite, "%d %s", (int *)&test_type, test_id) == 2) {
    FILE *input = fopen(strcat(test_id, "_input.txt"), "r");
    FILE *oracle = fopen(strcat(test_id, "_oracle.txt"), "r");
    FILE *output = fopen(strcat(test_id, "_output.txt"), "w");

    int test_result = 0; // Flag to track if all tests for this case passed
    switch (test_type) {
    case TEST_NEW_ROOM:
      test_result = test_new_room(input, oracle, output);
      break;
    case TEST_COPY_ROOM:
      test_result = test_copy_room(input, oracle, output);
      break;
    case TEST_IS_ROOM_EQUAL:
      test_result = test_is_room_equal(input, oracle, output);
      break;
    case TEST_GET_ROOM_NAME:
      test_result = test_get_room_name(input, oracle, output);
      break;
    case TEST_GET_ROOM_ID:
      test_result = test_get_room_id(input, oracle, output);
      break;
    // Add more cases for other test types if needed
    default:
      printf("Unknown test type: %d\n", test_type);
      break;
    }

    fclose(input);
    fclose(oracle);
    fclose(output);

    if (!test_result) {
      all_tests_passed = 0;
    }
  }

  // Write the overall result to results.txt
  if (all_tests_passed) {
    fprintf(results_file, "Tests passed!\n");
  } else {
    fprintf(results_file, "Tests failed!\n");
  }

  fclose(test_suite);
  fclose(results_file);
  return 0;
}

int test_new_room(FILE *input, FILE *oracle, FILE *output) {
  char name[100];
  unsigned int id;
  int all_tests_passed = 1; // Flag to track if all tests passed

  while (fscanf(input, "%s %u", name, &id) == 2) {
    Room room = new_room(name, id);
    int result = (room != NULL_ROOM); // Result of the new_room function
    fprintf(output, "%d\n", result);  // Output the result to the output file

    int expected_result = 0;
    if (fscanf(oracle, "%d", &expected_result) != 1) {
      fprintf(stderr, "Error reading from oracle file\n");
      all_tests_passed = 0;
      break; // Stop testing if an error occurs
    }

    // Compare the result with the expected result from the oracle
    if (result != expected_result) {
      all_tests_passed = 0;
    }

    if (room != NULL_ROOM) {
      free_room(room);
    }
  }

  return all_tests_passed;
}

int test_copy_room(FILE *input, FILE *oracle, FILE *output) {
  char name[100];
  unsigned int id;
  int all_tests_passed = 1; // Flag to track if all tests passed

  while (fscanf(input, "%s %u", name, &id) == 2) {
    Room room = new_room(name, id);
    Room room_oracle = read_room_from_file(oracle);
    Room copy = copy_room(room); // Create a copy of the room
    save_room_to_file(copy, output);

    // Check if the copy is equal to the original room
    bool result = is_room_equal(copy, room_oracle);

    // Read expected result from the oracle file

    // Compare the result with the expected result from the oracle
    if (!result) {
      all_tests_passed = 0;
    }

    free_room(room);
    free_room(room_oracle);
    free_room(copy);
  }

  return all_tests_passed;
}

int test_is_room_equal(FILE *input, FILE *oracle, FILE *output) {
  char name1[100];
  unsigned int id1 = 0;
  char name2[100];
  unsigned int id2 = 0;
  int all_tests_passed = 1; // Flag to track if all tests passed

  while (fscanf(input, "%u %s %u %s", &id1, name1, &id2, name2) == 4) {
    Room room1 = new_room(name1, id1);
    Room room2 = new_room(name2, id2);
    int result = is_room_equal(room1, room2);
    if (result) {
      fprintf(output, "1\n");
    } else {
      fprintf(output, "0\n");
      all_tests_passed = 0;
    }

    int expected_result = 0;
    if (fscanf(oracle, "%d", &expected_result) != 1) {
      fprintf(stderr, "Error reading from oracle file\n");
      all_tests_passed = 0;
      break; // Stop testing if an error occurs
    }

    // Compare the result with the expected result from the oracle
    if (result != expected_result) {
      all_tests_passed = 0;
    }
    free_room(room1);
    free_room(room2);
  }
  return all_tests_passed;
}
int test_get_room_name(FILE *input, FILE *oracle, FILE *output) {
  char name[100];
  unsigned int id;
  int all_tests_passed = 1; // Flag to track if all tests passed

  while (fscanf(input, "%s %u", name, &id) == 1) {
    Room room = new_room(name, id); // Read room data from input file

    // Get the name of the room
    const char *name = get_room_name(room);
    fprintf(output, "%s\n", name);

    // Read expected name from the oracle file
    char expected_name[100];
    if (fscanf(oracle, "%s", expected_name) != 1) {
      fprintf(stderr, "Error reading from oracle file\n");
      all_tests_passed = 0;
      break; // Stop testing if an error occurs
    }

    // Compare the obtained name with the expected name from the oracle
    if (strcmp(name, expected_name) != 0) {
      all_tests_passed = 0;
    }

    free_room(room);
  }

  return all_tests_passed;
}

int test_get_room_id(FILE *input, FILE *oracle, FILE *output) {
  char name[100];
  unsigned int id;
  int all_tests_passed = 1; // Flag to track if all tests passed

  while (fscanf(input, "%s %u", name, &id) == 1) {
    Room room = new_room(name, id); // Read room data from input file

    // Get the id of the room
    unsigned int id = get_room_id(room);
    fprintf(output, "%d\n", id);

    unsigned int expected_id = 0;
    if (fscanf(oracle, "%d", expected_id) != 1) {
      fprintf(stderr, "Error reading from oracle file\n");
      all_tests_passed = 0;
      break; // Stop testing if an error occurs
    }

    // Compare the obtained name with the expected name from the oracle
    if (id != expected_id) {
      all_tests_passed = 0;
    }

    free_room(room);
  }

  return all_tests_passed;
}
