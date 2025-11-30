#include "tests.h"

START_TEST(test_init_figure) {
  Figure_t *fig = init_figure();

  int next_type = fig->next_type;
  int next_rot = fig->next_rot;

  ck_assert_int_eq(fig->type, 0);
  ck_assert_int_eq(fig->x, MIDDLE);
  ck_assert_int_eq(fig->y, TOP);
  ck_assert_int_eq(fig->next_type, next_type);
  ck_assert_int_eq(fig->next_rot, next_rot);
  ck_assert_ptr_nonnull(fig->cur);
  ck_assert_ptr_nonnull(fig->next);
}

START_TEST(test_fill_one) {
  Figure_t *fig = init_figure();

  fig->next_type = 1;
  fig->next_rot = 0;
  fill_figure();

  ck_assert_int_eq(fig->next[0][0], 1);
  ck_assert_int_eq(fig->next[0][1], 1);
  ck_assert_int_eq(fig->next[0][2], 1);
  ck_assert_int_eq(fig->next[0][3], 1);
}

START_TEST(test_fill_two) {
  Figure_t *fig = init_figure();

  fig->next_type = 2;
  fig->next_rot = 0;
  fill_figure();

  ck_assert_int_eq(fig->next[0][0], 2);
  ck_assert_int_eq(fig->next[0][1], 2);
  ck_assert_int_eq(fig->next[1][0], 2);
  ck_assert_int_eq(fig->next[1][1], 2);
}

START_TEST(test_fill_three) {
  Figure_t *fig = init_figure();

  fig->next_type = 3;
  fig->next_rot = 0;
  fill_figure();

  ck_assert_int_eq(fig->next[0][0], 3);
  ck_assert_int_eq(fig->next[0][1], 3);
  ck_assert_int_eq(fig->next[1][1], 3);
  ck_assert_int_eq(fig->next[1][2], 3);
}

START_TEST(test_fill_four) {
  Figure_t *fig = init_figure();

  fig->next_type = 4;
  fig->next_rot = 0;
  fill_figure();

  ck_assert_int_eq(fig->next[0][0], 4);
  ck_assert_int_eq(fig->next[1][0], 4);
  ck_assert_int_eq(fig->next[2][0], 4);
  ck_assert_int_eq(fig->next[2][1], 4);
}

START_TEST(test_fill_five) {
  Figure_t *fig = init_figure();

  fig->next_type = 5;
  fig->next_rot = 0;
  fill_figure();

  ck_assert_int_eq(fig->next[0][0], 5);
  ck_assert_int_eq(fig->next[0][1], 5);
  ck_assert_int_eq(fig->next[0][2], 5);
  ck_assert_int_eq(fig->next[1][1], 5);
}

START_TEST(test_fill_six) {
  Figure_t *fig = init_figure();

  fig->next_type = 6;
  fig->next_rot = 0;
  fill_figure();

  ck_assert_int_eq(fig->next[0][1], 6);
  ck_assert_int_eq(fig->next[1][1], 6);
  ck_assert_int_eq(fig->next[2][1], 6);
  ck_assert_int_eq(fig->next[2][0], 6);
}

START_TEST(test_fill_seven) {
  Figure_t *fig = init_figure();

  fig->next_type = 7;
  fig->next_rot = 0;
  fill_figure();

  ck_assert_int_eq(fig->next[0][1], 7);
  ck_assert_int_eq(fig->next[0][2], 7);
  ck_assert_int_eq(fig->next[1][0], 7);
  ck_assert_int_eq(fig->next[1][1], 7);
}

START_TEST(test_init_game_info) {
  GameInfo_t *gi = init_game_info();

  ck_assert_int_eq(gi->level, 0);
  ck_assert_int_eq(gi->score, 0);
  ck_assert_int_eq(gi->high_score, get_high_score());
  ck_assert_int_eq(gi->pause, 0);
  ck_assert_int_eq(gi->speed, GET_SPEED(gi->level));
  ck_assert_ptr_nonnull(gi->field);
  ck_assert_ptr_nonnull(gi->next);
}

START_TEST(test_init_state) {
  State_t *state = init_state();

  ck_assert_int_eq((int)*state, -1);
}

START_TEST(test_updateCurrentState) {
  GameInfo_t gi = updateCurrentState();

  ck_assert_int_eq(gi.level, 0);
  ck_assert_int_eq(gi.score, 0);
  ck_assert_int_eq(gi.high_score, get_high_score());
  ck_assert_int_eq(gi.pause, 0);
  ck_assert_int_eq(gi.speed, GET_SPEED(gi.level));
  ck_assert_ptr_nonnull(gi.field);
  ck_assert_ptr_nonnull(gi.next);
}

START_TEST(test_init_user_act) {
  UserAction_t *act = init_act();

  ck_assert_int_eq((int)*act, -1);
}

START_TEST(test_userInput_spawning) {
  GameInfo_t *gi = init_game_info();
  State_t *state = init_state();
  UserAction_t *act = init_act();

  *state = Start;
  *act = StartGame;
  gi->level = 0;
  gi->pause = 0;
  userInput(*act, 0);
  ck_assert_int_eq((int)*state, (int)Spawn);
  userInput(*act, 0);

  Figure_t *fig = init_figure();

  ck_assert_int_eq(fig->x, MIDDLE);
  ck_assert_int_eq(fig->y, TOP);
}

START_TEST(test_userInput_shifting) {
  GameInfo_t *gi = init_game_info();
  State_t *state = init_state();
  UserAction_t *act = init_act();

  *state = Start;
  *act = StartGame;
  userInput(*act, 0);
  ck_assert_int_eq((int)*state, (int)Spawn);

  Figure_t *fig = init_figure();
  fig->cur = fig->next;
  fig->x = 5;
  fig->y = 14;

  *state = Shifting;
  *act = LeftArrow;
  userInput(*act, 0);
  ck_assert_int_eq(fig->x, 4);

  *act = RightArrow;
  userInput(*act, 0);
  ck_assert_int_eq(fig->x, 5);

  *act = DownArrow;
  userInput(*act, 1);
  int y = fig->y;
  ck_assert_int_eq(fig->y, y);

  *state = Spawn;
  *act = LeftArrow;
  gi->level = 10;
  userInput(*act, 0);
  ck_assert_int_eq((int)*state, (int)GameOver);

  *state = Attaching;
  gi->level = 0;
  userInput(*act, 0);
  y = gi->field[fig->y][fig->x];
  ck_assert_int_eq(gi->field[fig->y][fig->x], y);
}

START_TEST(test_userInput_pause) {
  GameInfo_t *gi = init_game_info();
  State_t *state = init_state();
  UserAction_t *act = init_act();

  *act = Pause;
  userInput(*act, 0);
  ck_assert_int_eq(gi->pause, 1);

  *act = Pause;
  userInput(*act, 0);
  ck_assert_int_eq(gi->pause, 0);

  *act = EndGame;
  userInput(*act, 0);
  ck_assert_int_eq((int)*state, (int)GameOver);
}

START_TEST(test_scoring) {
  GameInfo_t *gi = init_game_info();
  zero_matrix(gi->field, M_HEIGHT, M_WIDTH);

  for (int j = 1; j <= WIDTH; j++) gi->field[4][j] = 1;

  scoring();

  for (int j = 1; j <= WIDTH; j++) ck_assert_int_eq(gi->field[4][j], 0);
}

START_TEST(test_moving) {
  Figure_t *fig = init_figure();
  State_t *state = init_state();

  *state = Moving;
  int y = fig->y;
  clock_t start = clock();

  moving(&start);

  ck_assert_int_eq(fig->y, y);
}

Suite *test_suite(void) {
  Suite *s = suite_create("brick_game");
  TCase *tc = tcase_create("brick_game_tc");

  tcase_add_test(tc, test_init_figure);
  tcase_add_test(tc, test_fill_one);
  tcase_add_test(tc, test_fill_two);
  tcase_add_test(tc, test_fill_three);
  tcase_add_test(tc, test_fill_four);
  tcase_add_test(tc, test_fill_five);
  tcase_add_test(tc, test_fill_six);
  tcase_add_test(tc, test_fill_seven);

  tcase_add_test(tc, test_init_game_info);
  tcase_add_test(tc, test_init_state);
  tcase_add_test(tc, test_updateCurrentState);
  tcase_add_test(tc, test_init_user_act);
  tcase_add_test(tc, test_userInput_spawning);
  tcase_add_test(tc, test_userInput_shifting);
  tcase_add_test(tc, test_userInput_pause);
  tcase_add_test(tc, test_scoring);
  tcase_add_test(tc, test_moving);

  suite_add_tcase(s, tc);

  return s;
}

int main() {
  Suite *s = test_suite();
  SRunner *sr = srunner_create(s);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  srunner_free(sr);

  return 0;
}