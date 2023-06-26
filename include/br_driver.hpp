#include <Arduino.h>
#include "config.h"

namespace BrDriver
{
    // BH	CL
    // AH	CL
    // AH	BL
    // CH	BL
    // CH	AL
    // BH	AL
    // HardwareTimer beepTimer(TIM2);
    void init()
    {
        pinMode(BR_AH, OUTPUT);
        pinMode(BR_AL, OUTPUT);
        pinMode(BR_BH, OUTPUT);
        pinMode(BR_BL, OUTPUT);
        pinMode(BR_CH, OUTPUT);
        pinMode(BR_CL, OUTPUT);
        pinMode(HALL1, INPUT_PULLUP);
        pinMode(HALL2, INPUT_PULLUP);
        pinMode(HALL3, INPUT_PULLUP);
        analogWriteFrequency(1e4);
    }

    void drive(uint8_t h, uint8_t l)
    {

        analogWrite(BR_AH, 0);
        analogWrite(BR_BH, 0);
        analogWrite(BR_CH, 0);
        digitalWrite(BR_AL, 0);
        digitalWrite(BR_BL, 0);
        digitalWrite(BR_CL, 0);

        if (h == 0 && l == 0)
            return;

        analogWrite(h, 80);
        digitalWrite(l, 1);
    }

    void fuckStep(uint8_t s)
    {
#ifdef STEP_TEST
        Serial2.printf("Step:%d\tH1:%d\tH2:%d\tH3:%d\n", s, digitalRead(HALL1), digitalRead(HALL2), digitalRead(HALL3));
#endif
        switch (s)
        {
        case 3:
            drive(BR_CH, BR_AL);
            break;

        case 4:
            drive(BR_BH, BR_AL);
            break;
        case 5:
            drive(BR_BH, BR_CL);
            break;

        case 0:
            drive(BR_AH, BR_CL);
            break;

        case 1:
            drive(BR_AH, BR_BL);
            break;

        case 2:
            drive(BR_CH, BR_BL);
            break;
        }
    }

    void fuckNextStepByHall()
    {
        uint8_t hSum = (digitalRead(HALL1) << 2) + (digitalRead(HALL2) << 1) + digitalRead(HALL3);
        switch (hSum)
        {
        case 0b110:
            fuckStep(0);
            break;
        case 0b100:
            fuckStep(1);
            break;
        case 0b101:
            fuckStep(2);
            break;
        case 0b011:
            fuckStep(3);
            break;
        case 0b001:
            fuckStep(4);
            break;
        case 0b010:
            fuckStep(5);
            break;
        default:
            break;
        }
    }

    // void beepCallBack()
    // {
    //     static bool shit = false;
    //     if (shit)
    //         drive(BR_CH, BR_BL);
    //     else
    //         drive(0, 0);

    //     shit = !shit;
    // }

    // void beep(uint16_t f, uint16_t t)
    // {

    //     beepTimer.setOverflow(f, HERTZ_FORMAT);
    //     beepTimer.attachInterrupt(beepCallBack);
    //     beepTimer.resume();
    //     delay(t);
    //     beepTimer.detachInterrupt();
    //     drive(0, 0);
    // }

    void beep(uint16_t f, uint16_t t)
    {
        analogWriteFrequency(f);
        analogWrite(BR_AH, 20);
        digitalWrite(BR_BL, 1);
        delay(t);
        drive(0, 0);
        analogWriteFrequency(1e4);
    }

    void nextStep()
    {
        static uint8_t s = 0;
        fuckStep(s++);
        s %= 6;
    }
}
