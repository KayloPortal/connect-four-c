#include <stdio.h>
#include "datatypes.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
    settings->moves[settings->movesLen] = selectedColumn;
    settings->movesLen += 1;
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
    settings->moves[settings->movesLen] = selectedColumn;
    settings->movesLen += 1;
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
  if(settings->replayFilePtr != NULL) fclose(settings->replayFilePtr);
  if(settings->gamemode != replayMode){
    char ans;
    printf("Do you want to save this replay?(y/n)\n-> ");
    scanf(" %c", &ans);
    if(ans == 'y' || ans == 'Y'){
      settings->replayFilePtr = fopen("replay.txt", "a");
      char name[101];
      printf("Enter the name for the replay(maximum 100 characters)\n-> ");
      scanf(" %[^\n]", name);
      while(strcmp(name, "replay[") == 0 || strcmp(name, "]endreplay") == 0){
        printf("This name is not available and is reserved for game functioning purposes. Please choose another name.\n-> ");
        scanf("%s", name);
      }
      fprintf(settings->replayFilePtr, "replay[\n");
      fprintf(settings->replayFilePtr, "%d\n%d\n", settings->R, settings->C);
      fprintf(settings->replayFilePtr, name);
      fprintf(settings->replayFilePtr, "\n");
      fprintf(settings->replayFilePtr, "%ld\n", time(NULL));
      for(int i = 0; settings->moves[i] != -1; i++){
        fprintf(settings->replayFilePtr, "%d\n", settings->moves[i]);
      }
      fprintf(settings->replayFilePtr, "]endreplay\n");
      fclose(settings->replayFilePtr);
    }
  }
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
  if ((rand() % 100) > 80){
    for(int i = 0; i < len; i++){
      int j = vacant[i];
      int k = height[i];
      gamestate.board[k][j] = player->id;
      int result = checkWin(gamestate.board, settings->R, settings->C, 0);
      if(result == player->id) return j;
      gamestate.board[k][j] = 0;
    }
  }
  if((rand() % 100) > 70){
    for(int i = 0; i < len; i++){
      int j = vacant[i];
      int k = height[i];
      gamestate.board[k][j] = player->id == 1? 2 : 1;
      int result = checkWin(gamestate.board, settings->R, settings->C, 1);
      int horizontalLose = player->id == 1 && result == 8 || player->id == 2 && result == 4;
      int verticalLose = player->id == 1 && result == 9 || player->id == 2 && result == 5;
      int diagonalLose = player->id == 1 && result == 10 || player->id == 2 && result == 6;
      if((horizontalLose || verticalLose || diagonalLose) && ((rand() % 100) > 75)) return j;
    }
  }
  return vacant[rand() % len];
}

int aiMoveMedium(const GameState *st, Player *player, Settings *settings){
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
    if(result == player->id) return j;
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
    if(horizontalLose || verticalLose || diagonalLose) return j;
    gamestate.board[k][j] = 0;
  }
  int worth[12] = {0};
  int meaningfull_j[12] = {0};
  int meaningfull_i[12] = {0};
  int lenMeaning = 0;
  for(int index = 0; index < len; index++){
    int free = 0, consecutive = 0;
    int j = vacant[index];
    int i = 0;
    while(i < settings->R && gamestate.board[i][j] == 0){free++; i++;}
    while(i < settings->R && gamestate.board[i][j] == 1){consecutive++; i++;}
    if(consecutive == 0) while(i < settings->R && gamestate.board[i][j] == 2){consecutive++; i++;}
    if(free + consecutive >= 4) {meaningfull_j[lenMeaning] = vacant[index]; meaningfull_i[lenMeaning++] = height[index];}
  }
  int maxWorth = 0;
  int maxWorthJ = -1;
  if(lenMeaning == 0) return vacant[(int)len/2];
  for(int index = 0; index < len; index++){
    int j = meaningfull_j[index];
    int i = meaningfull_i[index];
    if(i < settings->R - 1){
      worth[index] += gamestate.board[i+1][j] == 0? 1 : gamestate.board[i+1][j] == player->id ? 3 : 2;
      if(j < settings->C - 1) worth[index] += gamestate.board[i+1][j+1] == 0? 1 : gamestate.board[i+1][j+1] == player->id ? 3 : 2;
      if(j > 0) worth[index] += gamestate.board[i+1][j-1] == 0? 1 : gamestate.board[i+1][j-1] == player->id ? 3 : 2;
    }
    if(i > 0){
      worth[index] += gamestate.board[i-1][j] == 0? 1 : gamestate.board[i-1][j] == player->id ? 3 : 2;
      if(j < settings->C - 1) worth[index] += gamestate.board[i-1][j+1] == 0? 1 : gamestate.board[i-1][j+1] == player->id ? 3 : 2;
      if(j > 0) worth[index] += gamestate.board[i-1][j-1] == 0? 1 : gamestate.board[i-1][j-1] == player->id ? 3 : 2;
    }
    if(j < settings->C - 1) worth[index] += gamestate.board[i][j+1] == 0? 1 : gamestate.board[i][j+1] == player->id ? 3 : 2;
    if(j > 0) worth[index] += gamestate.board[i][j-1] == 0? 1 : gamestate.board[i][j-1] == player->id ? 3 : 2;
    if(worth[index] > maxWorth) {maxWorth = worth[index]; maxWorthJ = j;}
  }
  if(maxWorthJ == -1 || maxWorth <= 4) return meaningfull_j[(int)len/2];
  if(maxWorth <= 5 && (rand() % 100) > 50) return meaningfull_j[(int)len/2];
  return maxWorthJ;
}

int aiMoveHard(const GameState *st, Player *player, Settings *settings){
  // to write
  return 1;
}

int parseInt(char string[]);

int replayMove(const GameState *st, Player *player, Settings *settings){
  char line[104];
  // printf("LOG");
  while(settings->isReplayLoaded == 0){
    fgets(line, 104, settings->replayFilePtr);
    if(strcmp(line, "replay[\n") == 0){
      fgets(line, 104, settings->replayFilePtr);
      fgets(line, 104, settings->replayFilePtr);
      fgets(line, 104, settings->replayFilePtr);
      char *endptr;
      char id[104];
      fgets(id, 104, settings->replayFilePtr);
      long id_int = strtol(id, &endptr,10);
      long int id_final_int = id_int;
      if(settings->selectedReplayId == id_final_int){
        settings->isReplayLoaded = 1;
        break;
      }
    }
  }
  fgets(line, 104, settings->replayFilePtr);
  // printf("[LOG] LINE %s | LINE INT %d", line, parseInt(line));
  printf("Enter any character and press Enter to navigate forward:\n-> ");
  char ch;
  scanf(" %c", &ch);
  return parseInt(line);
}

int parseInt(char string[]){
  int a1 = string[0] - '0';
  if (string[1] != '\0' && (string[1] - '0') >= 0 && (string[1] - '0') <= 9){
    int a0 = string[1] - '0';
    return 10 * a1 + a0;
  }
  return a1;
}

int fileDrivenMove(const GameState *st, Player *player, Settings *settings){
  char string[4];
  fgets(string, 4, settings->inputFilePtr);
  return parseInt(string) - 1;
}

int main(){  
  srand(time(NULL));
  int R = 0, C = 0;
  char token;
  char token2;
  int gamemode, difficulty;
  FILE *fptr = NULL;
  FILE *replay = NULL;
  char addr[100];
  printf("====> Choose player 1's token:\n-> ");
  scanf(" %c", &token);
  printf("====> Choose player 2's token:\n-> ");
  scanf(" %c", &token2);
  printf("====> Game Modes\n1. Player VS Computer\n2. Player VS Player\n3. File Input Mode\n4. Replay Mode\n-> ");
  scanf("%d", &gamemode);
  gamemode--;
  while(gamemode == fileInputMode){
    printf("Please enter the address of the input file(maximum 100 characters) it must be a .txt file:\n-> ");
    scanf("%s", addr);
    fptr = fopen(addr, "r");
    if (fptr == NULL) printf("INVALID ADDRESS!\n");
    else break;
  }
  if(gamemode != replayMode){
    printf("====> Enter the dimensions of the board\n");
    while(C < 4 || C > 12){
      printf("Number of columns(must be between 4-12):\n-> ");
      scanf(" %d", &C);
    }
    while(R < 4 || R > 12){
      printf("Number of rows(must be between 4-12):\n-> ");
      scanf(" %d", &R);
    }
  }
  int selectedId = -1;
  if(gamemode == replayMode){
    FILE *ptr;
    ptr = fopen("replay.txt", "r");
    if(ptr == NULL){
      printf("You have no replays saved on this device. The gamemode will be changed to Player vs Computer.\n");
      gamemode = humanVsComputer;
    }
    else {
      char line[104];
      long int ids[100];
      int Rs[100], Cs[100];
      int count = 0;
      char id[104];
      while(fgets(line, 104, ptr)){
        if(strcmp(line, "replay[\n") == 0){
          fgets(line, 104, ptr);
          Rs[count] = parseInt(line);
          fgets(line, 104, ptr);
          Cs[count] = parseInt(line);
          fgets(line, 104, ptr);
          fgets(id, 104, ptr);
          char *endptr;
          long id_int = strtol(id, &endptr,10);
          ids[count] = id_int;
          printf("\t%d. %ld | %s", count + 1, ids[count], line);
          count++;
        }
      }
      printf("Choose a replay\n-> ");
      int select = -1;
      while(1){
        scanf(" %d", &select);
        if(select < 1 || select > count) printf("Invalid number. Please enter again:\n-> ");
        else break;
      }
      selectedId = ids[select - 1];
      R = Rs[select - 1];
      C = Cs[select - 1];
    }
    fclose(ptr);
    replay = fopen("replay.txt", "r");
  }
  if(gamemode == humanVsComputer){
    printf("====> Difficulty\n1. Easy\n2. Medium\n-> ");
    scanf("%d", &difficulty);
    difficulty--;
  }
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
  settings.difficulty = difficulty;
  settings.inputFilePtr = fptr;
  settings.replayFilePtr = replay;
  for(int i = 0; i < 150; i++) settings.moves[i] = -1;
  settings.movesLen = 0;
  if(gamemode == replayMode){
    settings.selectedReplayId = selectedId;
    settings.isReplayLoaded = 0;
  }

  Player player1, player2;
  player1.id = 1;
  player1.move = gamemode == fileInputMode? fileDrivenMove : gamemode == replayMode? replayMove : humanMove;
  player1.token = token;
  player2.id = 2;
  player2.move = gamemode == humanVsComputer
  ? difficulty == 0? aiMoveEasy : aiMoveMedium 
  : gamemode == fileInputMode
  ? fileDrivenMove
  : gamemode == replayMode? replayMove : humanMove;
  player2.token = token2;
  printBoard(gameState.board, R, C, player1.token, player2.token);
  engine(&gameState, onEnd, &settings, onContinue, &player1, &player2, onWrongColumn);
  return 0;
}