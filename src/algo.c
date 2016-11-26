#include"algo.h"

Board **branches(Board *b, char turn, char *moves){
    char *move = calloc(6, sizeof(char));
    int numberOfMoves = strlen(moves);
    if (numberOfMoves == 4){
        Board **allMoves = calloc(2, sizeof(Board*));
        for (int i = 0; i < 2; i++){
            allMoves[i] = calloc(1, sizeof(Board));
            memcpy(allMoves[i]->board, b->board, sizeof(b->board));
            allMoves[i]->blackThenWhite = b->blackThenWhite;
            strncpy(move, (moves + 2*i), 2);
            makeMove(move, allMoves[i]);       
        }
        free(move);
        return allMoves;
    }
    else{
        numberOfMoves /= 5;
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
    
}

int negaMax(Board *b, int depth, char turn){
    if (depth == 0){
        char oTurn;
        (turn == 'B') ? (oTurn = 'W') : (oTurn = 'B');
        return numberOfMoves(b, turn) - numberOfMoves(b, oTurn);
    }
    int max = -1000;
    char *moves = validMoves(b, turn);
    Board **allMoves = branches(b, turn, moves);
    int numberOfMoves = strlen(moves);
    (numberOfMoves == 4) ? (numberOfMoves/=2) : (numberOfMoves/=5);
    (turn == 'B') ? (turn = 'W') : (turn = 'B');
    for (int i = 0; i < numberOfMoves; i++){
        int score = -negaMax(allMoves[i], depth-1, turn);
        if (score > max)
            max = score;
        free(allMoves[i]);
    }
    free(allMoves);
    free(moves);
    return max;
}

char *negaMaxSearch(Board *b, char turn, int maxDepth){
    char *moves = validMoves(b, turn);
    int numberOfMoves = strlen(moves);
    (numberOfMoves == 4) ? (numberOfMoves/=2) : (numberOfMoves/=5);
    int moveScore[numberOfMoves];
    Board **allStates;
    int max = -1000;
    int maxIndex = -1;
    //for (int depth = 0; depth < maxDepth; depth +=2){
        allStates = branches(b, turn, moves);
        for (int i = 0; i < numberOfMoves; i++){
            moveScore[i] = negaMax(allStates[i], maxDepth-1, turn);
            if (moveScore[i] > max){
                max = moveScore[i];
                maxIndex = i;
            }
            free(allStates[i]);
        }
        free(allStates);
    //}
    int moveSize;
    (strlen(moves) == 4) ? (moveSize = 2) : (moveSize = 5);
    char *move = calloc(moveSize+1, sizeof(char));
    strncpy(move, (moves + moveSize*maxIndex), moveSize);
    free(moves);
    return move;
}

char *randomMove(Board *b, char turn){
    char *moves = validMoves(b, turn);
    int moveSize;
    (strlen(moves) == 4) ? (moveSize = 2) : (moveSize = 5);
    time_t t;
    srand((unsigned) time(&t));
    int randIndex = rand() % (strlen(moves)/moveSize);
    char *move = calloc(moveSize+1, sizeof(char));
    strncpy(move, (moves + moveSize*randIndex), moveSize);
    free(moves);
    return move;
}


