#include <Arduino.h>
#include <PS4BT.h>
#include <usbhub.h>
#include <SPI.h>
#include "HBridgeController.h"

class Tank_Robot
{
private:
    HBridge_Controller controller;
public:
    Tank_Robot();
    void task();
};
