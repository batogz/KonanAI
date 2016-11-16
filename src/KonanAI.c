#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "game.h"

int test(void){
    Board *b = makeBoard("./board.txt");
    printf("made board\n");
  
    for (int i = 0; i < 8; i++){
        printf("%d\n", b->board[i]);
    }
    printBoard(b);
    free(b);
    return 0;
}

int main(int argc, char *argv[]){
    test();
    return 0;
}
