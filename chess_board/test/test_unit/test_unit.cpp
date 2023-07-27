#include <Arduino.h>
#include <Board.h>
#include <MoveSet.h>
#include "unity.h"

char *to_string(const char *description, int value)
{
  String timer_str(value);
  String description_str(description);
  timer_str = description_str + timer_str;
  char timer_c_str[description_str.length() + 12];
  timer_str.toCharArray(timer_c_str, 12 + description_str.length());
  return timer_c_str;
}
int test_for_correct_no_moves_full_board_starting_pos(void)
{

  Board board(true);
  MoveSet moves;
  board.generate_legal_moveset_for_color(white, moves);
  auto no_moves_white = moves.size;
  if (no_moves_white != 20)
    return 1;

  moves.clear();
  board.generate_legal_moveset_for_color(white, moves);
  auto no_moves_black = moves.size;

  if (no_moves_white != no_moves_black)
    return 1;
  return 0;
}

int test_for_correct_no_moves_empty_board(void)
{

  Board board;
  MoveSet moves;
  board.generate_legal_moveset_for_color(white, moves);
  auto no_moves_white = moves.size;
  if (no_moves_white == 0)
    return 0;
  return 1;
}

int test_for_correct_no_moves_pawn_starting_position(void)
{

  Board board;
  board.set_piece(6, 4, w_pawn);
  MoveSet moves;
  board.generate_legal_moveset_for_color(white, moves);

  auto no_moves_white = moves.size;

  if (2 != no_moves_white)
    return 1;

  moves.clear();
  board = Board();
  board.set_piece(5, 4, w_pawn);
  board.generate_legal_moveset_for_color(white, moves);

  no_moves_white = moves.size;
  if (1 != no_moves_white)
    return 1;
  moves.clear();
  board = Board();
  board.set_piece(1, 4, b_pawn);
  board.generate_legal_moveset_for_color(white, moves);

  no_moves_white = moves.size;
  if (2 != no_moves_white)
    return 1;

  moves.clear();
  board = Board();
  board.set_piece(2, 4, b_pawn);
  board.generate_legal_moveset_for_color(white, moves);

  no_moves_white = moves.size;
  if (1 != no_moves_white)
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
int test_correct_move_set_next(void)
{

  int8_t starting_pos[5]{3, 3, 9, 9, 9};
  int8_t move[5]{2, 4, 8, 16, 32};
  MoveSet moves;
  for (int i = 0; i < 5; i++)
  {
    moves.add_move(move[i]);
  }
  moves.add_starting_position(2, 3);
  moves.add_starting_position(3, 9);

  int8_t from, to;

  for (int i = 0; i < 5; i++)

  {
    moves.next(from, to);
    {
      String timer_str = String("iter:") + String(i) + String("exp:") + String(starting_pos[i]) + String("got:") + String(from);
      char timer_c_str[30];
      timer_str.toCharArray(timer_c_str, 30);

      UNITY_TEST_ASSERT(from == starting_pos[i], __LINE__, timer_c_str);
    }
    {
      String timer_str = String("iter:") + String(i) + String("exp:") + String(move[i]) + String("got:") + String(to);
      char timer_c_str[30];
      timer_str.toCharArray(timer_c_str, 30);

      UNITY_TEST_ASSERT(to == move[i], __LINE__, timer_c_str);
    }
  }
  return 0;
}
int test_correct_move_set_get(void)
{

  int8_t starting_pos[5]{3, 3, 9, 9, 9};
  int8_t move[5]{2, 4, 8, 16, 32};
  MoveSet moves;
  for (int i = 0; i < 5; i++)
  {
    moves.add_move(move[i]);
  }
  moves.add_starting_position(2, 3);
  moves.add_starting_position(3, 9);

  int8_t from, to;

  for (int i = 0; i < 5; i++)

  {
    moves.get(from, to, i);
    {
      String timer_str = String("iter:") + String(i) + String("exp:") + String(starting_pos[i]) + String("got:") + String(from);
      char timer_c_str[30];
      timer_str.toCharArray(timer_c_str, 30);

      UNITY_TEST_ASSERT(from == starting_pos[i], __LINE__, timer_c_str);
    }
    {
      String timer_str = String("iter:") + String(i) + String("exp:") + String(move[i]) + String("got:") + String(to);
      char timer_c_str[30];
      timer_str.toCharArray(timer_c_str, 30);

      UNITY_TEST_ASSERT(to == move[i], __LINE__, timer_c_str);
    }
  }
  return 0;
}
int test_generate_killing_moveset(void)
{

  MoveSet moves;
  Board board(true);
  board.generate_killing_moveset_for_color(white, moves);
  board.generate_killing_moveset_for_color(black, moves);

  String info_str(moves.size);
  char info_c_str[30];
  info_str.toCharArray(info_c_str, 30);
  UNITY_TEST_ASSERT(moves.size == 0, __LINE__, info_c_str);

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
  RUN_TEST(test_correct_move_set_next);
  RUN_TEST(test_correct_move_set_get);
  RUN_TEST(test_generate_killing_moveset);

  return UNITY_END();
}

void setup()
{
  delay(2000);
  runUnityTests();
}
void loop() {}