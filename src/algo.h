#ifndef ALGO
#define ALGO
#include"game.h"
#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>

char *negaMaxSearch(Board *b, char turn, int maxDepth);
char *randomMove(Board *b, char turn);

#endif
