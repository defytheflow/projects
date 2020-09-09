TARGET = snake
SRC_DIR = src

CC = gcc
CFLAGS = -W -Wall -Wextra -Wpedantic
LDLIBS = -lncurses

SRCS = $(shell find $(SRC_DIR) -name *.c)
OBJS = $(addsuffix .o, $(basename $(SRCS)))

default: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) -o $@

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS)
