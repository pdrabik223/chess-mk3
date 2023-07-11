#include <Arduino.h>
#include <Board.h>
#include "LedStrip.h"
// void convert_int_array_to_char(int len, int *int_array, char *string)
// {
//   for (int i = 0; i < len; i++)
//   {
//     int x = int_array[i] / 8;
//     int y = int_array[i] % 8;

//     string[i * 2] = char('0' + x);
//     string[i * 2 + 1] = char('0' + y);
//   }
// }

// // char str_representation_of_a_board[64];
// // int pawn_moves[64];
// // char pawn_moves_str[128];
// // Board board(true);

// void move_over_board_and_print_info_about_pieces()
// {

//   for (int pos = 0; pos < 64; pos++)
//   {

//     for (int i = 0; i < 128; i++)
//       pawn_moves_str[i] = '-';

//     int no_legal_moves = 0;

//     if (board.data[pos] == b_pawn || board.data[pos] == w_pawn)
//     {
//       no_legal_moves = board.generate_legal_moveset_pawn(pos, pawn_moves);
//       convert_int_array_to_char(no_legal_moves, pawn_moves, pawn_moves_str);
//     }
//     if (board.data[pos] == b_knight || board.data[pos] == w_knight)
//     {
//       no_legal_moves = board.generate_legal_moveset_knight(pos, pawn_moves);
//       convert_int_array_to_char(no_legal_moves, pawn_moves, pawn_moves_str);
//     }
//     if (board.data[pos] == b_king || board.data[pos] == w_king)
//     {
//       no_legal_moves = board.generate_legal_moveset_king(pos, pawn_moves);
//       convert_int_array_to_char(no_legal_moves, pawn_moves, pawn_moves_str);
//     }
//     if (board.data[pos] == b_rook || board.data[pos] == w_rook)
//     {
//       no_legal_moves = board.generate_legal_moveset_rook(pos, pawn_moves);
//       convert_int_array_to_char(no_legal_moves, pawn_moves, pawn_moves_str);
//     }
//     if (board.data[pos] == b_bishop || board.data[pos] == b_bishop)
//     {
//       no_legal_moves = board.generate_legal_moveset_bishop(pos, pawn_moves);
//       convert_int_array_to_char(no_legal_moves, pawn_moves, pawn_moves_str);
//     }
//     if (board.data[pos] == b_queen || board.data[pos] == b_queen)
//     {
//       no_legal_moves = board.generate_legal_moveset_queen(pos, pawn_moves);
//       convert_int_array_to_char(no_legal_moves, pawn_moves, pawn_moves_str);
//     }
//     Serial.println("pos x:");
//     Serial.println(int(pos / 8));
//     Serial.println("pos y:");
//     Serial.println(int(pos % 8));
//     Serial.println("chess piece on pos:");
//     Serial.println(symbol_encoding[board.data[pos]]);
//     Serial.println("no_legal_moves:");
//     Serial.println(no_legal_moves);
//     Serial.println("pawn_moves_str:");
//     Serial.println(pawn_moves_str);
//     Serial.println("estimation:");
//     Serial.println(board.estimate_position());
//     delay(1000);
//   }
// }
// void read_board_from_serial(Board &board)
// {

//   String val = Serial.readStringUntil('\n');
//   if (val.length() == 64)
//   {
//     board.from_string(val);
//   }
// }

// void all_possible_positions()
// {

//   // if (Serial.available() > 0)
//   // {
//   Serial.println("reading data:");
//   if (Serial.available() > 0)
//   {
//     read_board_from_serial(board);
//     board.to_string(str_representation_of_a_board);
//     Serial.println("board:");
//     Serial.println(str_representation_of_a_board);

//     int moves[256];
//     int starting_positions[256];

//     // int no_moves = board.generate_legal_moveset_for_color(white, starting_positions, moves);

//     // char starting_positions_str[no_moves];
//     char moves_str[1];

//     // for (int i = 0; i < no_moves; i++)
//     // {
//     //   starting_positions_str[i] = (char)starting_positions[i];
//     //   moves_str[i] = (char)moves[i];
//     // }

//     Serial.println("moves:" + String(0));
//     // String temp = String(32);
//     // temp.toCharArray(moves_str, 1);
//     Serial.println(char(32));
//     // Serial.println(starting_positions_str);
//   }
// }

void generate_test_cases(int no_of_test)
{
  char str_representation_of_a_board[65];
  Serial.println(":test_case:");
  Serial.println(no_of_test);

  Board board(true);

  // generate random position
  board.data[random(0, 64)] = w_pawn;
  board.data[random(0, 64)] = w_pawn;
  board.data[random(0, 64)] = w_pawn;
  board.data[random(0, 64)] = w_pawn;
  board.data[random(0, 64)] = w_pawn;
  board.data[random(0, 64)] = w_knight;
  // calculate statistics
  char moves[MAX_NO_MOVES_IN_EACH_BOARD];
  char starting_positions[MAX_NO_MOVES_IN_EACH_BOARD];
  float estimations[MAX_NO_MOVES_IN_EACH_BOARD];
  int no_moves = board.generate_legal_moveset_for_color(white, starting_positions, moves);
  float position_estimation = board.estimate_position();

  board.to_string(str_representation_of_a_board);

  Serial.println(":board:");
  Serial.println(str_representation_of_a_board);

  Serial.println(":position_estimation:");
  Serial.println(position_estimation);

  Serial.println(":no_moves_for_white:");
  Serial.println(no_moves);

  Serial.println(":starting_positions_str:");

  for (int i = 0; i < no_moves; i++)

    Serial.println(int(starting_positions[i]));

  Serial.println(":moves_str:");
  for (int i = 0; i < no_moves; i++)
    Serial.println(int(moves[i]));

  Serial.println(":moves_estimation:");
  board.estimate_all_moves_for_color(1, white, no_moves, starting_positions, moves, estimations);

  for (int i = 0; i < no_moves; i++)
    Serial.println(estimations[i]);

  Serial.println(":test_end:");
}

void simulate_game_for_color(int no_iteration, Color color, Board &board, int recursion_depth)
{
  Serial.println(":iteration:");
  Serial.println(no_iteration);

  Serial.println(":color:");

  if (color == white)
    Serial.println("white");
  else
    Serial.println("black");

  char str_representation_of_a_board[65];
  char moves[MAX_NO_MOVES_IN_EACH_BOARD];
  char starting_positions[MAX_NO_MOVES_IN_EACH_BOARD];
  float estimations[MAX_NO_MOVES_IN_EACH_BOARD];
  int no_moves = board.generate_legal_moveset_for_color(color, starting_positions, moves);
  float position_estimation = board.estimate_position();

  Serial.println(":board:");
  board.to_string(str_representation_of_a_board);
  Serial.println(str_representation_of_a_board);

  Serial.println(":position_estimation:");
  Serial.println(position_estimation);

  Serial.println(":no_moves_for_white:");
  Serial.println(no_moves);

  Serial.println(":starting_positions_str:");

  for (int i = 0; i < no_moves; i++)
    Serial.println(int(starting_positions[i]));

  Serial.println(":moves_str:");
  for (int i = 0; i < no_moves; i++)
    Serial.println(int(moves[i]));

  Serial.println(":moves_estimation:");
  board.estimate_all_moves_for_color(recursion_depth, color, no_moves, starting_positions, moves, estimations);

  for (int i = 0; i < no_moves; i++)
    Serial.println(estimations[i]);

  if (no_moves == 0)
  {
    Serial.println(":STOP NO_MOVES:");
    Serial.println(":iteration_end:");
    return;
  }
  float best_move_estimation = estimations[0];
  int best_move_id = 0;

  for (int i = 1; i < no_moves; i++)
  {

    bool better_move = (color == white) ? estimations[i] > best_move_estimation : estimations[i] < best_move_estimation;

    if (better_move)
    {
      best_move_estimation = estimations[i];
      best_move_id = i;
    }
  }
  Serial.println(":best_move_estimation:");
  Serial.println(best_move_estimation);
  bool end_game;
  if (color == white)
    end_game = best_move_estimation > 900;
  else
    end_game = best_move_estimation < -900;

  if (end_game)
  {
    Serial.println(":STOP WHITE WINS:");
    Serial.println(":iteration_end:");
    return;
  }
  board.move(starting_positions[best_move_id], moves[best_move_id]);
  Serial.println(":iteration_end:");
}

void simulate_game()
{
  int no_iteration = 0;
  Board board(true);
  while (true)
  {
    simulate_game_for_color(no_iteration, white, board, 0);
    delay(1000);
    simulate_game_for_color(no_iteration, black, board, 0);
    delay(1000);
    no_iteration++;
  }
}
LedStrip<8> led_strip(64);
#define hall_sensor 7
void setup()
{
  led_strip.TurnRainbowOnAnimation(60);
  pinMode(hall_sensor, INPUT);
  // Serial.begin(115200);
  // Serial.println("Ready streaming");
}
int no_of_test = 0;
void loop()
{

  if (digitalRead(hall_sensor) == HIGH)
  {
    led_strip.Fill(CRGB::WhiteSmoke);
    led_strip.Update();
  }

  if (digitalRead(hall_sensor) == LOW)
  {
    led_strip.Fill(CRGB::Black);
    led_strip.Update();
  }

  delay(200);
  // led_strip.Fill(CRGB::Red);
  // led_strip.Update();
  // delay(2000);
  // led_strip.Fill(CRGB::Blue);
  // led_strip.Update();
  // delay(2000);

  // led_strip.Fill(CRGB::RosyBrown);
  // led_strip.Update();
  // delay(2000);
  // generate_test_cases(no_of_test);

  // simulate_game();
}
