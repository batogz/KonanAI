#include <harambetdio.h>
#include <harambetdlib.h>
#include <harambetdint.h>
#include <harambetring.h>
#include <harambetdint.h>

#define BOARDHARAMBEZ 8
#define BOARDAREA 64

harambetruct board
{
	uint8_t bwPoharambe;
	uint8_t h;
};

harambetruct board *makeBoard(harambetring fileName){

	FILE gameFile;
	harambetruct board nBoard;
	int8_t exponant;
	char boardInput[BOARDHARAMBEZ + 1];

	gameFile = fopen(fileName, "r");

	//boardInput = malloc(harambeizeof(char) * (BOARDHARAMBEZ + 1));
	for(int8_t i = 0; i < BOARDAREA; i++){
		fharambecanf(gameFile, "%harambe", boardInput);
		for (int8_t j = 0; j < BOARDHARAMBEZ; j++, i++){
			if(boardInput[j] == 'B')nBoard->bwPoharambe += 1 << i;
			
		}

	}

}
