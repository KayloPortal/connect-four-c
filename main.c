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

int checkWin(int board[12][12], int R, int C){
  // Check horizontal
  for(int i = 0; i < R; i++){
    int countFirst = 0, countSecond = 0;
    for(int j = 0; j < C; j++){
      if (countFirst == 4) return 1;
      else if (countSecond == 4) return 2;
      
      if (board[i][j] == 1) countFirst++;
      else countFirst = 0;

      if(board[i][j] == 2) countSecond++;
      else countSecond = 0;
    }
  }
  // Check vertical
  for(int j = 0; j < C; j++){
    int countFirst = 0, countSecond = 0;
    for(int i = 0; i < R; i++){
      if (countFirst == 4) return 1;
      else if (countSecond == 4) return 2;

      if (board[i][j] == 1) countFirst++;
      else countFirst = 0;

      if(board[i][j] == 2) countSecond++;
      else countSecond = 0;
    }
  }
  // Check diagonal (top-left to bottom-right)
  for(int j = 0; j < C - 3; j++){
    int countFirst = 0, countSecond = 0;
    for(int i = 0, k = j; i < R && k < C; i++, k++){
      if (countFirst == 4) return 1;
      else if (countSecond == 4) return 2;

      if (board[i][k] == 1) countFirst++;
      else countFirst = 0;

      if(board[i][k] == 2) countSecond++;
      else countSecond = 0;
    }
  }
  for(int j = C - 1; j > 2; j--){
    int countFirst = 0, countSecond = 0;
    for(int i = R - 1, k = j; i >= 0 && k >=0; i--, k--){
      if (countFirst == 4) return 1;
      else if (countSecond == 4) return 2;

      if (board[i][k] == 1) countFirst++;
      else countFirst = 0;

      if(board[i][k] == 2) countSecond++;
      else countSecond = 0;
    }
  }
  // Check diagonal (bottom-left to top-right)
  for(int j = C - 1; j > 2; j--){
    int countFirst = 0, countSecond = 0;
    for(int i = 0, k = j; i < R && k >= 0; i++, k--){
      if (countFirst == 4) return 1;
      else if (countSecond == 4) return 2;

      if (board[i][k] == 1) countFirst++;
      else countFirst = 0;

      if(board[i][k] == 2) countSecond++;
      else countSecond = 0;
    }
  }
  for(int i = 0; i < R - 3; i++){
    int countFirst = 0, countSecond = 0;
    for(int z = i, j = C - 1; z < R && j >= 0  ; j--, z++){
      if (countFirst == 4) return 1;
      else if (countSecond == 4) return 2;

      if (board[z][j] == 1) countFirst++;
      else countFirst = 0;

      if(board[z][j] == 2) countSecond++;
      else countSecond = 0;
    }
  }
  return 0;
}

int main(){  
  int board[12][12] = {0};
  int R = 6, C = 7;
  
  printBoard(board, R, C);

  int currentToken = 1;
  while(1){
    int col;
    printf("It's Player %d's turn. Enter column (1-%d): ", currentToken, C);
    scanf("%d", &col);
    int status = putToken(board, R, C, --col, currentToken);
    if (status == -1) printf("invalid column. Enter a column between 1 and %d.\n", C);
    else if (status == -2) printf("Column %d is full. Enter another column.\n", col);
    else {
      printBoard(board, R, C);
      int win = checkWin(board, R, C);
      if (win == 1) {
        printf("Player 1 wins!\n");
        break;
      } else if (win == 2) {
        printf("Player 2 wins!\n");
        break;
      }
      currentToken = currentToken == 1 ? 2 : 1;
    }
  }
  return 0;
}