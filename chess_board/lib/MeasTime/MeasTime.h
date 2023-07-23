
#include <Arduino.h>
#ifndef MEAS_TIME_H
#define MEAS_TIME_H
class MeasTime
{
public:
    unsigned long timer;
    const char *timer_name;
    bool miliseconds_mode;
    MeasTime(const char *name, bool miliseconds_mode = false)
    {

        miliseconds_mode = miliseconds_mode;
        timer_name = name;
        if (miliseconds_mode)
            timer = millis();
        else
            timer = micros();
    }
    MeasTime()
    {
        timer = micros();
    }
    void show()
    {

        Serial.println(micros() - timer);
        Serial.flush();
    }
};

#endif