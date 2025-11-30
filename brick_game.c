/**
 * @file brick_game.c
 * @brief Entry point.
 */

#include "brick_game.h"

int main() {
  initscr();

  refresh();  // would not work (displ. boxes) w/out

  keypad(stdscr, TRUE);   // using arrows and other spec. keys
  nodelay(stdscr, TRUE);  // for non-blocking input from wgetch()
  cbreak();               // input handling w/out Enter
  curs_set(0);            // hides cursor
  noecho();               // disabling console input

  main_loop();

  endwin();

  return 0;
}

void main_loop() {
  WINDOW *field = create_newwin(GAME_H, GAME_W, 0, CONTROLS_W, "TETRIS", 0);
  WINDOW *controls = create_newwin(CONTROLS_H, CONTROLS_W, 0, 0, "CONTROLS", 1);
  WINDOW *info =
      create_newwin(GAME_H, INFO_W, 0, CONTROLS_W + GAME_W, "INFO", 0);

  start_color();
  init_colors();

  UserAction_t *act = init_act();
  clock_t start = clock();

  while ((int)*init_state() != GameOver) {
    bool hold = false;

    get_action(&hold);
    userInput(*act, hold);
    moving(&start);
    *act = -1;

    print_field(field);
    print_info(info);
  }

  set_high_score((int)init_game_info()->high_score);
  free_game();

  delwin(field);
  delwin(controls);
  delwin(info);
}