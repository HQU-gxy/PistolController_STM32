#include "wl.h"

WLModule::WLModule(uint8_t pin_set, uint8_t pin_cs,SerialUART *ser, uint8_t pin_rx, uint8_t pin_tx)
{
    _pin_set = pin_set;
    _pin_cs = pin_cs;
    _pin_rx = pin_rx;
    _pin_tx = pin_tx;
    _serial = ser;
    _serial->setRX(_pin_rx);
    _serial->setTX(_pin_tx);
    _serial->begin(9600);
}

