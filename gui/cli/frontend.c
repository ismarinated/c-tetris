/**
 * @file frontend.c
 * @brief Handles the visual part in console.
 */

#include "frontend.h"

WINDOW *create_newwin(int height, int width, int starty, int startx,
                      const char *text, int is_controls) {
  WINDOW *win = newwin(height, width, starty, startx);
  box(win, 0, 0);
  mvwprintw(win, 0, (width - strlen(text)) / 2, "%s", text);
  wrefresh(win);

  if (is_controls) print_controls(win);

  return win;
}

void init_colors() {
  init_pair(1, COLOR_RED, COLOR_RED);
  init_pair(2, COLOR_CYAN, COLOR_CYAN);
  init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(4, COLOR_WHITE, COLOR_WHITE);
  init_pair(5, COLOR_GREEN, COLOR_GREEN);
  init_pair(6, COLOR_BLUE, COLOR_BLUE);
  init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);
}

void print_controls(WINDOW *win) {
  int i = 1;

  mvwprintw(win, i++, 1, "Enter - start");
  mvwprintw(win, i++, 1, "q - quit");
  mvwprintw(win, i++, 1, "p - pause");
  i++;
  mvwprintw(win, i++, 1, "< - left");
  mvwprintw(win, i++, 1, "> - right");
  mvwprintw(win, i++, 1, "v - drop");
  mvwprintw(win, i++, 1, "r - rotate");

  wrefresh(win);
}

void print_field(WINDOW *win) {
  GameInfo_t gi = updateCurrentState();
  Figure_t *fig = init_figure();

  for (int i = 1; i <= HEIGHT; i++) {
    for (int j = 1; j <= WIDTH; j++) {
      if (!gi.field[i][j])
        mvwprintw(win, i, j * INDEX_W - 1, "..");
      else {
        wattron(win, COLOR_PAIR(gi.field[i][j]));
        mvwprintw(win, i, j * INDEX_W - 1, "##");
        wattroff(win, COLOR_PAIR(gi.field[i][j]));
      }
    }
  }

  if (fig->y != 1) {
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        if (fig->cur[i][j]) {
          wattron(win, COLOR_PAIR(fig->type));
          mvwprintw(win, fig->y + i - 1, (fig->x + j - 1) * INDEX_W - 1, "##");
          wattroff(win, COLOR_PAIR(fig->type));
        }
      }
    }
  }

  wrefresh(win);
}

void print_info(WINDOW *win) {
  GameInfo_t gi = updateCurrentState();

  if ((int)*init_state() != -1 && (int)*init_state() != GameOver) {
    int i = 1;
    mvwprintw(win, i++, 1, "High Score:");
    mvwprintw(win, i++, 3, "%d", gi.high_score);
    mvwprintw(win, i++, 1, "Score:");
    mvwprintw(win, i++, 3, "%d", gi.score);
    mvwprintw(win, i++, 1, "Level:");
    mvwprintw(win, i++, 3, "%d", gi.level);
    mvwprintw(win, i++, 1, "Next Figure:");

    for (int n = 0; n < SIZE; n++) {
      for (int m = 0; m < SIZE; m++) {
        if (gi.next[n][m] != 0) {
          wattron(win, COLOR_PAIR(init_figure()->next_type));
          mvwprintw(win, i + n, 3 + (m + 1) * INDEX_W - 1, "##");
          wattroff(win, COLOR_PAIR(init_figure()->next_type));
        } else
          mvwprintw(win, i + n, 3 + (m + 1) * INDEX_W - 1, "..");
      }
    }
  }

  wrefresh(win);
}

void get_action(bool *hold) {
  char ch = wgetch(stdscr);
  UserAction_t *act = init_act();
  State_t *state = init_state();

  switch (ch) {
    case '\n':
      *act = StartGame;
      if ((int)*state == -1) *state = Start;
      break;
    case 'q':
      *act = EndGame;
      break;
    case 'p':
      *act = Pause;
      break;
    case (char)KEY_LEFT:
      *act = LeftArrow;
      break;
    case (char)KEY_RIGHT:
      *act = RightArrow;
      break;
    case (char)KEY_DOWN:
      *act = DownArrow;
      *hold = true;
      break;
    case 'r':
      *act = Action;
      break;
  }
}