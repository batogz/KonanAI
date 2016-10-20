SHELL=/bin/bash

CC=gcc
CFLAGS=-Wall -std=c99

.PHONY: all clean

all: KonanAI

KonanAI: src/KonanAI.c board.o
	$(CC) $(CFLAGS) KonanAI.c board.o

board.o: src/board.c src/board.h

clean:
	$(RM) *.o AB