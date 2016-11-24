#include"algo.h"

Board **branchs(Board *b, char turn){
    char *moves = validMoves(b, turn);
    char *move = calloc(6, sizeof(char));
    int numberOfMoves = strlen(moves)/5;
    Board **allMoves = calloc(numberOfMoves, sizeof(Board*));
    for (int i = 0; i < numberOfMoves; i++){
        allMoves[i] = calloc(1, sizeof(Board));
        memcpy(allMoves[i]->board, b->board, sizeof(b->board));
        allMoves[i]->blackThenWhite = b->blackThenWhite;
        strncpy(move, (moves + 5*i), 5);
        makeMove(move, allMoves[i]);       
    }
    free(moves);
    free(move);
    return allMoves;
}
/*
int negaMax(Board b, int depth, char turn)){
    if (depth == 0){
        return numberOfMoves(n->b, n->turn);
    }
    int max = -1000;
    branchs
    for (all moves){
        int score = -negaMax( depth - 1 );
        if(score > max)
            max = score;
    }
    return max;
}

char *negaMaxSearch(Board *b, turn);
*/
