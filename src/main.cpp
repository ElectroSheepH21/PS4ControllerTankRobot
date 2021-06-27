#include <Arduino.h>
#include <PS4BT.h>
#include <usbhub.h>
#include <SPI.h>

USB Usb;
BTD Btd(&Usb);
PS4BT PS4(&Btd, PAIR);

void forwards()
{
  digitalWrite(4, 1);
  digitalWrite(5, 0);
  digitalWrite(7, 1);
  digitalWrite(8, 0);
}

void backwards()
{
  digitalWrite(4, 0);
  digitalWrite(5, 1);
  digitalWrite(7, 0);
  digitalWrite(8, 1);
}

void stop()
{
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  digitalWrite(7, 0);
  digitalWrite(8, 0);
}

void setEnable(uint8_t enA, uint8_t enB)
{
  analogWrite(6, enA);
  analogWrite(9, enB);
}

void setup()
{
  Serial.begin(115200);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  if (Usb.Init() == -1)
  {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
}

void loop()
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
      forwards();
    }
    else if (speed < 0)
    {
      Serial.print(" (backwards)");
      backwards();
    }
    else
    {
      Serial.print(" (stop)");
      stop();
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

    setEnable(enLeft, enRight);
  }
}