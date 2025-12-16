#include "ButtonBase.h"

// Internal FSM States
#define S_IDLE 0
#define S_DOWN 1
#define S_WAIT_UP 2
#define S_WAIT_DOUBLE 3
#define S_LONG_NOTIFY 4

ButtonBase::ButtonBase() : lastPressed(0), flags(0), _clickState(S_IDLE) {}

void ButtonBase::update()
{
    // 1. Read Input
    bool raw = readRaw();
    unsigned long now = millis();
    unsigned long waitTime = now - lastPressed;

    // 2. Clear Event Bits (5 and 6) at start of loop
    //    We preserve bits 0-4 (Signal state) and 7 (if used)
    flags &= ~(0x60);

    // 3. Update Basic Signal State (Debounce filtered for bits 0-4)
    //    Note: We decouple the logic FSM from the basic signal bits slightly
    //    to ensure 'state()' always reflects the stable physical state.

    // Simple software debounce for the physical 'state' bit
    static long _debounceTimer = 0; // Local static to isolate from logic timer
    static bool _lastRaw = false;
    if (raw != _lastRaw)
        _debounceTimer = now;
    _lastRaw = raw;

    if (now - _debounceTimer > debounce)
    {
        bitWrite(flags, 0, raw); // Stable State
    }

    // Edge Detection for bits 3 & 4
    bool curr = bitRead(flags, 0);
    bool prev = bitRead(flags, 1);
    bitWrite(flags, 3, curr && !prev); // Rising
    bitWrite(flags, 4, !curr && prev); // Falling
    if (bitRead(flags, 3))
        bitWrite(flags, 2, !bitRead(flags, 2)); // Toggle
    bitWrite(flags, 1, curr);                   // Store PreState

    // -----------------------------------------------------------
    // 4. COMPLEX EVENT LOGIC (Single Timer: lastPressed)
    // -----------------------------------------------------------

    switch (_clickState)
    {
    case S_IDLE:
        if (raw == HIGH)
        { // Button Pressed
            _clickState = S_DOWN;
            lastPressed = now; // Timer tracks: Start of Press
        }
        break;

    case S_DOWN:
        // Check for Long Press
        if (raw == HIGH && waitTime > longPress)
        {
            // Trigger LONG PRESS (Code 3: bits 5=1, 6=1)
            bitWrite(flags, 5, 1);
            bitWrite(flags, 6, 1);
            _clickState = S_LONG_NOTIFY;
        }
        // Check for Release (Potential Click)
        else if (raw == LOW && waitTime > debounce)
        {
            _clickState = S_WAIT_DOUBLE;
            lastPressed = now; // Timer tracks: Start of Release gap
        }
        break;

    case S_WAIT_DOUBLE:
        // Check for Timeout -> It was a SINGLE PRESS
        if (waitTime > doublePressGap)
        {
            // Trigger SINGLE PRESS (Code 1: bit 5=1, 6=0)
            bitWrite(flags, 5, 1);
            bitWrite(flags, 6, 0);
            _clickState = S_IDLE;
        }
        // Check for Second Press -> DOUBLE PRESS
        else if (raw == HIGH && waitTime > debounce)
        {
            // Trigger DOUBLE PRESS (Code 2: bit 5=0, 6=1)
            bitWrite(flags, 5, 0);
            bitWrite(flags, 6, 1);
            _clickState = S_LONG_NOTIFY; // Wait for release
        }
        break;

    case S_LONG_NOTIFY:
        // Wait for button to be released before resetting to Idle
        if (raw == LOW && waitTime > debounce)
        {
            _clickState = S_IDLE;
        }
        break;
    }
}

String ButtonBase::getFlagString(byte bits)
{
    String s = "";
    for (int i = bits - 1; i >= 0; i--)
        s += bitRead(flags, i);
    return s;
}

// Basic State Accessors
bool ButtonBase::state() { return bitRead(flags, 0); }
bool ButtonBase::preState() { return bitRead(flags, 1); }
bool ButtonBase::toggleState() { return bitRead(flags, 2); }
bool ButtonBase::risingEdge() { return bitRead(flags, 3); }
bool ButtonBase::fallingEdge() { return bitRead(flags, 4); }

// Complex Event Accessors
// Using the 2-bit code stored in flags(5,6)
// 00 = None, 01 = Single, 10 = Double, 11 = Long

bool ButtonBase::pressed()
{
    // Returns true only if code is exactly 01 (Single)
    return bitRead(flags, 5) && !bitRead(flags, 6);
}

bool ButtonBase::doublePressed()
{
    // Returns true only if code is exactly 10 (Double)
    return !bitRead(flags, 5) && bitRead(flags, 6);
}

bool ButtonBase::longPressed()
{
    // Returns true only if code is exactly 11 (Long)
    return bitRead(flags, 5) && bitRead(flags, 6);
}