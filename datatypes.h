#include <stdio.h>

typedef struct GameState GameState;

typedef int (*MoveFn)(const GameState *st, void *ctx);

typedef struct {
  MoveFn move;
  void *ctx;
  char token;
} PLayer;

typedef struct {
  int computerVsComputer;
  int humanVsComputer;
  int fileInputMode;
} GameMode;

typedef struct {
  int easy;
  int normal;
  int hard;
} Difficulty;

