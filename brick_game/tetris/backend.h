#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>
#include <stdio.h>   // remove
#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()

#define HEIGHT 20
#define WIDTH 10

#define SIZE 4

#define M_HEIGHT (HEIGHT + 2)
#define M_WIDTH (WIDTH + 2)

#define TOP 1
#define MIDDLE (M_WIDTH / 2)

#define MAX_LEVEL 10

#define GET_SPEED(index)                                                     \
  ({                                                                         \
    static int speed[] = {800, 720, 630, 550, 470, 380, 300, 220, 130, 100}; \
    speed[index];                                                            \
  })

#define GET_SCORE(rows)                         \
  ({                                            \
    static int score[] = {100, 300, 700, 1500}; \
    score[rows - 1];                            \
  })

// Start, Spawn, Moving, Shifting, Attaching, GameOver
typedef enum { Start, Spawn, Moving, Shifting, Attaching, GameOver } State_t;

// StartGame, Pause, EndGame, LeftArrow, RightArrow, DownArrow, UpArrow, Action
typedef enum {
  StartGame,
  Pause,
  EndGame,
  LeftArrow,
  RightArrow,
  DownArrow,
  UpArrow,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct {
  int **cur;
  int **next;
  int x;
  int y;
  int type;
  int next_type;
  int next_rot;
} Figure_t;

GameInfo_t *init_game_info();
GameInfo_t updateCurrentState();
State_t *init_state();
UserAction_t *init_act();
int is_collision();
void userInput(UserAction_t action, bool hold);
void scoring();
void del_row(int row);
void moving(clock_t *start);
void spawning();
void shifting(bool hold);
void attaching();
void free_game();

Figure_t *init_figure();
void fill_figure();
void set_to_start();
void rotate();
void move_right();
void move_left();
void move_down();

int **create_matrix(int n, int m);
void copy_matrix(int **src, int **dest, int n, int m);
void free_matrix(int **matrix, int n);
void zero_matrix(int **matrix, int n, int m);
int randomizer(int min, int max);
void shift_rows(int **matrix, int n, int m);
void shift_columns(int **matrix, int n, int m);
int get_high_score();
void set_high_score(int score);

#endif