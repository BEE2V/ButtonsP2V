#include "Button.h"

Button::Button(byte pin) : pin(pin)
{
    pinMode(pin, INPUT_PULLUP);
}

bool Button::readRaw()
{
    return !digitalRead(pin); // active LOW
}
