CC     = gcc
CFLAGS = -g -Wall -Wextra -Iinclude
TARGET = minidbg
SRCS   = $(wildcard src/*.c)
OBJS   = $(SRCS:src/%.c=build/%.o)

all: build $(TARGET)

build:
	mkdir -p build

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf build $(TARGET)

.PHONY: all clean
