#include <Arduino.h>
#define hall_sensor 7
void setup()
{
    pinMode(hall_sensor, INPUT);
    Serial.begin(115200);
    Serial.println("Ready streaming");
}
int no_of_test = 0;
void loop()
{

    if (digitalRead(hall_sensor) == HIGH)
    {
        Serial.println("high");
    }

    if (digitalRead(hall_sensor) == LOW)
    {
        Serial.println("low");
    }
}
