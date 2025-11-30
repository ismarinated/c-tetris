#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <string.h>

#include "../../brick_game/tetris/backend.h"

#define INDEX_W 2

#define GAME_H (HEIGHT + 2)
#define GAME_W (WIDTH * INDEX_W + 2)

#define INFO_W (8 * INDEX_W)
#define CONTROLS_W (8 * INDEX_W)
#define CONTROLS_H 10

WINDOW *create_newwin(int height, int width, int starty, int startx,
                      const char *text, int is_controls);
void init_colors();
void print_controls(WINDOW *win);
void print_field(WINDOW *win);
void print_info(WINDOW *win);
void get_action(bool *hold);

#endif