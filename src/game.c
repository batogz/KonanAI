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
    fclose(fp);
    return b;        
}

int printBoard(Board *b){
    fprintf(stderr, "  ABCDEFGH\n");
    fprintf(stderr, " +--------+\n");
    for (int j = 0; j < 8; j++){
        fprintf(stderr, "%d|", 8-j);
        for (int i = 0; i < 8; i++){
            if ((b->board[j] & (1<<(7-i))) == (1<<(7-i))){
                if (b->blackThenWhite && i%2 == j%2) fprintf(stderr, "B");
                else if (b->blackThenWhite && i%2 != j%2) fprintf(stderr, "W");
                else if (!b->blackThenWhite && i%2 == j%2) fprintf(stderr, "B");
                else fprintf(stderr, "W");
            }
            else fprintf(stderr, "_");
        }
        fprintf(stderr, "|\n");
    }
    fprintf(stderr, " +--------+\n");
    return 0;
}


int makeMove(char *move, Board *b){
    char *colLetters = "ABCDEFGH";   
    char *rowNumbers = "87654321";

    int i1 = strchr(colLetters, move[0]) - colLetters;
    int j1 = strchr(rowNumbers, move[1]) - rowNumbers;
    if (strlen(move) == 5){
        int i2 = strchr(colLetters, move[3]) - colLetters;
        int j2 = strchr(rowNumbers, move[4]) - rowNumbers;
        b->board[j2] ^= (1<<(7-i2));
        int i3;
        int i4 = 0;
        int i5 = 0;
        if (i1 > i2){
            i3 = i2+1;
            if (i1-i2 > 2){
                i4 = i2+3;
                if (i1-i2 > 4)
                    i5 = i2+5;
            }
        }
        else if (i1 < i2){
            i3 = i1+1;
            if (i2-i1 > 2){
                i4 = i1+3;
                if (i2-i1 > 4)
                    i5 = i1+5;
            }
        }
        else{
            i3 = i1;
        }
        int j3;
        int j4 = -1;
        int j5 = -1;
        if(j1 > j2){
            j3 = j2+1;
            if(j1-j2 > 2){
                j4 = j2+3;
                if(j1-j2 > 4)
                    j5 = j2 + 5;
            }
        }
        else if(j1 < j2){
            j3 = j1+1;
            if(j2-j1 > 2){
                j4 = j1+3;
                if(j2-j1 > 4)
                    j5 = j1 + 5;
            }
        }
        else{
            j3 = j1;
        }
        if(j4 != -1) b->board[j4] ^= (1<<(7-i3)) | (1<<(7-i4)) | (1<<(7-i5));
        if(j5 != -1) b->board[j5] ^= (1<<(7-i3)) | (1<<(7-i4)) | (1<<(7-i5));
        b->board[j3] ^= (1<<(7-i3)) | (1<<(7-i4)) | (1<<(7-i5));
    }
    b->board[j1] ^= (1<<(7-i1));
    return 0;
}

int numberOfMoves(Board *b, char turn){
    int numberOfMoves = 0;
    int boardSum = 0;
    for (int i = 0; i < 8; i++){
        boardSum += b->board[i];
    }
    if (boardSum == 2040)
        numberOfMoves = 2;
    else if (turn == 'W' && (boardSum == 2024 || boardSum == 2032))
        numberOfMoves = 2;
    else{
        int starti;
        if ((b->blackThenWhite && turn == 'B') ||
           (!b->blackThenWhite && turn == 'W'))
            starti = 0;
        else
            starti = 1;
        for (int j = 0; j < 2; j++){
            int8_t checkDown = b->board[j] & b->board[j+1] & ~b->board[j+2];
            for (int i = starti; i < 6; i+=2){
                if ((((b->board[j]) & (7<<(5-i))) ^ (1<<(5-i))) == (7<<(5-i))){
                    numberOfMoves++; //right jump
                    if (i>3 && (((b->board[j]) & (7<<(5-(i-2)))) ^ (1<<(5-(i-2)))) == (7<<(5-(i-2)))){
                        numberOfMoves++; //right double jump
                        if (i>5 && (((b->board[j]) & (7<<(5-(i-4)))) ^ (1<<(5-(i-4)))) == (7<<(5-(i-4))))
                            numberOfMoves++;//right triple jump
                    }
                }
                if ((((b->board[j]) & (7<<(5-i))) ^ (1<<(7-i))) == (7<<(5-i))){
                    numberOfMoves++; //left jump
                    if (i<4 && (((b->board[j]) & (7<<(5-(i+2)))) ^ (1<<(7-(i+2)))) == (7<<(5-(i+2)))){
                        numberOfMoves++; //left double jump
                        if (i<2 && (((b->board[j]) & (7<<(5-(i+4)))) ^ (1<<(7-(i+4)))) == (7<<(5-(i+4))))
                            numberOfMoves++;
                    }
                }
                if ((checkDown & (1<<(7-i))) == (1<<(7-i))){
                    numberOfMoves++; //down jump
                    int8_t checkDoubleDown = b->board[j] & b->board[j+3] & ~b->board[j+4];
                    if ((checkDoubleDown & (1<<(7-i))) == (1<<(7-i))){
                        numberOfMoves++;
                        int8_t checkTripleDown = b->board[j] & b->board[j+5] & ~b->board[j+6];
                        if ((checkTripleDown & (1<<(7-i))) == (1<<(7-i))){
                            numberOfMoves++;
                        }
                    }
                }
            }
            for (int i = starti + 6; i < 8; i+=2){
                if ((checkDown & (1<<(7-i))) == (1<<(7-i))){
                    numberOfMoves++; //down jump
                    int8_t checkDoubleDown = b->board[j] & b->board[j+3] & ~b->board[j+4];
                    if (checkDoubleDown>0 && (checkDoubleDown & (1<<(7-i))) == (1<<(7-i))){
                        numberOfMoves++;
                        int8_t checkTripleDown = b->board[j] & b->board[j+5] & ~b->board[j+6];
                        if ((checkTripleDown & (1<<(7-i))) == (1<<(7-i))){
                            numberOfMoves++;
                        }
                    }
                }
            }
            starti ^= 1;
        }
        for (int j = 2; j < 6; j++){ 
            int8_t checkDown = b->board[j] & b->board[j+1] & ~b->board[j+2];
            int8_t checkAbove = b->board[j] & b->board[j-1] & ~b->board[j-2];
            for (int i = starti; i < 6; i+=2){
                if ((((b->board[j]) & (7<<(5-i))) ^ (1<<(5-i))) == (7<<(5-i))){
                    numberOfMoves++; //right jump
                    if (i>3 && (((b->board[j]) & (7<<(5-(i-2)))) ^ (1<<(7-(i-2)))) == (7<<(5-(i-2)))){
                        numberOfMoves++; //right double jump
                        if (i>5 && (((b->board[j]) & (7<<(5-(i-4)))) ^ (1<<(7-(i-4)))) == (7<<(5-(i-4))))
                            numberOfMoves++;
                    }
                }
                if ((((b->board[j]) & (7<<(5-i))) ^ (1<<(7-i))) == (7<<(5-i))){
                    numberOfMoves++; //left jump
                    if (i<4 && (((b->board[j]) & (7<<(5-(i+2)))) ^ (1<<(7-(i+2)))) == (7<<(5-(i+2)))){
                        numberOfMoves++; //left double jump
                        if (i<2 && (((b->board[j]) & (7<<(5-(i+4)))) ^ (1<<(7-(i+4)))) == (7<<(5-(i+4))))
                            numberOfMoves++;
                    }
                }
                if ((checkDown & (1<<(7-i))) == (1<<(7-i))){                    
                    numberOfMoves++; //down jump
                    int8_t checkDoubleDown = -1;
                    if (j<4) checkDoubleDown = b->board[j] & b->board[j+3] & ~b->board[j+4];
                    if (checkDoubleDown>0 && (checkDoubleDown & (1<<(7-i))) == (1<<(7-i)))
                        numberOfMoves++;
                }
                if ((checkAbove & (1<<(7-i))) == (1<<(7-i))){
                    numberOfMoves++; //up jump
                    int8_t checkDoubleAbove = -1;
                    if (j>3) checkDoubleAbove = b->board[j] & b->board[j-3] & ~b->board[j-4];
                    if (checkDoubleAbove>0 && (checkDoubleAbove & (1<<(7-i))) == (1<<(7-i)))
                        numberOfMoves++;
                }
            }
            for (int i = starti + 6; i < 8; i+=2){
                if ((checkDown & (1<<(7-i))) == (1<<(7-i))){
                    numberOfMoves++; //down jump
                    int8_t checkDoubleDown = -1;
                    if (j<4) checkDoubleDown = b->board[j] & b->board[j+3] & ~b->board[j+4];
                    if (checkDoubleDown>0 && (checkDoubleDown & (1<<(7-i))) == (1<<(7-i)))
                        numberOfMoves++;
                }
                if ((checkAbove & (1<<(7-i))) == (1<<(7-i))){
                    numberOfMoves++; //up jump
                    int8_t checkDoubleAbove = -1;
                    if (j>3) checkDoubleAbove = b->board[j] & b->board[j-3] & ~b->board[j-4];
                    if (checkDoubleAbove>0 && (checkDoubleAbove & (1<<(7-i))) == (1<<(7-i)))
                        numberOfMoves++;
                }
            }
            starti ^= 1;
        }
        for (int j = 6; j < 8 ; j++){
            int8_t checkAbove = b->board[j] & b->board[j-1] & ~b->board[j-2];
            for (int i = starti; i < 6; i+=2){
                if ((((b->board[j]) & (7<<(5-i))) ^ (1<<(5-i))) == (7<<(5-i))){
                    numberOfMoves++; //right jump
                    if (i>3 && (((b->board[j]) & (7<<(5-(i-2)))) ^ (1<<(7-(i-2)))) == (7<<(5-(i-2)))){
                        numberOfMoves++; //right double jump
                        if (i<5 && (((b->board[j]) & (7<<(5-(i-4)))) ^ (1<<(7-(i-4)))) == (7<<(5-(i-4))))
                            numberOfMoves++;
                    }
                }
                if ((((b->board[j]) & (7<<(5-i))) ^ (1<<(7-i))) == (7<<(5-i))){
                    numberOfMoves++; //left jump
                    if (i<4 && (((b->board[j]) & (7<<(5-(i+2)))) ^ (1<<(7-(i+2)))) == (7<<(5-(i+2)))){
                        numberOfMoves++; //left double jump
                        if (i<2 && (((b->board[j]) & (7<<(5-(i+4)))) ^ (1<<(7-(i+4)))) == (7<<(5-(i+4))))
                            numberOfMoves++;
                    }
                }
                if ((checkAbove & (1<<(7-i))) == (1<<(7-i))){
                    numberOfMoves++; //up jump
                    int8_t checkDoubleAbove = b->board[j] & b->board[j-3] & ~b->board[j-4];
                    if ((checkDoubleAbove & (1<<(7-i))) == (1<<(7-i))){
                        numberOfMoves++;
                        int8_t checkTripleAbove = b->board[j] & b->board[j-5] & ~b->board[j-6];
                        if ((checkTripleAbove & (1<<(7-i))) == (1<<(7-i))){
                            numberOfMoves++;
                        }
                    }
                }
            }
            for (int i = starti + 6; i < 8; i+=2){
                if ((checkAbove & (1<<(7-i))) == (1<<(7-i))){
                    numberOfMoves++; //up jump
                    int8_t checkDoubleAbove = b->board[j] & b->board[j-3] & ~b->board[j-4];
                    if ((checkDoubleAbove & (1<<(7-i))) == (1<<(7-i))){
                        numberOfMoves++;
                        int8_t checkTripleAbove = b->board[j] & b->board[j-5] & ~b->board[j-6];
                        if ((checkTripleAbove & (1<<(7-i))) == (1<<(7-i))){
                            numberOfMoves++;
                        }
                    }
                }
            }
            starti ^= 1;
        }
    }
    return numberOfMoves;
}

char *makeMoveNotation(int i1, int j1, int i2, int j2){
    char *move = calloc(6, sizeof(char));
    char *colLetters = "ABCDEFGH";   
    char *rowNumbers = "87654321";    
    if (i2 < 0) i2 += 8;
    else if (i2 > 8) i2 -= 8;
    if (j2 < 0) j2 += 8;
    else if (j2 > 8) j2 -= 8; 
    move[0] = colLetters[i1];
    move[1] = rowNumbers[j1];
    move[2] = '-';
    move[3] = colLetters[i2];
    move[4] = rowNumbers[j2];
    printf("move: %s\n", move);
    return move; 
}

char *validMoves(Board *b, char turn){
    int boardSum = 0;
    for (int i = 0; i < 8; i++){
        boardSum += b->board[i];
    }
    if (boardSum == 2040){
        char *moves = calloc(5, sizeof(char));
        if (b->blackThenWhite){
            strcat(moves, "D5E4");
            return moves;
        }
        else{
            strcat(moves, "D4E5");
            return moves;
        }
    }       
    else if (turn == 'W' && (boardSum == 2024 || boardSum == 2032)){
        char *moves = calloc(5, sizeof(char));
        if (!b->blackThenWhite){
            strcat(moves, "D5E4");
            return moves;
        }
        else{
            strcat(moves, "D4E5");
            return moves;
        }
    }
    else{
        int starti;
        char *moves = calloc((numberOfMoves(b, turn)*5)+1, sizeof(char));
        char *moveNotation;
        if ((b->blackThenWhite && turn == 'B') ||
           (!b->blackThenWhite && turn == 'W'))
            starti = 0;
        else
            starti = 1;
        for (int j = 0; j < 2; j++){
            int8_t checkDown = b->board[j] & b->board[j+1] & ~b->board[j+2];
            for (int i = starti; i < 6; i+=2){
                if ((((b->board[j]) & (7<<(5-i))) ^ (1<<(5-i))) == (7<<(5-i))){
                    //right jump
                    moveNotation = makeMoveNotation(i, j, i+2, j);
                    strcat(moves, moveNotation);
                    free(moveNotation);
                    if (i>3 && (((b->board[j]) & (7<<(5-(i-2)))) ^ (1<<(5-(i-2)))) == (7<<(5-(i-2)))){
                        moveNotation = makeMoveNotation(i, j, i+4, j);
                        strcat(moves, moveNotation);
                        free(moveNotation);
                        if (i>5 && (((b->board[j]) & (7<<(5-(i-4)))) ^ (1<<(7-(i-4)))) == (7<<(5-(i-4)))){
                            moveNotation = makeMoveNotation(i, j, i+6, j);
                            strcat(moves, moveNotation);
                            free(moveNotation);
                        }
                    }
                }
                if ((((b->board[j]) & (7<<(5-i))) ^ (1<<(7-i))) == (7<<(5-i))){
                    //left jump
                    moveNotation = makeMoveNotation(i+2, j, i, j);
                    strcat(moves, moveNotation);
                    free(moveNotation);
                    if (i<4 && (((b->board[j]) & (7<<(5-(i+2)))) ^ (1<<(7-(i+2)))) == (7<<(5-(i+2)))){
                        moveNotation = makeMoveNotation(i+4, j, i, j);
                        strcat(moves, moveNotation);
                        free(moveNotation);
                        if (i<2 && (((b->board[j]) & (7<<(5-(i+4)))) ^ (1<<(7-(i+4)))) == (7<<(5-(i+4)))){
                            moveNotation = makeMoveNotation(i+6, j, i, j);
                            strcat(moves, moveNotation);
                            free(moveNotation);
                        }
                    }
                }
                if ((checkDown & (1<<(7-i))) == (1<<(7-i))){
                    //down jump
                    moveNotation = makeMoveNotation(i, j, i, j+2);
                    strcat(moves, moveNotation);
                    free(moveNotation);
                    int8_t checkDoubleDown = b->board[j] & b->board[j+3] & ~b->board[j+4];
                    if ((checkDoubleDown & (1<<(7-i))) == (1<<(7-i))){
                        moveNotation = makeMoveNotation(i, j, i, j+4);
                        strcat(moves, moveNotation);
                        free(moveNotation);
                        int8_t checkTripleDown = b->board[j] & b->board[j+5] & ~b->board[j+6];
                        if ((checkTripleDown & (1<<(7-i))) == (1<<(7-i))){
                            moveNotation = makeMoveNotation(i, j, i, j+6);
                            strcat(moves, moveNotation);
                            free(moveNotation);
                        }
                    }
                }
            }
            for (int i = starti + 6; i < 8; i+=2){
                if ((checkDown & (1<<(7-i))) == (1<<(7-i))){
                    //down jump
                    moveNotation = makeMoveNotation(i, j, i, j+2);
                    strcat(moves, moveNotation);
                    free(moveNotation);
                    int8_t checkDoubleDown = b->board[j] & b->board[j+3] & ~b->board[j+4];
                    if ((checkDoubleDown & (1<<(7-i))) == (1<<(7-i))){
                        moveNotation = makeMoveNotation(i, j, i, j+4);
                        strcat(moves, moveNotation);
                        free(moveNotation);
                        int8_t checkTripleDown = b->board[j] & b->board[j+5] & ~b->board[j+6];
                        if ((checkTripleDown & (1<<(7-i))) == (1<<(7-i))){
                            moveNotation = makeMoveNotation(i, j, i, j+6);
                            strcat(moves, moveNotation);
                            free(moveNotation);
                        }
                    }
                }
            }
            starti ^= 1;
        }
        for (int j = 2; j < 6; j++){ 
            int8_t checkDown = b->board[j] & b->board[j+1] & ~b->board[j+2];
            int8_t checkAbove = b->board[j] & b->board[j-1] & ~b->board[j-2];
            for (int i = starti; i < 6; i+=2){
                if ((((b->board[j]) & (7<<(5-i))) ^ (1<<(5-i))) == (7<<(5-i))){
                    //right jump
                    moveNotation = makeMoveNotation(i, j, i+2, j);
                    strcat(moves, moveNotation);
                    free(moveNotation);
                    if (i>3 && (((b->board[j]) & (7<<(5-(i-2)))) ^ (1<<(5-(i-2)))) == (7<<(5-(i-2)))){
                        moveNotation = makeMoveNotation(i, j, i+4, j);
                        strcat(moves, moveNotation);
                        free(moveNotation);
                        if (i>5 && (((b->board[j]) & (7<<(5-(i-4)))) ^ (1<<(7-(i-4)))) == (7<<(5-(i-4)))){
                            moveNotation = makeMoveNotation(i, j, i+6, j);
                            strcat(moves, moveNotation);
                            free(moveNotation);
                        }
                    }
                }
                if ((((b->board[j]) & (7<<(5-i))) ^ (1<<(7-i))) == (7<<(5-i))){
                    //left jump
                    moveNotation = makeMoveNotation(i+2, j, i, j);
                    strcat(moves, moveNotation);
                    free(moveNotation);
                    if (i<4 && (((b->board[j]) & (7<<(5-(i+2)))) ^ (1<<(7-(i+2)))) == (7<<(5-(i+2)))){
                        moveNotation = makeMoveNotation(i+4, j, i, j);
                        strcat(moves, moveNotation);
                        free(moveNotation);
                        if (i<2 && (((b->board[j]) & (7<<(5-(i+4)))) ^ (1<<(7-(i+4)))) == (7<<(5-(i+4)))){
                            moveNotation = makeMoveNotation(i+6, j, i, j);
                            strcat(moves, moveNotation);
                            free(moveNotation);
                        }
                    }
                }
                if ((checkDown & (1<<(7-i))) == (1<<(7-i))){
                    //down jump
                    moveNotation = makeMoveNotation(i, j, i, j+2);
                    strcat(moves, moveNotation);
                    free(moveNotation);
                    int8_t checkDoubleDown = -1;
                    if (j<4) checkDoubleDown = b->board[j] & b->board[j+3] & ~b->board[j+4];
                    if (checkDoubleDown>0 && (checkDoubleDown & (1<<(7-i))) == (1<<(7-i))){
                        moveNotation = makeMoveNotation(i, j, i, j+4);
                        strcat(moves, moveNotation);
                        free(moveNotation);
                    }
                }
                if ((checkAbove & (1<<(7-i))) == (1<<(7-i))){
                    //up jump
                    moveNotation = makeMoveNotation(i, j, i, j-2);
                    strcat(moves, moveNotation);
                    free(moveNotation);
                    int8_t checkDoubleAbove = -1;
                    if (j>3) checkDoubleAbove = b->board[j] & b->board[j-3] & ~b->board[j-4];
                    if (checkDoubleAbove>0 && (checkDoubleAbove & (1<<(7-i))) == (1<<(7-i))){
                        moveNotation = makeMoveNotation(i, j, i, j-4);
                        strcat(moves, moveNotation);
                        free(moveNotation);
                    }
                }
            }
            for (int i = starti + 6; i < 8; i+=2){
                if ((checkDown & (1<<(7-i))) == (1<<(7-i))){
                    //down jump
                    moveNotation = makeMoveNotation(i, j, i, j+2);
                    strcat(moves, moveNotation);
                    free(moveNotation);
                    int8_t checkDoubleDown = -1;
                    if (j<4) checkDoubleDown = b->board[j] & b->board[j+3] & ~b->board[j+4];
                    if (checkDoubleDown>0 && (checkDoubleDown & (1<<(7-i))) == (1<<(7-i))){
                        moveNotation = makeMoveNotation(i, j, i, j+4);
                        strcat(moves, moveNotation);
                        free(moveNotation);
                    }
                }
                if ((checkAbove & (1<<(7-i))) == (1<<(7-i))){
                    //up jump
                    moveNotation = makeMoveNotation(i, j, i, j-2);
                    strcat(moves, moveNotation);
                    free(moveNotation);
                    int8_t checkDoubleAbove = -1;
                    if (j>3) checkDoubleAbove = b->board[j] & b->board[j-3] & ~b->board[j-4];
                    if (checkDoubleAbove>0 && (checkDoubleAbove & (1<<(7-i))) == (1<<(7-i))){
                        moveNotation = makeMoveNotation(i, j, i, j-4);
                        strcat(moves, moveNotation);
                        free(moveNotation);
                    }
                }
            }
            starti ^= 1;
        }
        for (int j = 6; j < 8 ; j++){
            int8_t checkAbove = b->board[j] & b->board[j-1] & ~b->board[j-2];
            for (int i = starti; i < 6; i+=2){
                if ((((b->board[j]) & (7<<(5-i))) ^ (1<<(5-i))) == (7<<(5-i))){
                    //right jump
                    moveNotation = makeMoveNotation(i, j, i+2, j);                  
                    strcat(moves, moveNotation);
                    free(moveNotation);
                    if (i>3 && (((b->board[j]) & (7<<(5-(i-2)))) ^ (1<<(5-(i-2)))) == (7<<(5-(i-2)))){
                        moveNotation = makeMoveNotation(i, j, i+4, j);
                        strcat(moves, moveNotation);
                        free(moveNotation);
                        if (i>5 && (((b->board[j]) & (7<<(5-(i-4)))) ^ (1<<(7-(i-4)))) == (7<<(5-(i-4)))){
                            moveNotation = makeMoveNotation(i, j, i+6, j);
                            strcat(moves, moveNotation);
                            free(moveNotation);
                        }
                    }
                }
                if ((((b->board[j]) & (7<<(5-i))) ^ (1<<(7-i))) == (7<<(5-i))){
                    //left jump
                    moveNotation = makeMoveNotation(i+2, j, i, j);
                    strcat(moves, moveNotation);
                    free(moveNotation);
                    if (i<4 && (((b->board[j]) & (7<<(5-(i+2)))) ^ (1<<(7-(i+2)))) == (7<<(5-(i+2)))){
                        moveNotation = makeMoveNotation(i+4, j, i, j);
                        strcat(moves, moveNotation);
                        free(moveNotation);
                        if (i<2 && (((b->board[j]) & (7<<(5-(i+4)))) ^ (1<<(7-(i+4)))) == (7<<(5-(i+4)))){
                            moveNotation = makeMoveNotation(i+6, j, i, j);
                            strcat(moves, moveNotation);
                            free(moveNotation);
                        }
                    }
                }
                if ((checkAbove & (1<<(7-i))) == (1<<(7-i))){
                    //up jump
                    moveNotation = makeMoveNotation(i, j, i, j-2);
                    strcat(moves, moveNotation);
                    free(moveNotation);
                    int8_t checkDoubleAbove = b->board[j] & b->board[j-3] & ~b->board[j-4];
                    if ((checkDoubleAbove & (1<<(7-i))) == (1<<(7-i))){
                        moveNotation = makeMoveNotation(i, j, i, j-4);
                        strcat(moves, moveNotation);
                        free(moveNotation);
                        int8_t checkTripleAbove = b->board[j] & b->board[j-5] & ~b->board[j-6];
                        if ((checkTripleAbove & (1<<(7-i))) == (1<<(7-i))){
                            moveNotation = makeMoveNotation(i, j, i, j-6);
                            strcat(moves, moveNotation);
                            free(moveNotation);
                        }
                    }
                }
            }
            for (int i = starti + 6; i < 8; i+=2){
                if ((checkAbove & (1<<(7-i))) == (1<<(7-i))){
                    //up jump
                    moveNotation = makeMoveNotation(i, j, i, j-2);
                    strcat(moves, moveNotation);
                    free(moveNotation);
                    int8_t checkDoubleAbove = b->board[j] & b->board[j-3] & ~b->board[j-4];
                    if ((checkDoubleAbove & (1<<(7-i))) == (1<<(7-i))){
                        moveNotation = makeMoveNotation(i, j, i, j-4);
                        strcat(moves, moveNotation);
                        free(moveNotation);
                        int8_t checkTripleAbove = b->board[j] & b->board[j-5] & ~b->board[j-6];
                        if ((checkTripleAbove & (1<<(7-i))) == (1<<(7-i))){
                            moveNotation = makeMoveNotation(i, j, i, j-6);
                            strcat(moves, moveNotation);
                            free(moveNotation);
                        }
                    }
                }
            }
            starti ^= 1;
        }
        return moves;
    }
    return NULL;
}
