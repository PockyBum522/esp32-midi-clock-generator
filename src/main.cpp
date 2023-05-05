#include <Arduino.h>

hw_timer_t *timerConfiguration = NULL;

bool currentState = 1;

const int outputPin = 3;

void IRAM_ATTR timerCallback()
{
    currentState = !currentState;

    digitalWrite(outputPin, currentState);
}

void setup()
{
    pinMode(outputPin, OUTPUT); // That tracks
    digitalWrite(outputPin, 1); // ESP32: HIGH = 0v on pin, LOW = 3v3 on pin. Because that wouldn't have been easy to fix in their SDK, noooooo...

    Serial.begin(115200);

    timerAttachInterrupt(timerConfiguration, &timerCallback, true);

    timerAlarmWrite(timerConfiguration, 50, true); // Every 100 uS

    timerAlarmEnable(timerConfiguration);
}

void loop()
{

}
