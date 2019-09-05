#include "Arduino.h"
#include "Wire.h"
#include "Multiservo.h"
#include "SpiderLeg.h"

SpiderLeg::SpiderLeg(byte servoMountPin, byte servoHipPin, byte servoKneePin) {
  Wire.begin(); // Переместить в библиотеку движения или в общий скетч
  _servoMountPin = servoMountPin;
  _servoHipPin = servoHipPin;
  _servoKneePin = servoKneePin;
  _mountServo.attach(_servoMountPin);
  _hipServo.attach(_servoHipPin);
  _kneeServo.attach(_servoKneePin);
}

void SpiderLeg::moveMountServo(short mountServoAngle) {
  _mountServo.write(mountServoAngle);
}

void SpiderLeg::moveHipServo(short hipServoAngle) {
  _mountServo.write(hipServoAngle);
}

void SpiderLeg::moveKneeServo(short kneeServoAngle) {
  _mountServo.write(kneeServoAngle);
}

void SpiderLeg::moveLeg(short mountServoAngle, short hipServoAngle, short kneeServoAngle) {
  moveMountServo(mountServoAngle);
  moveHipServo(hipServoAngle);
  moveKneeServo(kneeServoAngle);
}
