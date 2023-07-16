#include <Arduino.h>
#include <Board.h>
#include "LedStrip.h"
#include "unity.h"

int test_for_correct_no_moves_full_board_starting_pos(void)
{

  Board board(true);
  int8_t moves[MAX_NO_MOVES_IN_EACH_BOARD];
  int8_t starting_positions[MAX_NO_MOVES_IN_EACH_BOARD];
  if (20 == board.generate_legal_moveset_for_color(white, starting_positions, moves))
    return 0;
  return 1;
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

int runUnityTests(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_for_correct_no_moves_full_board_starting_pos);
  RUN_TEST(test_for_correct_no_moves_empty_board);
  RUN_TEST(test_for_correct_no_moves_pawn_starting_position);
  RUN_TEST(test_move_black_pawn_upgrade);
  RUN_TEST(test_move_white_pawn_upgrade);
  return UNITY_END();
}
void setup()
{
  delay(2000);
  runUnityTests();
}
void loop() {}