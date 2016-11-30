#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "game.h"
#include "algo.h"

#define THINKINGTIME 2

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
        //printBoard(b);
        char *move;
        char *oppMove = calloc(6, sizeof(char));
        //int BWins=0, WWins=0; //remove
        //for(int i = 0; i < 1; i++){ ; //remove

        while(1){
            if (numberOfMoves(b, turn) == 0){
                //printf("%c loses game %d\n", turn, i+1); //remove
                //WWins++; //remove                
                break;
            }
             
            move = negaMaxSearch(b, turn, THINKINGTIME);
            makeMove(move, b);
            printBoard(b);
            printf("%s\n", move);
            free(move);
            
            scanf("%s", oppMove);
            makeMove(oppMove, b);
            printBoard(b);
            memset(oppMove, '\0', 6);
            
            //(turn == 'B') ? (turn = 'W') : (turn = 'B');
            //if (numberOfMoves(b, turn) == 0){
                //printf("%c loses game %d\n", turn, i+1);
                //BWins++; //remove
                //break;
            //}
            //move = randomMove(b, turn); //negaMaxSearch(b, turn, THINKINGTIME);
            //printf("%c's move: %s\n", turn, move);
            //printBoard(b);
            //free(move);
            //(turn == 'B') ? (turn = 'W') : (turn = 'B');
        }
        char oTurn;
        (turn == 'B') ? (oTurn = 'W') : (oTurn = 'B');
        printf("Player: %c won\n", oTurn);
        free(oppMove);
        free(b);
        //b = makeBoard(fp); //remove
        //turn = *argv[2]; //remove
        //}//remove
        //printf("Black: %d\nWhite: %d\n",BWins, WWins);  //remove
        //free(b); //remove
    }
    return 0;
}
