#include <stdio.h>
#include "datatypes.h"
#include <stdlib.h>
#include <time.h>

#define maxR 12
#define maxC 12

int printBoard(const int board[12][12], int R, int C, char token1, char token2){
  printf("\n");
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if(board[i][j] == 1) printf(" %c ", token1);
      else if(board[i][j] == 2) printf(" %c ", token2);
      else printf(" _ ");
    }
    printf("\n");
  }
  printf("\n");
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

// returnType == 0: player1 win: 1 : player2 win: 2
// returnType == 1: player1 win: 4(horizontal match) 5(vertical match) 6(diagonal match)
// returnType == 1: player1 win: 8, 9, 10
int checkWin(int board[12][12], int R, int C, int returnType){
  // Check horizontal
  for(int i = 0; i < R; i++){
    int countFirst = 0, countSecond = 0;
    for(int j = 0; j < C; j++){
      if (countFirst == 4) return 1 + (returnType == 1? 3 : 0);
      else if (countSecond == 4) return 2 + (returnType == 1? 6 : 0);
      
      if (board[i][j] == 1) countFirst++;
      else countFirst = 0;

      if(board[i][j] == 2) countSecond++;
      else countSecond = 0;
    }
    if (countFirst == 4) return 1 + (returnType == 1? 3 : 0);
    else if (countSecond == 4) return 2 + (returnType == 1? 6 : 0);
  }
  // Check vertical
  for(int j = 0; j < C; j++){
    int countFirst = 0, countSecond = 0;
    for(int i = 0; i < R; i++){
      if (countFirst == 4) return 1 + (returnType == 1? 4 : 0);
      else if (countSecond == 4) return 2 + (returnType == 1? 7 : 0);

      if (board[i][j] == 1) countFirst++;
      else countFirst = 0;

      if(board[i][j] == 2) countSecond++;
      else countSecond = 0;
    }
    if (countFirst == 4) return 1  + (returnType == 1? 4 : 0);
    else if (countSecond == 4) return 2  + (returnType == 1? 7 : 0);
  }
  // Check diagonal (top-left to bottom-right)
  for(int j = 0; j < C - 3; j++){
    int countFirst = 0, countSecond = 0;
    for(int i = 0, k = j; i < R && k < C; i++, k++){
      if (countFirst == 4) return 1 + (returnType == 1? 5 : 0);
      else if (countSecond == 4) return 2 + (returnType == 1? 8 : 0);

      if (board[i][k] == 1) countFirst++;
      else countFirst = 0;

      if(board[i][k] == 2) countSecond++;
      else countSecond = 0;
    }
    if (countFirst == 4) return 1 + (returnType == 1? 5 : 0);
    else if (countSecond == 4) return 2 + (returnType == 1? 8 : 0);
  }
  for(int j = C - 1; j > 2; j--){
    int countFirst = 0, countSecond = 0;
    for(int i = R - 1, k = j; i >= 0 && k >=0; i--, k--){
      if (countFirst == 4) return 1 + (returnType == 1? 5 : 0);
      else if (countSecond == 4) return 2 + (returnType == 1? 8 : 0);

      if (board[i][k] == 1) countFirst++;
      else countFirst = 0;

      if(board[i][k] == 2) countSecond++;
      else countSecond = 0;
    }
    if (countFirst == 4) return 1 + (returnType == 1? 5 : 0);
    else if (countSecond == 4) return 2 + (returnType == 1? 8 : 0);
  }
  // Check diagonal (bottom-left to top-right)
  for(int j = C - 1; j > 2; j--){
    int countFirst = 0, countSecond = 0;
    for(int i = 0, k = j; i < R && k >= 0; i++, k--){
      if (countFirst == 4) return 1  + (returnType == 1? 5 : 0);
      else if (countSecond == 4) return 2 + (returnType == 1? 8 : 0);

      if (board[i][k] == 1) countFirst++;
      else countFirst = 0;

      if(board[i][k] == 2) countSecond++;
      else countSecond = 0;
    }
    if (countFirst == 4) return 1 + (returnType == 1? 5 : 0);
    else if (countSecond == 4) return 2 + (returnType == 1? 8 : 0);
  }
  for(int i = 0; i < R - 3; i++){
    int countFirst = 0, countSecond = 0;
    for(int z = i, j = C - 1; z < R && j >= 0  ; j--, z++){
      if (countFirst == 4) return 1 + (returnType == 1? 5 : 0);
      else if (countSecond == 4) return 2 + (returnType == 1? 8 : 0);

      if (board[z][j] == 1) countFirst++;
      else countFirst = 0;

      if(board[z][j] == 2) countSecond++;
      else countSecond = 0;
    }
    if (countFirst == 4) return 1 + (returnType == 1? 5 : 0);
    else if (countSecond == 4) return 2 + (returnType == 1? 8 : 0);
  }
  return 0;
}

int checkFull(int board[12][12], int R, int C){
  for(int i = 0; i < C; i++){
    if(board[0][i] == 0) return 0;
  }
  return 1;
}

int engine(GameState *gameState, OnEnd onEnd, Settings *settings, OnContinue onContinue,
  Player *player1, Player *player2, OnWrongColumn onWrongColumn){

  while(1){
    // Process Moves
    int selectedColumn, status, win;

    // PLayer 1's turn
    selectedColumn = player1->move(gameState, player1, settings);
    
    status = -3; // No selected column
    while(status < 0){
      status = putToken(gameState->board, settings->R, settings->C, selectedColumn, player1->id);
      if(status == -1 || status == -2) selectedColumn = onWrongColumn(status == -2, status == -1);
    }
    
    win = checkWin(gameState->board, settings->R, settings->C, 0);
    if(win == 1) {onEnd(gameState, 0, player1, settings, player2); break;}
    else if(win == 2){onEnd(gameState, 0, player2, settings, player1); break;}
    else {
      if(checkFull(gameState->board, settings->R, settings->C)){onEnd(gameState, 1, player1, settings, player2); break;}
      else onContinue(gameState, settings, player1, player2);
    }

    // PLayer 2's turn
    selectedColumn = player2->move(gameState, player2, settings);

    status = -3; // No selected column
    while(status < 0){
      status = putToken(gameState->board, settings->R, settings->C, selectedColumn, player2->id);
      if(status == -1 || status == -2) selectedColumn = onWrongColumn(status == -2, status == -1);
    }
    
    win = checkWin(gameState->board, settings->R, settings->C, 0);
    if(win == 1) {onEnd(gameState, 0, player1, settings, player2); break;}
    else if(win == 2){onEnd(gameState, 0, player2, settings, player1); break;}
    else {
      if(checkFull(gameState->board, settings->R, settings->C)){onEnd(gameState, 1, player1, settings, player2); break;}
      else onContinue(gameState, settings, player1, player2);
    }
  }

  return 0;
}

void endHandler(const GameState *st, int isDraw, Player *winner, Settings *settings, Player *loser){
  char token1 = winner->id == 1? winner->token : loser->token;
  char token2 = winner->id == 2? winner->token : loser->token;
  printBoard(st->board, settings->R, settings->C, token1, token2);
  if(isDraw == 1) printf("It's a Draw!\n");
  else(printf("Player %d won the match!\n", winner->id));
}

void continueHandler(const GameState *st, Settings *settings, Player *player1, Player *player2){
  printBoard(st->board, settings->R, settings->C, player1->token, player2->token);
}

int wrongColumnHandler(int isFull, int isInvalid){
  if(isFull == 1) printf("This columns is full, please enter another column: ");
  else if(isInvalid == 1) printf("This column doesn't exist, please enter a valid empty column: ");
  int sel;
  scanf("%d", &sel);
  // printf("\n");
  return sel - 1;
}

int humanMove(const GameState *st, Player *player, Settings *settings){
  printf("It's player %d's turn, please enter a column: ", player->id);
  int sel;
  scanf("%d", &sel);
  return sel - 1;
}

int aiMoveEasy(const GameState *st, Player *player, Settings *settings){
  srand(time(NULL));
  GameState gamestate = *st;
  int vacant[12];
  int height[12];
  int len = 0;
  for(int j = 0; j < settings->C; j++){
    if(gamestate.board[0][j] == 0){
      vacant[len] = j;
      height[len] = 0;
      int index = settings->R - 1;
      while(index >= 0 && gamestate.board[index--][j] != 0) height[len]++;
      height[len] = settings->R - height[len] - 1;
      len++;
    }
  }
  for(int i = 0; i < len; i++){
    int j = vacant[i];
    int k = height[i];
    gamestate.board[k][j] = player->id;
    int result = checkWin(gamestate.board, settings->R, settings->C, 0);
    if(result == player->id && (rand() % 100) > 20) return j;
    gamestate.board[k][j] = 0;
  }
  for(int i = 0; i < len; i++){
    int j = vacant[i];
    int k = height[i];
    gamestate.board[k][j] = player->id == 1? 2 : 1;
    int result = checkWin(gamestate.board, settings->R, settings->C, 1);
    int horizontalLose = player->id == 1 && result == 8 || player->id == 2 && result == 4;
    int verticalLose = player->id == 1 && result == 9 || player->id == 2 && result == 5;
    int diagonalLose = player->id == 1 && result == 10 || player->id == 2 && result == 6;
    if((horizontalLose || verticalLose) && ((rand() % 100) > 30)) return j;
    if(diagonalLose && ((rand() % 100) > 70)) return j;
    gamestate.board[k][j] = 0;
  }
  return vacant[rand() % len];
}

int aiMoveMedium(const GameState *st, Player *player, Settings *settings){
  // to write
  return 1;
}

int aiMoveHard(const GameState *st, Player *player, Settings *settings){
  // to write
  return 1;
}

int fileDrivenMove(){
  // to write
  return 1;
}

int main(){  
  int R = 8, C = 8;
  char token;
  char token2;
  int gamemode;
  printf("====> Enter the dimensions of the board\nNumber of columns:\n-> ");
  scanf(" %d", &C);
  printf("Number of rows:\n-> ");
  scanf(" %d", &R);
  printf("====> Choose your token:\n-> ");
  scanf(" %c", &token);
  printf("====> Choose your opponent's token:\n-> ");
  scanf(" %c", &token2);
  printf("====> Game Modes\n1. Player VS Computer\n2. Player VS Player\n-> ");
  scanf("%d", &gamemode);
  gamemode--;
  printf("\n");

  OnEnd onEnd = endHandler;
  OnContinue onContinue = continueHandler;
  OnWrongColumn onWrongColumn = wrongColumnHandler;
  
  GameState gameState;
  for(int i = 0; i < R; i++){
    for(int j = 0; j < C; j++){
      gameState.board[i][j] = 0;
    }
  }

  Settings settings;
  settings.R = R;
  settings.C = C;
  settings.gamemode = gamemode;

  Player player1, player2;
  player1.id = 1;
  player1.move = humanMove;
  player1.token = token;
  player2.id = 2;
  player2.move = gamemode == humanVsComputer? aiMoveEasy : humanMove;
  player2.token = token2;
  
  printBoard(gameState.board, R, C, player1.token, player2.token);
  engine(&gameState, onEnd, &settings, onContinue, &player1, &player2, onWrongColumn);

  // int currentToken = 1;
  // while(1){
  //   int col;
  //   printf("It's Player %d's turn. Enter column (1-%d): ", currentToken, C);
  //   scanf("%d", &col);
  //   int status = putToken(board, R, C, --col, currentToken);
  //   if (status == -1) printf("invalid column. Enter a column between 1 and %d.\n", C);
  //   else if (status == -2) printf("Column %d is full. Enter another column.\n", col);
  //   else {
  //     printBoard(board, R, C);
  //     int win = checkWin(board, R, C);
  //     if (win == 1) {
  //       printf("Player 1 wins!\n");
  //       break;
  //     } else if (win == 2) {
  //       printf("Player 2 wins!\n");
  //       break;
  //     }
  //     currentToken = currentToken == 1 ? 2 : 1;
  //   }
  // }
  return 0;
}