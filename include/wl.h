#pragma once
#include <Arduino.h>
#include <RF24.h>
#include <SPI.h>
#include "config.h"

namespace WLModule
{
    extern RF24 radio;
    void init();
    bool available();
    bool send(char *data, uint8_t len);
    void readInto(char *buf);
    
}