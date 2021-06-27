#include "Tank_Robot.h"

USB Usb;
BTD Btd(&Usb);
PS4BT PS4(&Btd, PAIR);

Tank_Robot::Tank_Robot()
{
    HBridge_Motor motor0 = HBridge_Motor(4, 5, 6);
    HBridge_Motor motor1 = HBridge_Motor(7, 8, 9);
    controller = HBridge_Controller(motor0, motor1);

    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);

    if (Usb.Init() == -1)
    {
        Serial.print(F("\r\nOSC did not start"));
        while (1)
            ;
    }
    Serial.print(F("\r\nPS4 Bluetooth Library Started"));
}

void Tank_Robot::task()
{
    Usb.Task();

    if (PS4.connected())
    {
        uint8_t speedBackwards = PS4.getAnalogButton(L2);
        uint8_t speedForwards = PS4.getAnalogButton(R2);
        int16_t speed = speedForwards - speedBackwards;
        Serial.print("Speed: " + String(speed));
        if (speed > 0)
        {
            Serial.print(" (forwards)");
            controller.forwards();
        }
        else if (speed < 0)
        {
            Serial.print(" (backwards)");
            controller.backwards();
        }
        else
        {
            Serial.print(" (stop)");
            controller.stop();
        }

        int16_t steerX = map(PS4.getAnalogHat(LeftHatX), 0, 255, -255, 255);
        Serial.print("\t\tSteerX: " + String(steerX) + "[" + String((double)abs(steerX) / 255.0) + "]");
        uint8_t enRight;
        uint8_t enLeft;

        if (steerX > 20)
        {
            Serial.print(" (right)");
            enRight = abs(speed) - abs(speed) * ((double)abs(steerX) / 255.0);
            enLeft = abs(speed);
        }
        else if (steerX < -20)
        {
            enRight = abs(speed);
            enLeft = abs(speed) - abs(speed) * ((double)abs(steerX) / 255.0);
        }
        else
        {
            Serial.print(" (straight)");
            enRight = abs(speed);
            enLeft = abs(speed);
        }
        Serial.print("\tenRight: " + String(enRight));
        Serial.print("\tenLeft: " + String(enLeft));
        Serial.println();

        controller.setEnable(enLeft, enRight);
    }
}