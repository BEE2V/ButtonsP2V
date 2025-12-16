#include <Arduino.h>
#include "Button.h"

// =======================================================================
// EXAMPLE: Standard GPIO Buttons
// =======================================================================
// This sketch demonstrates how to use the ButtonsP2V library with standard
// buttons connected directly to Arduino pins.
//
// Wiring:
// - Button 1: Pin 5 to GND (Input Pullup is used internally)
// - Button 2: Pin 4 to GND
// =======================================================================

// Initialize buttons on specific pins
Button actionBtn(5); // Button for clicking/double-clicking
Button modeBtn(4);   // Button for long-press/toggling

void setup()
{
    Serial.begin(115200);
    Serial.println("ButtonsP2V: GPIO Example Started");
    Serial.println("Btn 1 (Pin 5): Try Single & Double Clicks");
    Serial.println("Btn 2 (Pin 4): Try Long Press & Toggle");
}

void loop()
{
    // 1. UPDATE LOOP
    // You must call update() on every button at the start of the loop
    actionBtn.update();
    modeBtn.update();

    // -------------------------------------------------
    // DEMO 1: Complex Events (Click vs Double Click)
    // -------------------------------------------------

    // .pressed() is true ONLY after a single click is completed
    // (and the timeout for a potential double click has passed).
    if (actionBtn.pressed())
    {
        Serial.println("[Btn 1] Single Click detected!");
    }

    // .doublePressed() detects two quick taps
    if (actionBtn.doublePressed())
    {
        Serial.println("[Btn 1] Double Click detected! (Bang Bang!)");
    }

    // -------------------------------------------------
    // DEMO 2: Holding and Toggling
    // -------------------------------------------------

    // .longPressed() triggers once after the button is held for 'longPress' duration
    if (modeBtn.longPressed())
    {
        Serial.println("[Btn 2] LONG PRESS detected - Entering Menu...");
    }

    // .toggleState() flips between true/false on every press.
    // Useful for on/off switches without needing extra boolean variables.
    static bool lastToggleState = false;
    if (modeBtn.toggleState() != lastToggleState)
    {
        lastToggleState = modeBtn.toggleState();
        Serial.print("[Btn 2] Toggle Switch is now: ");
        Serial.println(lastToggleState ? "ON" : "OFF");
    }
}