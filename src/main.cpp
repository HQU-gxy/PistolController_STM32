#include <Arduino.h>
#include "config.h"
#include "wl.hpp"
#include "br_driver.hpp"
#include <TinyIRSender.hpp>
#include <EEPROM.h>

// #include"wl_uart.hpp"

// #include"wl_uart.hpp"

bool toBeFucked = false, toFuckNextStep = false;

inline void test4NextStep()
{
    toFuckNextStep = true;
}

bool checkBattery()
{
    bool batteryNice = (analogRead(ADC_BAT) > 139);
    if (batteryNice)
        return true;

    BrDriver::beep(900, 100);
    BrDriver::beep(700, 100);
    BrDriver::beep(500, 100);
    return false;
}

inline void batteryCheckCallback()
{
    static uint8_t cnt = 0;
    if (cnt++ == 10)
    {
        checkBattery();
        cnt = 0;
    }
}

inline void fuckBr()
{
    // if (!checkBattery)
    //     return;
    Serial2.println("------Fucking By Trigger-----");
    toBeFucked = true;
    attachInterrupt(HALL1, test4NextStep, CHANGE);
    attachInterrupt(HALL2, test4NextStep, CHANGE);
    attachInterrupt(HALL3, test4NextStep, CHANGE);
}

void setup()
{

    pinMode(TRIGGER, INPUT);
    pinMode(IR_SEND_PIN, OUTPUT);

    Serial2.begin(9600);
    WLModule::init();

    BrDriver::init();
    BrDriver::beep(500, 200);
    BrDriver::beep(700, 200);
    BrDriver::beep(900, 200);

    // HardwareTimer batteryCheckTimer(TIM2);
    // batteryCheckTimer.setOverflow(1, HERTZ_FORMAT);
    // batteryCheckTimer.attachInterrupt(batteryCheckCallback);
    // batteryCheckTimer.resume();

    attachInterrupt(TRIGGER, fuckBr, FALLING);
}

bool startFuckingTiming = false;
uint32_t fuckingStartTime = 0;

void loop()
{

    if (toBeFucked)
    {
        if (!startFuckingTiming)
        {
            fuckingStartTime = millis();
            startFuckingTiming = true;
            BrDriver::fuckStep(0);
            delay(10);
            BrDriver::fuckStep(1);
        }
        if (toFuckNextStep)
        {
            toFuckNextStep = false;
            // BrDriver::nextStep();
            BrDriver::fuckNextStepByHall();
            delay(15);
        }

        if (millis() - fuckingStartTime > 150) // stop fucking
        {
            BrDriver::drive(0, 0);
            startFuckingTiming = false;
            toBeFucked = false;
            detachInterrupt(HALL1);
            detachInterrupt(HALL2);
            detachInterrupt(HALL3);
            attachInterrupt(TRIGGER, fuckBr, FALLING); // this EXTI might be fucked up by another INT configuration
        }
    }

    if (!(millis() % 200))
        sendNEC(IR_SEND_PIN, 233, 11451, 1);

    /*
    if (Serial.available())
    {
        char c = Serial.read();
        int s = atoi(&c);
        BrDriver::fuckStep(s);
        delay(6);

        BrDriver::drive(0, 0);
    }

// if (!(millis() % 1000))
//     WLModule::send("shit", 5);
#ifdef STEP_TEST
    if (Serial2.available())
    {
        char c = Serial2.read();
        if (c == 'g')
        {
            Serial2.println("------Fucking fully------");
            for (uint8_t a = 0; a < 12; a++)
            {
                BrDriver::fuckStep(a % 6);
                delay(10);
            }
            BrDriver::drive(0, 0);
            delay(400);
        }
        else
        {
            int s = atoi(&c);
            Serial2.printf("Fucking: %d\n", s);
            BrDriver::fuckStep(s);
            delay(5);

            BrDriver::drive(0, 0);
        }
    }
#endif

    // if (toBeFucked)
    // {
    //     for (uint8_t i = 0; i < 12; i++)
    //     {
    //             toFuckNextStep = false;
    //             BrDriver::nextStep();
    //             delay(20);
    //     }
    //     BrDriver::drive(0, 0);
    //     toBeFucked = false;
    // }

    if (!(millis() % 1000))
    {
        Serial2.println("114514");
        yield();
    }
}
