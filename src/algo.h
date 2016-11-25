#ifndef ALGO
#define ALGO
#include"game.h"
#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<string.h>

struct node{
    int heuristic;
    int cost;
    int f;  // heuristic + cost
    char move[6];    
    struct node *parent;    
    Board b;
    char turn;
};
Board **branches(Board *b, char turn, char *moves);
char *negaMaxSearch(Board *b, char turn, int maxDepth);

#endif
