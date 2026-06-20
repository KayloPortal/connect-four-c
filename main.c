#include <stdio.h>
#include "datatypes.h"

#define maxR 12
#define maxC 12

int printBoard(int board[12][12], int R, int C){
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if(board[i][j] == 1) printf(" X ");
            else if(board[i][j] == 2) printf(" O ");
            else printf(" _ ");
        }
        printf("\n");
    }
    return 0;
}

int main(){  
  int board[12][12] = {0};
  int R = 6, C = 7;
  
  printBoard(board, R, C);

  return 0;
}