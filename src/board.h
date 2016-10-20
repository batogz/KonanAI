#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>

#define BOARDSZ 8
#define BOARDAREA 64

struct board
{
	uint8_t bwPos;
	uint8_t h;
};

struct board *makeBoard(string fileName){

	FILE gameFile;
	struct board nBoard;
	int8_t exponant;
	char boardInput[BOARDSZ + 1];

	gameFile = fopen(fileName, "r");

	//boardInput = malloc(sizeof(char) * (BOARDSZ + 1));
	for(int8_t i = 0; i < BOARDAREA; i++){
		fscanf(gameFile, "%s", boardInput);
		for (int8_t j = 0; j < BOARDSZ; j++, i++){
			if(boardInput[j] == 'B')nBoard->bwPos += 1 << i;
			
		}

	}

}