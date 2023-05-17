#include <Arduino.h>

hw_timer_t *timerConfiguration = NULL;

void IRAM_ATTR togglePinState();
void initializeHardwareTimer();

const int outputPin = 5;
bool currentState = true;

void setup()
{
    pinMode(outputPin, OUTPUT); // That tracks
    digitalWrite(outputPin, true); // ESP32: HIGH = 0v on pin, LOW = 3v3 on pin. Because that wouldn't have been easy to fix in their SDK, noooooo...

    Serial.begin(115200);

    initializeHardwareTimer();
}

void loop()
{
#if defined(ESP32)
    Serial.println("I'm a esp32");
#endif

    delay(2000);
}

void togglePinState()
{
    currentState = !currentState;

    digitalWrite(outputPin, currentState);
}

void initializeHardwareTimer()
{
    timerConfiguration = timerBegin(0, 80, true);

    timerAttachInterrupt(timerConfiguration, &togglePinState, true);

    timerAlarmWrite(timerConfiguration, 50, true); // Cycle on/off totals 100 uS. 50us on then 50us off

    timerAlarmEnable(timerConfiguration);
}