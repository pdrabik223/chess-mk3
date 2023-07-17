#include <Arduino.h>
#include <Board.h>
#include "unity.h"

int test_for_correct_no_moves_full_board_starting_pos(void)
{

  Board board(true);
  int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
  int8_t starting_positions[MAX_NO_MOVES_IN_EACH_BOARD];
  if (20 != board.generate_legal_moveset_for_color(white, starting_positions, moves))
    return 1;
  if (board.generate_legal_moveset_for_color(black, starting_positions, moves) != board.generate_legal_moveset_for_color(white, starting_positions, moves))
    return 1;
  return 0;
}

int test_for_correct_no_moves_empty_board(void)
{

  Board board;
  int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
  int8_t starting_positions[MAX_NO_MOVES_IN_EACH_BOARD];
  if (0 == board.generate_legal_moveset_for_color(white, starting_positions, moves))
    return 0;
  return 1;
}

int test_for_correct_no_moves_pawn_starting_position(void)
{

  Board board;
  board.set_piece(6, 4, w_pawn);
  int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
  int8_t starting_positions[MAX_NO_MOVES_IN_EACH_BOARD];
  if (2 != board.generate_legal_moveset_for_color(white, starting_positions, moves))
    return 1;

  board = Board();
  board.set_piece(5, 4, w_pawn);
  if (1 != board.generate_legal_moveset_for_color(white, starting_positions, moves))
    return 1;

  board = Board();
  board.set_piece(1, 4, b_pawn);
  if (2 != board.generate_legal_moveset_for_color(black, starting_positions, moves))
    return 1;

  board = Board();
  board.set_piece(2, 4, b_pawn);
  if (1 != board.generate_legal_moveset_for_color(black, starting_positions, moves))
    return 1;

  return 0;
}

int test_move_black_pawn_upgrade(void)
{
  Board board;
  board.set_piece(6, 4, b_pawn);
  board.move(6 * 8, 4);
  Board board2;
  board2.set_piece(7, 4, b_queen);
  if (board != board2)
    return 1;

  return 0;
}
int test_move_white_pawn_upgrade(void)
{
  Board board;
  board.set_piece(1, 4, w_pawn);
  board.move(12, 4);
  Board board2;
  board2.set_piece(0, 4, w_queen);
  if (board != board2)
    return 1;

  return 0;
}

int test_if_starting_position_is_equal(void)
{
  Board board(true);
  if (board.estimate_position() == 0)
    return 0;
  return 1;
}

int performance_test_generate_legal_moveset_w_pawn(void)
{
  int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
  uint16_t no_test_cases = 100;
  unsigned long avg = 0;
  for (uint16_t i = 0; i < no_test_cases; i++)
  {
    Board board;
    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = b_pawn;

    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = w_pawn;

    int pawn_pos = random(0, 64);
    board.data[pawn_pos] = w_pawn;

    auto timer = micros();
    board.generate_legal_moveset_pawn(pawn_pos, moves);
    avg += micros() - timer;
  }
  float f_avg = avg / no_test_cases;
  String timer_str(f_avg);
  String description_str("execution time [microseconds]:");
  timer_str = description_str + timer_str;
  char timer_c_str[31 + 12];
  timer_str.toCharArray(timer_c_str, 12 + 31);
  UNITY_TEST_ASSERT(f_avg <= 25.00, __LINE__, timer_c_str);
  return 0;
}
int performance_test_generate_legal_moveset_b_pawn(void)
{
  int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
  uint16_t no_test_cases = 100;

  unsigned long avg = 0;
  for (uint16_t i = 0; i < no_test_cases; i++)
  {
    Board board;
    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = w_pawn;

    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = b_pawn;

    int pawn_pos = random(0, 64);
    board.data[pawn_pos] = b_pawn;

    auto timer = micros();
    board.generate_legal_moveset_pawn(pawn_pos, moves);
    avg += micros() - timer;
  }
  float f_avg = avg / no_test_cases;
  String timer_str(f_avg);
  String description_str("execution time [microseconds]:");
  timer_str = description_str + timer_str;
  char timer_c_str[31 + 12];
  timer_str.toCharArray(timer_c_str, 12 + 31);
  UNITY_TEST_ASSERT(f_avg <= 25.00, __LINE__, timer_c_str);
  return 0;
}
int performance_test_generate_legal_moveset_w_knight(void)
{
  int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
  uint16_t no_test_cases = 100;
  unsigned long avg = 0;
  for (uint16_t i = 0; i < no_test_cases; i++)
  {
    Board board;
    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = b_pawn;

    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = w_pawn;

    int pawn_pos = random(0, 64);
    board.data[pawn_pos] = w_knight;

    auto timer = micros();
    board.generate_legal_moveset_knight(pawn_pos, moves);
    avg += micros() - timer;
  }
  float f_avg = avg / no_test_cases;
  String timer_str(f_avg);
  String description_str("execution time [microseconds]:");
  timer_str = description_str + timer_str;
  char timer_c_str[31 + 12];
  timer_str.toCharArray(timer_c_str, 12 + 31);
  UNITY_TEST_ASSERT(f_avg <= 36.00, __LINE__, timer_c_str);
  return 0;
}
int performance_test_generate_legal_moveset_b_knight(void)
{
  int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
  uint16_t no_test_cases = 100;

  unsigned long avg = 0;
  for (uint16_t i = 0; i < no_test_cases; i++)
  {
    Board board;
    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = w_pawn;

    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = b_pawn;

    int pawn_pos = random(0, 64);
    board.data[pawn_pos] = b_knight;

    auto timer = micros();
    board.generate_legal_moveset_knight(pawn_pos, moves);
    avg += micros() - timer;
  }
  float f_avg = avg / no_test_cases;
  String timer_str(f_avg);
  String description_str("execution time [microseconds]:");
  timer_str = description_str + timer_str;
  char timer_c_str[31 + 12];
  timer_str.toCharArray(timer_c_str, 12 + 31);
  UNITY_TEST_ASSERT(f_avg <= 36.00, __LINE__, timer_c_str);
  return 0;
}

int performance_test_generate_legal_moveset_w_bishop(void)
{
  int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
  uint16_t no_test_cases = 100;
  unsigned long avg = 0;
  for (uint16_t i = 0; i < no_test_cases; i++)
  {
    Board board;
    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = b_pawn;

    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = w_pawn;

    int pawn_pos = random(0, 64);
    board.data[pawn_pos] = w_bishop;

    auto timer = micros();
    board.generate_legal_moveset_bishop(pawn_pos, moves);
    avg += micros() - timer;
  }
  float f_avg = avg / no_test_cases;
  String timer_str(f_avg);
  String description_str("execution time [microseconds]:");
  timer_str = description_str + timer_str;
  char timer_c_str[31 + 12];
  timer_str.toCharArray(timer_c_str, 12 + 31);
  UNITY_TEST_ASSERT(f_avg <= 39.00, __LINE__, timer_c_str);
  return 0;
}
int performance_test_generate_legal_moveset_b_bishop(void)
{
  int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
  uint16_t no_test_cases = 100;

  unsigned long avg = 0;
  for (uint16_t i = 0; i < no_test_cases; i++)
  {
    Board board;
    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = w_pawn;

    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = b_pawn;

    int pawn_pos = random(0, 64);
    board.data[pawn_pos] = b_bishop;

    auto timer = micros();
    board.generate_legal_moveset_bishop(pawn_pos, moves);
    avg += micros() - timer;
  }
  float f_avg = avg / no_test_cases;
  String timer_str(f_avg);
  String description_str("execution time [microseconds]:");
  timer_str = description_str + timer_str;
  char timer_c_str[31 + 12];
  timer_str.toCharArray(timer_c_str, 12 + 31);
  UNITY_TEST_ASSERT(f_avg <= 39.00, __LINE__, timer_c_str);
  return 0;
}

int performance_test_generate_legal_moveset_w_queen(void)
{
  int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
  uint16_t no_test_cases = 100;
  unsigned long avg = 0;
  for (uint16_t i = 0; i < no_test_cases; i++)
  {
    Board board;
    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = b_pawn;

    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = w_pawn;

    int pawn_pos = random(0, 64);
    board.data[pawn_pos] = w_queen;

    auto timer = micros();
    board.generate_legal_moveset_queen(pawn_pos, moves);
    avg += micros() - timer;
  }
  float f_avg = avg / no_test_cases;
  String timer_str(f_avg);
  String description_str("execution time [microseconds]:");
  timer_str = description_str + timer_str;
  char timer_c_str[31 + 12];
  timer_str.toCharArray(timer_c_str, 12 + 31);
  UNITY_TEST_ASSERT(f_avg <= 75.00, __LINE__, timer_c_str);
  return 0;
}
int performance_test_generate_legal_moveset_b_queen(void)
{
  int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
  uint16_t no_test_cases = 100;

  unsigned long avg = 0;
  for (uint16_t i = 0; i < no_test_cases; i++)
  {
    Board board;
    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = w_pawn;

    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = b_pawn;

    int pawn_pos = random(0, 64);
    board.data[pawn_pos] = b_queen;

    auto timer = micros();
    board.generate_legal_moveset_queen(pawn_pos, moves);
    avg += micros() - timer;
  }
  float f_avg = avg / no_test_cases;
  String timer_str(f_avg);
  String description_str("execution time [microseconds]:");
  timer_str = description_str + timer_str;
  char timer_c_str[31 + 12];
  timer_str.toCharArray(timer_c_str, 12 + 31);
  UNITY_TEST_ASSERT(f_avg <= 75.00, __LINE__, timer_c_str);
  return 0;
}

int performance_test_generate_legal_moveset_w_king(void)
{
  int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
  uint16_t no_test_cases = 100;
  unsigned long avg = 0;
  for (uint16_t i = 0; i < no_test_cases; i++)
  {
    Board board;
    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = b_pawn;

    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = w_pawn;

    int pawn_pos = random(0, 64);
    board.data[pawn_pos] = w_king;

    auto timer = micros();
    board.generate_legal_moveset_king(pawn_pos, moves);
    avg += micros() - timer;
  }
  float f_avg = avg / no_test_cases;
  String timer_str(f_avg);
  String description_str("execution time [microseconds]:");
  timer_str = description_str + timer_str;
  char timer_c_str[31 + 12];
  timer_str.toCharArray(timer_c_str, 12 + 31);
  UNITY_TEST_ASSERT(f_avg <= 37.00, __LINE__, timer_c_str);
  return 0;
}

int performance_test_generate_legal_moveset_b_king(void)
{
  int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
  uint16_t no_test_cases = 100;

  unsigned long avg = 0;
  for (uint16_t i = 0; i < no_test_cases; i++)
  {
    Board board;
    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = w_pawn;

    for (int j = 0; j < 16; j++)
      board.data[random(0, 64)] = b_pawn;

    int pawn_pos = random(0, 64);
    board.data[pawn_pos] = b_king;

    auto timer = micros();
    board.generate_legal_moveset_king(pawn_pos, moves);
    avg += micros() - timer;
  }
  float f_avg = avg / no_test_cases;
  String timer_str(f_avg);
  String description_str("execution time [microseconds]:");
  timer_str = description_str + timer_str;
  char timer_c_str[31 + 12];
  timer_str.toCharArray(timer_c_str, 12 + 31);
  UNITY_TEST_ASSERT(f_avg <= 37.00, __LINE__, timer_c_str);
  return 0;
}

int runUnityTests(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_for_correct_no_moves_full_board_starting_pos);
  RUN_TEST(test_for_correct_no_moves_empty_board);
  RUN_TEST(test_for_correct_no_moves_pawn_starting_position);
  RUN_TEST(test_move_black_pawn_upgrade);
  RUN_TEST(test_move_white_pawn_upgrade);
  RUN_TEST(test_if_starting_position_is_equal);

  // RUN_TEST(performance_test_generate_legal_moveset_w_pawn);
  // RUN_TEST(performance_test_generate_legal_moveset_b_pawn);

  // RUN_TEST(performance_test_generate_legal_moveset_w_knight);
  // RUN_TEST(performance_test_generate_legal_moveset_b_knight);

  // RUN_TEST(performance_test_generate_legal_moveset_w_bishop);
  // RUN_TEST(performance_test_generate_legal_moveset_b_bishop);

  // RUN_TEST(performance_test_generate_legal_moveset_w_queen);
  // RUN_TEST(performance_test_generate_legal_moveset_b_queen);

  // RUN_TEST(performance_test_generate_legal_moveset_w_king);
  // RUN_TEST(performance_test_generate_legal_moveset_b_king);

  return UNITY_END();
}

void setup()
{
  delay(2000);
  runUnityTests();
}
void loop() {}