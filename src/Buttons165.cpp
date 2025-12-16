#include "Buttons165.h"

Buttons165::Buttons165(byte dataPin, byte loadPin, byte clockPin, byte numChips)
    : dataPin(dataPin), loadPin(loadPin), clockPin(clockPin), numChips(numChips)
{
    pinMode(loadPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, INPUT);

    data = new uint8_t[numChips];
    buttons = new Button165 *[numChips * 8];

    // Create all button objects
    for (byte chip = 0; chip < numChips; chip++)
    {
        for (byte bit = 0; bit < 8; bit++)
        {
            byte idx = chip * 8 + bit;
            buttons[idx] = new Button165(data, chip, bit);
        }
    }
}

Buttons165::~Buttons165()
{
    for (byte i = 0; i < numChips * 8; i++)
    {
        delete buttons[i];
    }
    delete[] buttons;
    delete[] data;
}

void Buttons165::readAll()
{
    // Latch parallel inputs
    digitalWrite(loadPin, LOW);
    delayMicroseconds(5);
    digitalWrite(loadPin, HIGH);

    // Read all bytes (MSB first per chip)
    for (byte chip = 0; chip < numChips; chip++)
    {
        uint8_t value = 0;
        for (int i = 0; i < 8; i++)
        {
            value <<= 1;
            if (digitalRead(dataPin))
                value |= 1;
            digitalWrite(clockPin, HIGH);
            delayMicroseconds(2);
            digitalWrite(clockPin, LOW);
        }
        data[chip] = value;
    }
}

void Buttons165::update()
{
    readAll();
    for (byte i = 0; i < numChips * 8; i++)
    {
        buttons[i]->update();
    }
}

Button165 &Buttons165::get(byte index)
{
    return *buttons[index];
}

byte Buttons165::getButtonCount()
{
    return numChips * 8;
}
