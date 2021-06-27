#include <Arduino.h>

class HBridge_Motor
{
private:
int8_t offset;
uint8_t pin0;
uint8_t pin1;
uint8_t pinEn;
public:
    HBridge_Motor();
    HBridge_Motor(uint8_t p0, uint8_t p1, uint8_t pEn);
    void setOffset(int8_t off);
    uint8_t getOffset();
    uint8_t getPin0();
    uint8_t getPin1();
    uint8_t getPinEn();
    void stop();
    void fowards();
    void backwards();
    void setEnable(uint8_t en);
};
