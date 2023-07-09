#include <Arduino.h>
#include <Board.h>

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

  Board board;

  // generate random position
  board.data[random(0, 64)] = w_pawn;
  board.data[random(0, 64)] = w_pawn;
  board.data[random(0, 64)] = w_pawn;
  board.data[random(0, 64)] = w_pawn;
  board.data[random(0, 64)] = w_pawn;
  board.data[random(0, 64)] = w_knight;
  // calculate statistics
  char moves[64];
  char starting_positions[64];
  float estimations[64];
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
  {
    Serial.println(int(starting_positions[i]));
    // Serial.println(' ');
  }
  Serial.println(":moves_str:");
  for (int i = 0; i < no_moves; i++)
  {
    Serial.println(int(moves[i]));
    // Serial.println(' ');
  }
  Serial.println(":moves_estimation:");
  board.estimate_all_moves_for_color(0, white, no_moves, starting_positions, moves, estimations);

  for (int i = 0; i < no_moves; i++)
  {
    Serial.println(estimations[i]);
    // Serial.println(' ');
  }

  Serial.println(":test_end:");
}

void setup()
{

  Serial.begin(115200);
  // Serial.println("Ready streaming");
}

int no_of_test = 0;
void loop()
{

  generate_test_cases(no_of_test);
  no_of_test += 1;
  delay(1000);
}
