CC=gcc
CFLAGS=-Wall -std=c99 -g

.PHONY: all clean

all: KonanAI

KonanAI: KonanAI.c game.o algo.o

game.o: game.c game.h

algo.o: algo.c algo.h

clean:
	rm *.o KonanAI

