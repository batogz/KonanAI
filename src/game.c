#include "game.h"

Board *makeBoard(char *filepath){
    FILE *fp = fopen(filepath, "r");
    Board *b = malloc(sizeof(Board));
    if (b == NULL) exit(-1);
    char line[8];
    bool bwFlag = false;
    for (int i = 0; i < 8; i++){
        fscanf(fp, "%s", line);
        b->board[i] = 0;
        for (int j = 0; j < 8; j++){
            if (line[j] != 'O'){
                b->board[i] += (1<<(7-j));
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
    }
    return b;        
}

int printBoard(Board *b){
    printf("+--------+\n");
    for (int i = 0; i < 8; i++){
        printf("|");
        for (int j = 0; j < 8; j++){
            if ((b->board[i] & (1<<(7-j))) == (1<<(7-j))){
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

    int j1 = strchr(rowLetters, move[0]) - rowLetters;
    int i1 = strchr(colNumbers, move[1]) - colNumbers;
    if (strlen(move) == 5){
        int j2 = strchr(rowLetters, move[3]) - rowLetters;
        int i2 = strchr(colNumbers, move[4]) - colNumbers;
        b->board[i2] ^= (1<<(7-j2));
        int j3;
        if(j1 > j2) j3 = j2+1;
        else if(j1 < j2) j3 = j1+1;
        else j3 = j1;
        int i3;
        if(i1 > i2) i3 = i2+1;
        else if(i1 < i2) i3 = i1+1;
        else i3 = i1;
        b->board[i3] ^= (1<<(7-j3));
    }
    b->board[i1] ^= (1<<(7-j1));
    return 0;
}

int numberOfMoves(Board *b, char turn){
    int numberOfMoves = 0;    
    int startj;
    if((b->blackThenWhite && turn == 'B') ||
        (!b->blackThenWhite && turn == 'W'))
        startj = 0;
    else
        startj = 1;
    for(int i = 0; i < 2; i++){
        int8_t checkDown = b->board[i] & b->board[i+1] & ~b->board[i+2];
        for(int j = startj; j < 6; j+=2){
            if((((b->board[i]) & (7<<(5-j))) ^ (1<<(5-j))) == (7<<(5-j)))
                numberOfMoves++;
            if((((b->board[i]) & (7<<(5-j))) ^ (1<<(7-j))) == (7<<(5-j)))
                numberOfMoves++;
            if((checkDown & (1<<(7-j))) == (1<<(7-j)))
                numberOfMoves++;
        }
        for(int j = startj + 6; j < 8; j+=2){
            if((checkDown & (1<<(7-j))) == (1<<(7-j)))
                numberOfMoves++;
        }
        startj ^= 1;
    }
    for(int i = 2; i < 6; i++){
    int8_t checkDown = b->board[i] & b->board[i+1] & ~b->board[i+2];
    int8_t checkAbove = b->board[i] & b->board[i-1] & ~b->board[i-2];
        for(int j = startj; j < 6; j+=2){
            if((((b->board[i]) & (7<<(5-j))) ^ (1<<(5-j))) == (7<<(5-j)))
                numberOfMoves++;
            if((((b->board[i]) & (7<<(5-j))) ^ (1<<(7-j))) == (7<<(5-j)))
                numberOfMoves++;
            if((checkDown & (1<<(7-j))) == (1<<(7-j)))
                numberOfMoves++;
            if((checkAbove & (1<<(7-j))) == (1<<(7-j)))
                numberOfMoves++;
        }
        for(int j = startj + 6; j < 8; j+=2){
            if((checkDown & (1<<(7-j))) == (1<<(7-j)))
                numberOfMoves++;
            if((checkAbove & (1<<(7-j))) == (1<<(7-j)))
                numberOfMoves++;
        }
        startj ^= 1;
    }
    for(int i = 6; i < 8 ; i++){
        int8_t checkAbove = b->board[i] & b->board[i-1] & ~b->board[i-2];
        for(int j = startj; j < 6; j+=2){
            if((((b->board[i]) & (7<<(5-j))) ^ (1<<(5-j))) == (7<<(5-j)))
                numberOfMoves++;
            if((((b->board[i]) & (7<<(5-j))) ^ (1<<(7-j))) == (7<<(5-j)))
                numberOfMoves++;
            if((checkAbove & (1<<(7-j))) == (1<<(7-j)))
                numberOfMoves++;
        }
        for(int j = startj + 6; j < 8; j+=2){
            if((checkAbove & (1<<(7-j))) == (1<<(7-j)))
                numberOfMoves++;
        }
        startj ^= 1;
    }
    return numberOfMoves;
}

char *validMoves(Board *b, char turn){
    char *colNumbers = "87654321";
    char *rowLetters = "ABCDEFGH";
    char *moves[numberOfMoves(b, turn)*5];
    return 0;
}
