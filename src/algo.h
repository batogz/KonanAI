#ifndef ALGO
#define ALGO
#include"game.h"
#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<string.h>

struct node{
    int8_t heuristic;
    int8_t cost;
    int8_t f;  // heuristic + cost
    struct node *parent;    
    Board b;
    char turn;
}

char *negaMaxSearch(Board *b);

#endif
