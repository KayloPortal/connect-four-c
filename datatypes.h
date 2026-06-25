#include <stdio.h>

typedef struct {
  int board[12][12];
} GameState;

typedef enum {
  humanVsHuman,
  humanVsComputer,
  fileInputMode,
} GameMode;

typedef enum {
  easy,
  normal,
  hard
} Difficulty;

typedef struct {
  Difficulty difficulty;
  GameMode gamemode;
  int R;
  int C;
} Settings;

typedef struct Player Player;

typedef int (*MoveFn)(const GameState *st, Player *player);
struct Player {
  MoveFn move;
  void *ctx;
  char token;
  int id; // is 1 for player one, is 2 for player two.
};

typedef int (*BoardExportFn)(const GameState *st);

typedef void (*OnContinue)(const GameState *st,
Settings *settings);

typedef int (*OnWrongColumn)(int isFull, int isInvalid);

typedef void (*OnEnd)(const GameState *st, Player *winner,
Settings *settings);