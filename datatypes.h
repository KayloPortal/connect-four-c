#include <stdio.h>

typedef struct {
  int board[12][12];
} GameState;

typedef enum {
  humanVsComputer,
  humanVsHuman,
  fileInputMode,
  replayMode
} GameMode;

typedef enum {
  easy,
  medium,
  hard
} Difficulty;

typedef struct {
  Difficulty difficulty;
  GameMode gamemode;
  int R;
  int C;
  FILE *inputFilePtr;
  FILE *replayFilePtr;
  int moves[150];
  int movesLen;
  long int selectedReplayId;
  int isReplayLoaded;
} Settings;

typedef struct Player Player;

typedef int (*MoveFn)(const GameState *st, Player *player, Settings *settings);
struct Player {
  MoveFn move;
  void *ctx;
  char token;
  int id; // is 1 for player one, is 2 for player two.
};

typedef int (*BoardExportFn)(const GameState *st);

typedef void (*OnContinue)(const GameState *st,
Settings *settings, Player *player1, Player *player2);

typedef int (*OnWrongColumn)(int isFull, int isInvalid);
typedef void (*OnEnd)(const GameState *st, int isDraw, Player *winner,
Settings *settings, Player *loser);