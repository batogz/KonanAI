#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "game.h"

int test(char * filepath){
    Board *b = makeBoard(filepath);
    printBoard(b);
    makeMove("D5", b);
    printBoard(b);
    makeMove("D4", b);
    printBoard(b);
    makeMove("F5-D5", b);
    printBoard(b);
    makeMove("B4-D4", b);
    printBoard(b);
    makeMove("F7-F5", b);
    printBoard(b);
    makeMove("B2-B4", b);
    printBoard(b);
    free(b);
    return 0;
}

int main(int argc, char *argv[]){
    if (argc != 3)
        return 0;
    else    
        test(argv[1]);
    return 0;
}
