CFLAGS=-O0
CC=gcc

all: main
main: main.c
	$(CC) $(CFLAGS) -g -o $@ $^ -Wall -Wextra
clean:
	rm -f main
