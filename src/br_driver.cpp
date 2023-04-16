#include "br_driver.h"

// BH	CL
// AH	CL
// AH	BL
// CH	BL
// CH	AL
// BH	AL
void BrDriver::init()
{
    pinMode(BR_AH, OUTPUT);
    pinMode(BR_AL, OUTPUT);
    pinMode(BR_BH, OUTPUT);
    pinMode(BR_BL, OUTPUT);
    pinMode(BR_CH, OUTPUT);
    pinMode(BR_CL, OUTPUT);
    pinMode(HALL1, INPUT);
    pinMode(HALL2, INPUT);
    pinMode(HALL3, INPUT);
    analogWriteFrequency(10000);
}

void BrDriver::drive(uint8_t p1, uint8_t p2)
{

    analogWrite(BR_AH, 0);
    analogWrite(BR_AL, 0);
    analogWrite(BR_BH, 0);
    analogWrite(BR_BL, 0);
    analogWrite(BR_CH, 0);
    analogWrite(BR_CL, 0);

    if (p1 == 0 && p2 == 0)
        return;

    analogWrite(p1, 180);
    analogWrite(p2, 180);
}

void BrDriver::fuckStep(uint8_t s)
{
    Serial.printf("Step:%d\tH1:%d\tH2:%d\tH3:%d\n", s, digitalRead(HALL1), digitalRead(HALL2), digitalRead(HALL3));
    switch (s)
    {
    case 0:
        drive(BR_CH, BR_AL);
        break;

    case 5:
        drive(BR_BH, BR_AL);
        break;
    case 4:
        drive(BR_BH, BR_CL);
        break;

    case 3:
        drive(BR_AH, BR_CL);
        break;

    case 2:
        drive(BR_AH, BR_BL);
        break;

    case 1:
        drive(BR_CH, BR_BL);
        break;
    }
}

void BrDriver::fuckNextStepByHall()
{
    uint8_t hSum = (digitalRead(HALL1) << 2) + (digitalRead(HALL2) << 1) + digitalRead(HALL3);
    switch (hSum)
    {
    case 0b011:
        fuckStep(0);
        break;
    case 0b010:
        fuckStep(1);
        break;
    case 0b110:
        fuckStep(2);
        break;
    case 0b100:
        fuckStep(3);
        break;
    case 0b101:
        fuckStep(4);
        break;
    case 0b001:
        fuckStep(5);
        break;
    default:
        break;
    }
}