#ifndef BUTTONS165_H
#define BUTTONS165_H

#include <Arduino.h>
#include "Button165.h"

class Buttons165
{
private:
    const byte loadPin;
    const byte clockPin;
    const byte dataPin;
    const byte numChips;
    uint8_t *data;       // Stores 1 byte per 74LS165
    Button165 **buttons; // Array of pointers to each Button165

    void readAll(); // Reads all LS165 chips into data[]

public:
    Buttons165(byte dataPin, byte loadPin, byte clockPin, byte numChips);
    ~Buttons165();

    void update();
    Button165 &get(byte index); // Get a specific button reference
    byte getButtonCount();
};

#endif
