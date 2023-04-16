#pragma once

#include <Arduino.h>
#include "config.h"

namespace BrDriver
{
    void init();
    void drive(uint8_t p1, uint8_t p2);
    void fuckStep(uint8_t s);
    void fuckNextStepByHall();
}
