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
// #include <Arduino.h>
// #include "LedStrip.h"
// LedStrip<8> led_strip(90);

// void setup()
// {
//     led_strip.TurnRainbowOnAnimation(64);
// }
// void loop()
// {
//     led_strip.Clear();
//     led_strip[89] = CRGB(255, 0, 0);
//     // led_strip[88] = CRGB(255, 0, 0);
//     led_strip[85] = CRGB(255, 0, 0);
//     // led_strip[84] = CRGB(255, 0, 0);
//     led_strip.Update();
//     delay(500);

//     led_strip.Clear();
//     // led_strip[89] = CRGB(255, 0, 0);
//     led_strip[88] = CRGB(255, 0, 0);
//     // led_strip[85] = CRGB(255, 0, 0);
//     led_strip[84] = CRGB(255, 0, 0);
//     led_strip.Update();
//     delay(500);
// }