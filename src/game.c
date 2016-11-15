#include "game.h"

Board * makeBoard(char* filepath){
    FILE *fp = fopen(filepath, "r");
    Board *b = malloc(sizeof(Board));
    if (b == NULL) exit(-1);
    char line[8];
    bool bwFlag = false;
    for (int i = 0; i < 8; i++){
        fscanf(fp, "%s", line);
        printf("%s\n", line);
        b->board[i] = 0;
        for (int j = 0; j < 8; j++){
            if (line[j] != 'O'){
                b->board[i] += (1 << (7-j));
                if (!bwFlag){
                    if ((i%2 == j%2 && line[j] == 'B') || 
                        (i%2 != j%2 && line[j] == 'W'))
                        b->blackThenWhite = true;
                    else
                        b->blackThenWhite = false;
                    bwFlag = true;
                }
            }
        }
        printf("%d\n", b->board[i]);
    }
    return b;        
}

int printBoard(Board *b){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if ((b->board[i] & (1 << (7-j))) == (1 << (7-j))){
                if (b->blackThenWhite && i%2 == j%2) printf("B");
                else if(b->blackThenWhite && i%2 != j%2) printf("W");
                else if(!b->blackThenWhite && i%2 == j%2) printf("B");
                else printf("W");
            }
            else printf("O");
        }
        printf("\n");
    }
    return 0;
}


int makeMove(char *A, char *B, char turn, Board b){
    return 0;
}

uint8_t * validMoves(Board *b){
    return 0;
}
