#include "HBridgeController.h"

HBridge_Controller::HBridge_Controller()
{
}

HBridge_Controller::HBridge_Controller(HBridge_Motor m0, HBridge_Motor m1)
{
    this->motor0 = m0;
    this->motor1 = m1;
}

void HBridge_Controller::setEnable(uint8_t enA, uint8_t enB)
{
    motor0.setEnable(enA);
    motor1.setEnable(enB);
}

void HBridge_Controller::stop()
{
    motor0.stop();
    motor1.stop();
}

void HBridge_Controller::forwards()
{
    motor0.forwards();
    motor1.forwards();
}

void HBridge_Controller::backwards()
{
    motor0.backwards();
    motor1.backwards();
}
