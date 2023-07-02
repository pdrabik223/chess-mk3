#include <Arduino.h>
#include <Board.h>

void convert_int_array_to_char(int len, int *int_array, char *string)
{
  for (int i = 0; i < len; i++)
  {
    int x = int_array[i] / 8;
    int y = int_array[i] % 8;

    string[i * 2] = char('0' + x);
    string[i * 2 + 1] = char('0' + y);
  }
}

char str_representation_of_a_board[64];
int pawn_moves[64];
char pawn_moves_str[128];
Board board(true);

void setup()
{
  Serial.begin(115200);
  Serial.println("Ready streaming");

  board.to_string(str_representation_of_a_board);
  Serial.println("board:");
  Serial.println(str_representation_of_a_board);
  delay(1000);
}
void loop()
{

  for (int pos = 0; pos < 64; pos++)
  {

    for (int i = 0; i < 128; i++)
      pawn_moves_str[i] = '-';

    int no_legal_moves = 0;

    if (board.data[pos] == b_pawn || board.data[pos] == w_pawn)
    {
      no_legal_moves = board.generate_legal_moveset_pawn(pos, pawn_moves);
      convert_int_array_to_char(no_legal_moves, pawn_moves, pawn_moves_str);
    }
    if (board.data[pos] == b_knight || board.data[pos] == w_knight)
    {
      no_legal_moves = board.generate_legal_moveset_knight(pos, pawn_moves);
      convert_int_array_to_char(no_legal_moves, pawn_moves, pawn_moves_str);
    }
    if (board.data[pos] == b_king || board.data[pos] == w_king)
    {
      no_legal_moves = board.generate_legal_moveset_king(pos, pawn_moves);
      convert_int_array_to_char(no_legal_moves, pawn_moves, pawn_moves_str);
    }
    if (board.data[pos] == b_rook || board.data[pos] == w_rook)
    {
      no_legal_moves = board.generate_legal_moveset_rook(pos, pawn_moves);
      convert_int_array_to_char(no_legal_moves, pawn_moves, pawn_moves_str);
    }
    if (board.data[pos] == b_bishop || board.data[pos] == b_bishop)
    {
      no_legal_moves = board.generate_legal_moveset_bishop(pos, pawn_moves);
      convert_int_array_to_char(no_legal_moves, pawn_moves, pawn_moves_str);
    }
    if (board.data[pos] == b_queen || board.data[pos] == b_queen)
    {
      no_legal_moves = board.generate_legal_moveset_queen(pos, pawn_moves);
      convert_int_array_to_char(no_legal_moves, pawn_moves, pawn_moves_str);
    }
    Serial.println("pos x:");
    Serial.println(int(pos / 8));
    Serial.println("pos y:");
    Serial.println(int(pos % 8));
    Serial.println("chess piece on pos:");
    Serial.println(symbol_encoding[board.data[pos]]);
    Serial.println("no_legal_moves:");
    Serial.println(no_legal_moves);
    Serial.println("pawn_moves_str:");
    Serial.println(pawn_moves_str);
    Serial.println("estimation:");
    Serial.println(board.estimate_position());
    delay(1000);
  }
}
