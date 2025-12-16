#ifndef BUTTON_H
#define BUTTON_H

#include "ButtonBase.h"

class Button : public ButtonBase
{
private:
    const byte pin;

public:
    Button(byte pin);
    bool readRaw() override;
};

#endif
