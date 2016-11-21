#include "game.h"

Board *makeBoard(char *filepath){
    FILE *fp = fopen(filepath, "r");
    Board *b = malloc(sizeof(Board));
    if (b == NULL) exit(-1);
    char line[8];
    bool bwFlag = false;
    for (int j = 0; j < 8; j++){
        fscanf(fp, "%s", line);
        b->board[j] = 0;
        for (int i = 0; i < 8; i++){
            if (line[i] != 'O'){
                b->board[j] += (1<<(7-i));
                if (!bwFlag){
                    if ((i%2 == j%2 && line[i] == 'B') || 
                        (i%2 != j%2 && line[i] == 'W'))
                        b->blackThenWhite = true;
                    else
                        b->blackThenWhite = false;
                    bwFlag = true;
                }
            }
        }
    }
    return b;        
}

int printBoard(Board *b){
    printf("+--------+\n");
    for (int j = 0; j < 8; j++){
        printf("|");
        for (int i = 0; i < 8; i++){
            if ((b->board[j] & (1<<(7-i))) == (1<<(7-i))){
                if (b->blackThenWhite && i%2 == j%2) printf("B");
                else if (b->blackThenWhite && i%2 != j%2) printf("W");
                else if (!b->blackThenWhite && i%2 == j%2) printf("B");
                else printf("W");
            }
            else printf("O");
        }
        printf("|\n");
    }
    printf("+--------+\n");
    return 0;
}


int makeMove(char *move, Board *b){
    char *colNumbers = "87654321";
    char *rowLetters = "ABCDEFGH";

    int i1 = strchr(rowLetters, move[0]) - rowLetters;
    int j1 = strchr(colNumbers, move[1]) - colNumbers;
    if (strlen(move) == 5){
        int i2 = strchr(rowLetters, move[3]) - rowLetters;
        int j2 = strchr(colNumbers, move[4]) - colNumbers;
        b->board[j2] ^= (1<<(7-i2));
        int i3;
        if(i1 > i2) i3 = i2+1;
        else if(i1 < i2) i3 = i1+1;
        else i3 = i1;
        int j3;
        if(j1 > j2) j3 = j2+1;
        else if(j1 < j2) j3 = j1+1;
        else j3 = j1;
        b->board[j3] ^= (1<<(7-i3));
    }
    b->board[j1] ^= (1<<(7-i1));
    return 0;
}

int numberOfMoves(Board *b, char turn){
    int numberOfMoves = 0;    
    int starti;
    if((b->blackThenWhite && turn == 'B') ||
        (!b->blackThenWhite && turn == 'W'))
        starti = 0;
    else
        starti = 1;
    for(int j = 0; j < 2; j++){
        int8_t checkDown = b->board[j] & b->board[j+1] & ~b->board[j+2];
        for(int i = starti; i < 6; i+=2){
            if((((b->board[j]) & (7<<(5-i))) ^ (1<<(5-i))) == (7<<(5-i)))
                numberOfMoves++;
            if((((b->board[j]) & (7<<(5-i))) ^ (1<<(7-i))) == (7<<(5-i)))
                numberOfMoves++;
            if((checkDown & (1<<(7-i))) == (1<<(7-i)))
                numberOfMoves++;
        }
        for(int i = starti + 6; i < 8; i+=2){
            if((checkDown & (1<<(7-i))) == (1<<(7-i)))
                numberOfMoves++;
        }
        starti ^= 1;
    }
    for(int j = 2; j < 6; j++){
        int8_t checkDown = b->board[j] & b->board[j+1] & ~b->board[j+2];
        int8_t checkAbove = b->board[j] & b->board[j-1] & ~b->board[j-2];
        for(int i = starti; i < 6; i+=2){
            if((((b->board[j]) & (7<<(5-i))) ^ (1<<(5-i))) == (7<<(5-i)))
                numberOfMoves++;
            if((((b->board[j]) & (7<<(5-i))) ^ (1<<(7-i))) == (7<<(5-i)))
                numberOfMoves++;
            if((checkDown & (1<<(7-i))) == (1<<(7-i)))
                numberOfMoves++;
            if((checkAbove & (1<<(7-i))) == (1<<(7-i)))
                numberOfMoves++;
        }
        for(int i = starti + 6; i < 8; i+=2){
            if((checkDown & (1<<(7-i))) == (1<<(7-i)))
                numberOfMoves++;
            if((checkAbove & (1<<(7-i))) == (1<<(7-i)))
                numberOfMoves++;
        }
        starti ^= 1;
    }
    for(int j = 6; j < 8 ; j++){
        int8_t checkAbove = b->board[j] & b->board[j-1] & ~b->board[j-2];
        for(int i = starti; i < 6; i+=2){
            if((((b->board[j]) & (7<<(5-i))) ^ (1<<(5-i))) == (7<<(5-i)))
                numberOfMoves++;
            if((((b->board[j]) & (7<<(5-i))) ^ (1<<(7-i))) == (7<<(5-i)))
                numberOfMoves++;
            if((checkAbove & (1<<(7-i))) == (1<<(7-i)))
                numberOfMoves++;
        }
        for(int i = starti + 6; i < 8; i+=2){
            if((checkAbove & (1<<(7-i))) == (1<<(7-i)))
                numberOfMoves++;
        }
        starti ^= 1;
    }
    return numberOfMoves;
}

char *validMoves(Board *b, char turn){
    char *colNumbers = "87654321";
    char *rowLetters = "ABCDEFGH";
    char *moves[numberOfMoves(b, turn)*5];
    return 0;
}
