#include <Arduino.h>
#include "config.h"

#define SerialWL Serial
namespace WLModuleUART
{
    constexpr uint8_t WL_TX = PB6;
    constexpr uint8_t WL_RX = PB7;

    void init()
    {
        SerialWL.setRx(WL_RX);
        SerialWL.setTx(WL_TX);
        SerialWL.begin(9600);
    }

    inline void send(char *data, uint8_t len)
    {
        SerialWL.write(data, len);
    }
    inline void print(String s)
    {
        SerialWL.print(s);
    }

    inline bool available()
    {
        return SerialWL.available();
    }

    inline char read()
    {
        return SerialWL.read();
    }
}