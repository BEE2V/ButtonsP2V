#ifndef BUTTON165_H
#define BUTTON165_H

#include "ButtonBase.h"

class Button165 : public ButtonBase
{
private:
    const byte chipIndex;   // Which LS165 chip
    const byte bitIndex;    // Which bit in that chip (0–7)
    const uint8_t *dataPtr; // Pointer to data array managed by Buttons165

public:
    Button165(const uint8_t *dataPtr, byte chipIndex, byte bitIndex);
    bool readRaw() override;
};

#endif
