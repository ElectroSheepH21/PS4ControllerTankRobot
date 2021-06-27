#include <Arduino.h>
#include "TankRobot.h"

Tank_Robot robot;

void setup()
{
  Serial.begin(115200);

  robot = Tank_Robot();
}

void loop()
{
  robot.task();
}