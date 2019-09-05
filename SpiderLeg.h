#ifndef SpiderLeg_h
#define SpiderLeg_h

#include "Arduino.h"

class SpiderLeg {
  public:
    SpiderLeg(
      byte servoMountPin,
      byte servoHipPin,
      byte servoKneePin
    );
    void moveMountServo(short mountServoAngle);
    void moveHipServo(short hipServoAngle);
    void moveKneeServo(short kneeServoAngle);
    void moveLeg(
      short mountServoAngle,
      short hipServoAngle,
      short kneeServoAngle
    );
  
  private:
    byte _servoMountPin;
    byte _servoHipPin;
    byte _servoKneePin;
    Multiservo _mountServo;
    Multiservo _hipServo;
    Multiservo _kneeServo;
};

#endif
