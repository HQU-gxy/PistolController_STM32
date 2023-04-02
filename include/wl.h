#pragma once

#include <Arduino.h>
class WLModule
{
public:
    WLModule(uint8_t pin_set, uint8_t pin_cs, SerialUART *ser, uint8_t pin_rx, uint8_t pin_tx);

private:
    uint8_t _pin_set;
    uint8_t _pin_cs;
    uint8_t _pin_rx;
    uint8_t _pin_tx;
    SerialUART *_serial;
};
