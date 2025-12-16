# ButtonsP2V Library

A robust Arduino/PlatformIO library for handling buttons. It supports both standard GPIO buttons and buttons connected via **74HC165 shift registers** (daisy-chained).

## Features
- **Debounce**: Configurable software debouncing.
- **Event Detection**: Rising edge, Falling edge, Toggle state.
- **Complex Events**: 
  - Single Click
  - Double Click
  - Long Press
- **Shift Register Support**: Efficiently read multiple 74HC165 chips using a single object.

## Installation (PlatformIO)

Add the git link to your `platformio.ini`:

```ini
[env:my_env]
lib_deps =
    [https://github.com/BEE2V/ButtonsP2V.git](https://github.com/BEE2V/ButtonsP2V.git)
```
## Arduino IDE
Download this repository as a ZIP file.
In Arduino IDE, go to Sketch -> Include Library -> Add .ZIP Library...
Select the downloaded file.

## Usage
1. Standard GPIO Button
```c++
#include <Button.h>

// Button on Pin 5, active LOW (Input Pullup internal)
Button myBtn(5); 

void setup() {
    Serial.begin(115200);
}

void loop() {
    myBtn.update(); // Must be called every loop

    if (myBtn.pressed()) {
        Serial.println("Single Click!");
    }
    
    if (myBtn.longPressed()) {
        Serial.println("Long Press Detected");
    }
}
```
2. 74HC165 Shift Registers
```c++
#include <Buttons165.h>

// Config: DataPin=4, LoadPin=7, ClockPin=6, Number of Chips=2
Buttons165 shiftButtons(4, 7, 6, 2);

void setup() {
    Serial.begin(115200);
}

void loop() {
    shiftButtons.update(); // Reads all chips and updates logic

    // Access specific button (Index 0-7 for chip 1, 8-15 for chip 2, etc.)
    if (shiftButtons.get(0).pressed()) {
        Serial.println("First button on shift register clicked");
    }
}
```

## API Reference
ButtonBase Methods (Available on both Button and Button165)

| **Method**        | **Returns** | **Description**                                                       |
| ----------------- | ----------- | --------------------------------------------------------------------- |
| `update()`        | `void`      | Read hardware & update state machines. Call this every loop.          |
| `state()`         | `bool`      | Current stable state (High/Low).                                      |
| `pressed()`       | `bool`      | True only on a completed single click event.                          |
| `doublePressed()` | `bool`      | True only on a completed double click event.                          |
| `longPressed()`   | `bool`      | True when the button has been held for the long press duration.       |
| `risingEdge()`    | `bool`      | True on the exact frame the signal goes HIGH.                         |
| `fallingEdge()`   | `bool`      | True on the exact frame the signal goes LOW.                          |
| `toggleState()`   | `bool`      | Toggles true/false on every rising edge (useful for on/off switches). |

