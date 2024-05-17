CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS =
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

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

date_test:	$(OBJS)
	$(CC) $(CFLAGS) $(BUILD_DIR)/utils.o $(BUILD_DIR)/logging.o $(BUILD_DIR)/date.o tests/date_test/main.c -o tests/date_test/date_test

clean:
	rm -rf $(BUILD_DIR)/*.o $(MAIN_EXEC)
