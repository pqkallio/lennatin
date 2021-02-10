#include <Arduino.h>
#include "morse.h"

#define BTN_OFF 0
#define BTN_PRESS 1
#define BTN_HOLD 2

static const uint8_t TEMPO_PIN = 12;
static const uint8_t MORSE_PIN = 8;

static bool secondHalf = true;
static const uint16_t tickLenInMS = 250;

static uint8_t prevBtnSt = BTN_OFF;

void tempoPinBlink(const unsigned int timeElapsed)
{
    const uint16_t cycleElapse = static_cast<uint16_t>(timeElapsed % tickLenInMS);
    const uint16_t halfCycle = tickLenInMS >> 1;

    if (cycleElapse >= halfCycle && !secondHalf)
    {
        secondHalf = true;

        digitalWrite(TEMPO_PIN, LOW);
    }
    else if (cycleElapse < halfCycle && secondHalf)
    {
        secondHalf = false;

        digitalWrite(TEMPO_PIN, HIGH);
    }
}

const uint8_t getButtonState()
{
    const int btnState = digitalRead(MORSE_PIN);

    if (btnState == LOW)
    {
        prevBtnSt = BTN_OFF;
        return BTN_OFF;
    }

    if (prevBtnSt == BTN_OFF)
    {
        prevBtnSt = BTN_PRESS;
        return BTN_PRESS;
    }

    return BTN_HOLD;
}

void setup()
{
    pinMode(TEMPO_PIN, OUTPUT);
    pinMode(MORSE_PIN, INPUT);
}

void loop()
{
    const unsigned int timeElapsed = millis();
    tempoPinBlink(timeElapsed);
}
