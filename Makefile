CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g
LDFLAGS =
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
TEST_DIR = tests

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
# List of object files (replace .c with .o)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Name of the main executable
MAIN_EXEC = $(BIN_DIR)/program

.PHONY: all clean

all: $(BIN_DIR) $(MAIN_EXEC)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN_EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

test: $(OBJS) $(TEST_DIR)/test.o
	$(CC) $(LDFLAGS) $(filter-out $(BUILD_DIR)/main.o, $(OBJS)) $(TEST_DIR)/test.o -o $(TEST_DIR)/test

$(TEST_DIR)/test.o:
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test.c -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(MAIN_EXEC) $(TEST_DIR)/test.o $(TEST_DIR)/test
