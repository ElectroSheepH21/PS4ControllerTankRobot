#include "HBridgeMotor.h"

HBridge_Motor::HBridge_Motor()
{
}

HBridge_Motor::HBridge_Motor(uint8_t p0, uint8_t p1, uint8_t pEn)
{
    this->pin0 = p0;
    this->pin1 = p1;
    this->pinEn = pEn;

    pinMode(pin0, OUTPUT);
    pinMode(pin1, OUTPUT);
    pinMode(pinEn, OUTPUT);
}

void HBridge_Motor::setOffset(int8_t off)
{
    this->offset = off;
}

uint8_t HBridge_Motor::getOffset()
{
    return this->offset;
}

uint8_t HBridge_Motor::getPin0()
{
    return this->pin0;
}

uint8_t HBridge_Motor::getPin1()
{
    return this->pin1;
}

uint8_t HBridge_Motor::getPinEn()
{
    return this->pinEn;
}

void HBridge_Motor::stop()
{
    digitalWrite(pin0, 0);
    digitalWrite(pin1, 0);
}

void HBridge_Motor::forwards()
{
    digitalWrite(pin0, 1);
    digitalWrite(pin1, 0);
}

void HBridge_Motor::backwards()
{
    digitalWrite(pin0, 0);
    digitalWrite(pin1, 1);
}

void HBridge_Motor::setEnable(uint8_t en)
{
    analogWrite(pinEn, en);
}