CC = gcc
CFLAGS = -Wall -Wextra -I./include
LDFLAGS = -Llib

SRCDIR = src
INCDIR = include
TESTDIR = tests
BINDIR = bin
LIBDIR = lib

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:.c=.o)

TEST_SRCS = $(wildcard $(TESTDIR)/date_test/*.c)
TEST_OBJS = $(TEST_SRCS:.c=.o)

.PHONY: all clean

all: $(BINDIR)/program

$(BINDIR)/program: $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LIBS) -o $@


$(BINDIR):
	mkdir -p $(BINDIR)


clean:
	rm -rf $(OBJS) $(TEST_OBJS) $(BINDIR)/program
