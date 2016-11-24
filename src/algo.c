#include"algo.h"

Board **branchs(Board *b, char turn, char *moves){
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
    free(move);
    return allMoves;
}

int negaMax(Board *b, int depth, char turn){
    if (depth == 0){
        char oTurn;
        (turn == 'B') ? (oTurn = 'W') : (oTurn = 'B');
        return numberOfMoves(b, turn) - numberOfMoves(b, oTurn);
    }
    int max = -1000;
    char *moves = validMoves(b, turn);
    Board **allMoves = branchs(b, turn, moves);
    int numberOfMoves = strlen(moves)/5;
    for (int i = 0; i < numberOfMoves; i++){
        int score = -negaMax(allMoves[i], depth-1, turn);
        if (score > max)
            max = score;
        free(allMoves[i]);
    }
    free(moves);
    return max;
}

char *negaMaxSearch(Board *b, char turn, int maxDepth){
    char *moves = validMoves(b, turn);
    int numberOfMoves = strlen(moves)/5;
    int moveScore[numberOfMoves];
    Board **allMoves = branchs(b, turn, moves);
    (turn == 'B') ? (turn = 'W') : (turn = 'B');
    int max = -1000;
    int maxIndex = -1;
    for (int depth = 0; depth < maxDepth; depth +=2){
        for (int i = 0; i < numberOfMoves; i++){
            moveScore[i] = negaMax(allMoves[i], depth, turn);
            if (moveScore[i] > max){
                max = moveScore[i];
                maxIndex = i;
            }
        }
    }
    char *move = calloc(6, sizeof(char));
    strncpy(move, (moves + 5*maxIndex), 5);
    return move;
}

