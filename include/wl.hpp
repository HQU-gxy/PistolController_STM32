#pragma once
#include <Arduino.h>
#include <RF24.h>
#include <SPI.h>
#include "config.h"

namespace WLModule
{
    RF24 radio;
    void init()
    {
        const uint8_t localAddr[6] = "lm";
        const uint8_t remoteAddr[6] = "cmy";

        SPIClass SPI_WL(WL_MOSI, WL_MISO, WL_CLK);
        RF24 radio(WL_CE, WL_CS);
        radio.begin(&SPI_WL);
        radio.openWritingPipe(localAddr);
        radio.openReadingPipe(1, remoteAddr);
        radio.setPALevel(RF24_PA_MAX);
        radio.startListening();
    }
    inline bool available()
    {
        return radio.available();
    }
    inline bool send(char *data, uint8_t len)
    {
        radio.stopListening();
        return radio.write(data, len);
        radio.startListening();
    }

    inline void readInto(char *buf)
    {
        radio.read(buf, 32);
    }

}