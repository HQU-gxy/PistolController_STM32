#include <Arduino.h>
#include "config.h"
#include"wl.h"
#include "br_driver.h"

// WLModule wlMod(SET, CS, &Serial1, PIN_RX, PIN_TX);
bool toBeFucked = false, toFuckNextStep = false;

void test4NextStep()
{
    toFuckNextStep = true;
}

void fuckBr()
{
    toBeFucked = true;
    attachInterrupt(HALL1, test4NextStep, CHANGE);
    attachInterrupt(HALL2, test4NextStep, CHANGE);
    attachInterrupt(HALL3, test4NextStep, CHANGE);
}

void setup()
{

    pinMode(TRIGGER, INPUT);
    pinMode(HALL1, INPUT_PULLUP);
    pinMode(HALL2, INPUT_PULLUP);
    pinMode(HALL3, INPUT_PULLUP);
    Serial.begin(115200);
    BrDriver::init();

    attachInterrupt(TRIGGER, fuckBr, FALLING);
}

void loop()
{
    if (toBeFucked)
    {
        uint64_t t0 = millis();
        toFuckNextStep = false;
        BrDriver::fuckStep(0);
        while (millis() - t0 <= 50)
        {
            if (toFuckNextStep)
            {
                toFuckNextStep = false;
                // BrDriver::nextStep();
                BrDriver::fuckNextStepByHall();
            }
        }
        BrDriver::drive(0, 0);
        toBeFucked = false;
        detachInterrupt(HALL1);
        detachInterrupt(HALL2);
        detachInterrupt(HALL3);
    }
}

