#include <Arduino.h>
#include <Board.h>

char str_representation_of_a_board[64];
Board board(true);

void setup()
{
  Serial.begin(115200);
  Serial.println("Ready for input");
  board.to_string(str_representation_of_a_board);
}

void loop()
{

  Serial.println("board:");
  delay(1000);
  Serial.println(str_representation_of_a_board);
  delay(1000);
}
