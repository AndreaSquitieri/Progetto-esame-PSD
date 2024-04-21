##
# Progetto esame PSD, Prima traccia
#
# @file
# @version 0.1

CC = gcc
CFLAGS = -Wall -Wextra -I./include
LDFLAGS = -L./lib

SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/progetto-psd

all:	$(TARGET)

$(TARGET):	$(OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

.PHONY:	all clean

# end
