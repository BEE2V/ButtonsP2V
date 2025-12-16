#include <Arduino.h>
#include "Buttons165.h"

// =======================================================================
// EXAMPLE: 74HC165 Shift Register Buttons
// =======================================================================
// This sketch demonstrates reading multiple buttons using 74HC165 chips.
// This saves pins: you get 8, 16, 24+ buttons using only 3 wire pins.
//
// Wiring (74HC165):
// - Pin 1 (PL/Load)  -> Arduino Pin 7
// - Pin 2 (CP/Clock) -> Arduino Pin 6
// - Pin 9 (Q7/Data)  -> Arduino Pin 4
// - Chain multiple chips by connecting Q7 (Pin 9) of Chip 2 to DS (Pin 10) of Chip 1.
// =======================================================================

// Configuration: Data=4, Load=7, Clock=6, Count=2 chips (16 buttons)
Buttons165 inputs(4, 7, 6, 2);

void setup()
{
    Serial.begin(115200);
    Serial.println("ButtonsP2V: Shift Register Example");
}

void loop()
{
    // 1. UPDATE LOOP
    // Reads all shift registers at once and processes logic for every button
    inputs.update();

    // -------------------------------------------------
    // Method A: Check specific known buttons
    // -------------------------------------------------

    // Check the very first button (Chip 0, Pin 0) for a click
    if (inputs.get(0).pressed())
    {
        Serial.println("Button 0 Clicked!");
    }

    // Check the last button (Chip 1, Pin 7 -> Index 15) for a hold
    if (inputs.get(15).longPressed())
    {
        Serial.println("Button 15 Held Down!");
    }

    // -------------------------------------------------
    // Method B: Iterate all buttons (Good for grids/sequencers)
    // -------------------------------------------------
    for (int i = 0; i < inputs.getButtonCount(); i++)
    {

        // 'state()' gives the raw debounced state (True = Held Down)
        // Useful for debugging to see what is currently pressed
        if (inputs.get(i).state())
        {
            // Uncomment to flood serial with current states
            // Serial.print("Btn "); Serial.print(i); Serial.println(" is DOWN");
        }

        // Detect a rising edge (the exact moment a button is pressed)
        if (inputs.get(i).risingEdge())
        {
            Serial.print("Button ");
            Serial.print(i);
            Serial.println(" just went DOWN (Rising Edge)");
        }
    }
}