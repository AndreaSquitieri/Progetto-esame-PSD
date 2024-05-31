SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
BIN_DIR = bin
TEST_DIR = tests
CC = gcc
CFLAGS = -Wall -Wextra -I$(INCLUDE_DIR) -g
LDFLAGS =


# Name of the main executable
MAIN_EXEC = $(BIN_DIR)/progetto

.PHONY: all clean

all: $(BIN_DIR) $(MAIN_EXEC) $(TEST_DIR)/test

$(MAIN_EXEC): $(BUILD_DIR)/logging.o $(BUILD_DIR)/utils.o $(BUILD_DIR)/date.o $(BUILD_DIR)/room.o $(BUILD_DIR)/mevent.o $(BUILD_DIR)/room_list.o $(BUILD_DIR)/event_bst.o $(BUILD_DIR)/conference.o $(BUILD_DIR)/main.o
	$(CC) $(LDFLAGS) $^ -o $@

$(TEST_DIR)/test: $(BUILD_DIR)/logging.o $(BUILD_DIR)/utils.o $(BUILD_DIR)/date.o $(BUILD_DIR)/room.o $(BUILD_DIR)/mevent.o $(BUILD_DIR)/room_list.o $(BUILD_DIR)/event_bst.o $(BUILD_DIR)/conference.o $(TEST_DIR)/test.o
	$(CC) $(LDFLAGS) $^ -o $(TEST_DIR)/test

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR)/logging.o: $(SRC_DIR)/logging.c $(INCLUDE_DIR)/logging.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/logging.c -o $@

$(BUILD_DIR)/utils.o: $(SRC_DIR)/utils.c $(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/logging.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/utils.c -o $@

$(BUILD_DIR)/date.o: $(SRC_DIR)/date.c $(INCLUDE_DIR)/date.h $(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/logging.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/date.c -o $@

$(BUILD_DIR)/room.o: $(SRC_DIR)/room.c $(INCLUDE_DIR)/room.h $(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/logging.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/room.c -o $@

$(BUILD_DIR)/mevent.o: $(SRC_DIR)/mevent.c $(INCLUDE_DIR)/mevent.h $(INCLUDE_DIR)/date.h $(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/logging.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/mevent.c -o $@

$(BUILD_DIR)/room_list.o: $(SRC_DIR)/room_list.c $(INCLUDE_DIR)/room_list.h $(INCLUDE_DIR)/room.h $(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/logging.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/room_list.c -o $@

$(BUILD_DIR)/event_bst.o: $(SRC_DIR)/event_bst.c $(INCLUDE_DIR)/event_bst.h $(INCLUDE_DIR)/room_list.h $(INCLUDE_DIR)/mevent.h $(INCLUDE_DIR)/date.h $(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/logging.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/event_bst.c -o $@

$(BUILD_DIR)/conference.o: $(SRC_DIR)/conference.c $(INCLUDE_DIR)/conference.h $(INCLUDE_DIR)/event_bst.h $(INCLUDE_DIR)/room_list.h $(INCLUDE_DIR)/room.h $(INCLUDE_DIR)/mevent.h $(INCLUDE_DIR)/date.h $(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/logging.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/conference.c -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c $(INCLUDE_DIR)/conference.h  $(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/logging.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $@

$(TEST_DIR)/test.o: $(TEST_DIR)/test.c $(INCLUDE_DIR)/conference.h
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test.c -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(MAIN_EXEC) $(TEST_DIR)/test.o $(TEST_DIR)/test
