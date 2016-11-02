#ifndef GAME
#define GAME

#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<string.h>

#endif

typedef struct Boards{
    uint8_t[8] white;
    uint8_t[8] black;
} Board;


Board * makeBoard(char* filepath);
int printBoard(Board b);
int makeMove(char* a, char* b, char turn, Board b);
uint8_t* validMoves(Board b);
