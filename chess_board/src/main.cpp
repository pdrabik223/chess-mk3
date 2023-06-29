#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup()
{
  Serial.begin(115200);
  Serial.println("Ready for input");
}

void loop()
{
  char c;

  if (Serial.available() > 0)
  {
    c = Serial.read();

    Serial.print("Char = ");
    Serial.println(c, DEC);
  }
}
