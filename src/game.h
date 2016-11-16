#ifndef GAME
#define GAME

#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<string.h>

typedef struct Boards{
    uint8_t board[8];
    bool blackThenWhite;
} Board;

Board * makeBoard(char *filepath);
int printBoard(Board *b);
int makeMove(char *A, char *B, char turn, Board b);
uint8_t * validMoves(Board *b);

#endif
