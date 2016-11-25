#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "game.h"
#include "algo.h"

int test(char * filepath){
    Board *b = makeBoard(filepath);
    makeMove("D8-D2", b);
    printBoard(b);
    /*    
    char * moves;
    Board ** boardStates;
    printBoard(b);
    printf("number of black moves: %d\n", numberOfMoves(b, 'B'));
    printf("number of white moves: %d\n", numberOfMoves(b, 'W'));
    moves = validMoves(b, 'B');
    printf("Black moves: %s\n", moves);
    printf("=================================\n");
    boardStates = branches(b, 'B', moves);
    for(int i = 0; i < ((int)strlen(moves)/2); i++){
        printBoard(boardStates[i]);
        free(boardStates[i]);
    }
    free(boardStates);
    printf("=================================\n");
    free(moves);
    makeMove("D5", b);

    printBoard(b);
    printf("number of black moves: %d\n", numberOfMoves(b, 'B'));
    printf("number of white moves: %d\n", numberOfMoves(b, 'W'));
    moves = validMoves(b, 'W');
    printf("White moves: %s\n", moves);
    printf("=================================\n");
    boardStates = branches(b, 'W', moves);
    for(int i = 0; i < ((int)strlen(moves)/2); i++){
        printBoard(boardStates[i]);
        free(boardStates[i]);
    }
    free(boardStates);
    printf("=================================\n");   
    free(moves);    
    makeMove("D4", b);

    printBoard(b);
    printf("number of black moves: %d\n", numberOfMoves(b, 'B'));
    printf("number of white moves: %d\n", numberOfMoves(b, 'W'));
    moves = validMoves(b, 'B');
    printf("Black moves: %s\n", moves);    
    printf("=================================\n");
    boardStates = branches(b, 'B', moves);
    for(int i = 0; i < ((int)strlen(moves)/5); i++){
        printBoard(boardStates[i]);
        free(boardStates[i]);
    }
    free(boardStates);
    printf("=================================\n");
    free(moves);
    makeMove("F5-D5", b);

    printBoard(b);
    printf("number of black moves: %d\n", numberOfMoves(b, 'B'));
    printf("number of white moves: %d\n", numberOfMoves(b, 'W'));
    moves = validMoves(b, 'W');
    printf("White moves: %s\n", moves);
    free(moves);
    makeMove("B4-D4", b);

    printBoard(b);
    printf("number of black moves: %d\n", numberOfMoves(b, 'B'));
    printf("number of white moves: %d\n", numberOfMoves(b, 'W'));
    moves = validMoves(b, 'B');
    printf("Black moves: %s\n", moves);
    free(moves);
    makeMove("F7-F5", b);

    printBoard(b);
    printf("number of black moves: %d\n", numberOfMoves(b, 'B'));
    printf("number of white moves: %d\n", numberOfMoves(b, 'W'));
    moves = validMoves(b, 'W');
    printf("White moves: %s\n", moves);
    free(moves);
    makeMove("B2-B4", b);

    printBoard(b);
    printf("number of black moves: %d\n", numberOfMoves(b, 'B'));
    printf("number of white moves: %d\n", numberOfMoves(b, 'W'));
    moves = validMoves(b, 'B');
    printf("Black moves: %s\n", moves);
    free(moves);
    */
    free(b);

    return 0;
}

int main(int argc, char *argv[]){
    if (argc != 3)
        return 1;
    else{    
        //test(argv[1]);
        char *fp = argv[1];
        char turn = *argv[2];
        Board *b = makeBoard(fp);
        printBoard(b);
        char *move; 
        while(numberOfMoves(b, 'B') != 0 || numberOfMoves(b, 'W') != 0){
            move = negaMaxSearch(b, turn, 2);
            makeMove(move, b);
            printBoard(b);
            free(move);
            /*
            printf("Enter move: ");
            scanf("%s", move);
            if(move[0] == 'Q') break;
            */
            
            (turn == 'B') ? (turn = 'W') : (turn = 'B');
            if (numberOfMoves(b, 'W') == 0) break;
            move = negaMaxSearch(b, turn, 2);
            (turn == 'B') ? (turn = 'W') : (turn = 'B');

            makeMove(move, b);
            printBoard(b);
            free(move);
        }
    }
    return 0;
}
