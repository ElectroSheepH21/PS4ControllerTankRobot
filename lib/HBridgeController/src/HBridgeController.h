#include <Arduino.h>
#include "HBridgeMotor.h"

class HBridge_Controller
{
private:
    HBridge_Motor motor0;
    HBridge_Motor motor1;

public:
    HBridge_Controller();
    HBridge_Controller(HBridge_Motor m0, HBridge_Motor m1);
    void setEnable(uint8_t enA, uint8_t enB);
    void stop();
    void forwards();
    void backwards();
};


