#include "Button165.h"

Button165::Button165(const uint8_t *dataPtr, byte chipIndex, byte bitIndex)
    : dataPtr(dataPtr), chipIndex(chipIndex), bitIndex(bitIndex) {}

bool Button165::readRaw()
{
    return bitRead(dataPtr[chipIndex], bitIndex);
}
