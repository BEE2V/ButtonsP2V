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
