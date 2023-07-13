#include <Arduino.h>
#include "LedStrip.h"
LedStrip<8> led_strip(64);

void setup()
{
    led_strip.TurnRainbowOnAnimation(64);
}
void loop()
{
}
