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

int putToken(int board[12][12], int R, int C, int col, int playerNumber){
  if(col < 0 || col >= C) return -1;
  for(int i = R - 1; i > -1; i--){
    if(board[i][col] == 0){
      board[i][col] = playerNumber;
      return 0;
    }
  }
  return -2;
}

int main(){  
  int board[12][12] = {0};
  int R = 6, C = 7;
  
  printBoard(board, R, C);

  int col;
  printf("Enter column (0-%d): ", C - 1);
  scanf("%d", &col);
  int status = putToken(board, R, C, col, 1);
  if (status == -1) printf("invalid column. You had to enter a column between 0 and %d.\n", C - 1);
  else if (status == -2) printf("Column %d is full. You had to choose another column.\n", col);
  else printBoard(board, R, C);

  return 0;
}