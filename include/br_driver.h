#pragma once

#include <Arduino.h>
#include "config.h"

namespace BrDriver
{

    void init();
    void drive(uint8_t h, uint8_t l);
    void fuckStep(uint8_t s);
    void nextStep();
    void fuckNextStepByHall();
    void beep(uint16_t f, uint16_t t);
    void beepCallBack();
}
