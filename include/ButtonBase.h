#ifndef BUTTON_BASE_H
#define BUTTON_BASE_H

#include <Arduino.h>

class ButtonBase
{
protected:
    static const int debounce = 50;
    static const int doublePressGap = 250;
    static const int longPress = 200; // Time held down to trigger long press

    long lastPressed;
    byte flags;
    // flags bits:
    // 0=State, 1=PreState, 2=Toggle, 3=RisingEdge, 4=FallingEdge
    // 5,6 = Output Code (0=None, 1=Pressed, 2=Double, 3=Long)

    uint8_t _clickState; // Internal State Machine Tracker

public:
    ButtonBase();
    virtual void update();
    virtual bool readRaw() = 0;

    String getFlagString(byte bits = 7);

    // Basic Signal states
    bool state();
    bool preState();
    bool toggleState();
    bool risingEdge();
    bool fallingEdge();

    // Complex Events (Transient - true for one loop only)
    bool pressed();       // Single Click
    bool doublePressed(); // Double Click
    bool longPressed();   // Long Hold
};

#endif