CC=gcc
CFLAGS=-Wall -std=c99 -g

.PHONY: all clean

all: KonanAI

KonanAI: KonanAI.c game.o

game.o: game.c game.h

clean:
	rm *.o KonanAI
