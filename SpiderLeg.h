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
    SpiderLeg(
      byte servoMountPin,
      byte servoHipPin,
      byte servoKneePin,
      byte servoSpeed
    );
    void moveMountServo(short mountServoAngle);
    void moveHipServo(short hipServoAngle);
    void moveKneeServo(short kneeServoAngle);
    void move(
      short mountServoAngle,
      short hipServoAngle,
      short kneeServoAngle,
      float speedMod,
      bool isSync = false,
    );
    void move(
      short mountServoAngle,
      short hipServoAngle,
      short kneeServoAngle
    );

    bool isMountServoReady();
    bool isHipServoReady();
    bool isKneeServoReady();
    bool isLegReady();

    void standBy(byte orientation, unsigned int standByDelay);
    void standBy(byte orientation);
    // The less speed value, the faster leg moves
    void setSpeed(byte speed);
    void stepForward(byte numberOfLegs = 1);
    void stepBackward();

    static const byte forwardLeft = 0;
    static const byte forwardRight = 1;
    static const byte backwardLeft = 2;
    static const byte backwardRight = 3;

    // TODO
    // String left[2] = { "middle", "left" };
    // String right[2] = { "middle", "right" };
  
  private:
    byte _servoMountPin;
    byte _servoHipPin;
    byte _servoKneePin;
    Multiservo _mountServo;
    Multiservo _hipServo;
    Multiservo _kneeServo;

    byte _servoSpeed = 15;
    short _mountServoPosition = 90;
    short _hipServoPosition = 90;
    short _kneeServoPosition = 90;

    bool _isMountServoReady = true;
    bool _isHipServoReady = true;
    bool _isKneeServoReady = true;

    byte _stepStage = 0;

    short _mountIncZeroCount = 0;
    short _hipIncZeroCount = 0;
    short _kneeIncZeroCount = 0;

    byte _orientation = 0;
};

#endif
