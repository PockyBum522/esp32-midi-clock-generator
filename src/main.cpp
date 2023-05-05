#include <Arduino.h>

hw_timer_t *timerConfiguration = NULL;

void IRAM_ATTR togglePinState();

const int outputPin = 4;
bool currentState = true;

void setup()
{
    pinMode(outputPin, OUTPUT); // That tracks
    digitalWrite(outputPin, true); // ESP32: HIGH = 0v on pin, LOW = 3v3 on pin. Because that wouldn't have been easy to fix in their SDK, noooooo...

    Serial.begin(115200);

    timerAttachInterrupt(timerConfiguration, &togglePinState, true);

    timerAlarmWrite(timerConfiguration, 50, true); // Every 100 uS

    timerAlarmEnable(timerConfiguration);
}

void loop()
{
//    togglePinState();
//
//    delay(100); // ages
}

void togglePinState()
{
    currentState = !currentState;

    digitalWrite(outputPin, currentState);
}
