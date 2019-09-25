#include "Arduino.h"
#include "Wire.h"
#include "Multiservo.h"
#include "SpiderLeg.h"

SpiderLeg::SpiderLeg(byte servoMountPin, byte servoHipPin, byte servoKneePin) {
  // Wire.begin();
  _servoMountPin = servoMountPin;
  _servoHipPin = servoHipPin;
  _servoKneePin = servoKneePin;
  _mountServo.attach(_servoMountPin);
  _hipServo.attach(_servoHipPin);
  _kneeServo.attach(_servoKneePin);
}

SpiderLeg::SpiderLeg(byte servoMountPin, byte servoHipPin, byte servoKneePin, byte servoSpeed) {
  // Wire.begin();
  _servoMountPin = servoMountPin;
  _servoHipPin = servoHipPin;
  _servoKneePin = servoKneePin;
  _servoSpeed = servoSpeed;
  _mountServo.attach(_servoMountPin);
  _hipServo.attach(_servoHipPin);
  _kneeServo.attach(_servoKneePin);
}

void SpiderLeg::moveMountServo(short mountServoAngle) {
  _mountServo.write(mountServoAngle);
  _mountServoPosition = mountServoAngle;
}

void SpiderLeg::moveHipServo(short hipServoAngle) {
  _hipServo.write(hipServoAngle);
  _hipServoPosition = hipServoAngle;
}

void SpiderLeg::moveKneeServo(short kneeServoAngle) {
  _kneeServo.write(kneeServoAngle);
  _kneeServoPosition = kneeServoAngle;
}

bool SpiderLeg::isMountServoReady() {
  return _isMountServoReady;
}

bool SpiderLeg::isHipServoReady() {
  return _isHipServoReady;
}

bool SpiderLeg::isKneeServoReady() {
  return _isKneeServoReady;
}

bool SpiderLeg::isLegReady() {
  return isHipServoReady() && isKneeServoReady() && isMountServoReady();
}

void SpiderLeg::move(short mountServoAngle, short hipServoAngle, short kneeServoAngle, float speedMod, bool isSync = false) {
  short nextMountPosition = _mountServoPosition;
  short nextHipPosition = _hipServoPosition;
  short nextKneePosition = _kneeServoPosition;

  _isMountServoReady = false;
  _isHipServoReady = false;
  _isKneeServoReady = false;

  short mountDif = abs(_mountServoPosition - mountServoAngle);
  short hipDif = abs(_hipServoPosition - hipServoAngle);
  short kneeDif = abs(_kneeServoPosition - kneeServoAngle);

  byte mountInc = 1;
  byte hipInc = 1;
  byte kneeInc = 1;

  if (isSync) {
    if (mountDif >= hipDif && mountDif >= kneeDif) {
      mountInc = 1;
      if (hipDif < mountDif) {
        short mountHipDif = (short)ceil((float)mountDif / (float)hipDif);
        if (_hipIncZeroCount + 1 >= mountHipDif) {
          _hipIncZeroCount = 0;
          hipInc = 1;
        } else {
          _hipIncZeroCount ++;
          hipInc = 0;
        }
      }
      if (kneeDif < mountDif) {
        short mountKneeDif = (short)ceil((float)mountDif / (float)kneeDif);
        if (_kneeIncZeroCount + 1 >= mountKneeDif) {
          _kneeIncZeroCount = 0;
          kneeInc = 1;
        } else {
          _kneeIncZeroCount ++;
          kneeInc = 0;
        }
      }
    } else if (hipDif >= mountDif && hipDif >= kneeDif) {
      hipInc = 1;
      if (mountDif < hipDif) {
        short hipMountDif = (short)ceil((float)hipDif / (float)mountDif);
        if (_mountIncZeroCount + 1 >= hipMountDif) {
          _mountIncZeroCount = 0;
          mountInc = 1;
        } else {
          _mountIncZeroCount ++;
          mountInc = 0;
        }
      }
      if (kneeDif < hipDif) {
        short hipKneeDif = (short)ceil((float)hipDif / (float)kneeDif);
        if (_kneeIncZeroCount + 1 >= hipKneeDif) {
          _kneeIncZeroCount = 0;
          kneeInc = 1;
        } else {
          _kneeIncZeroCount ++;
          kneeInc = 0;
        }
      }
    } else if (kneeDif >= hipDif && kneeDif >= mountDif) {
      kneeInc = 1;
      if (hipDif < kneeDif) {
        short kneeHipDif = (short)ceil((float)kneeDif / (float)hipDif);
        if (_hipIncZeroCount + 1 >= kneeHipDif) {
          _hipIncZeroCount = 0;
          hipInc = 1;
        } else {
          _hipIncZeroCount ++;
          hipInc = 0;
        }
      }
      if (mountDif < kneeDif) {
        short kneeMountDif = (short)ceil((float)kneeDif / (float)mountDif);
        if (_mountIncZeroCount + 1 >= kneeMountDif) {
          _mountIncZeroCount = 0;
          mountInc = 1;
        } else {
          _mountIncZeroCount ++;
          mountInc = 0;
        }
      }
    }
  }

  // Calculate next position for servo
  if (mountServoAngle > _mountServoPosition) {
    nextMountPosition = _mountServoPosition + mountInc;
  } else if (mountServoAngle < _mountServoPosition) {
    nextMountPosition = _mountServoPosition - mountInc;
  } else {
    _isMountServoReady = true;
  }

  if (hipServoAngle > _hipServoPosition) {
    nextHipPosition = _hipServoPosition + hipInc;
  } else if (hipServoAngle < _hipServoPosition) {
    nextHipPosition = _hipServoPosition - hipInc;
  } else {
    _isHipServoReady = true;
  }

  if (kneeServoAngle > _kneeServoPosition) {
    nextKneePosition = _kneeServoPosition + kneeInc;
  } else if (kneeServoAngle < _kneeServoPosition) {
    nextKneePosition = _kneeServoPosition - kneeInc;
  } else {
    _isKneeServoReady = true;
  }

  moveMountServo(nextMountPosition);
  moveHipServo(nextHipPosition);
  moveKneeServo(nextKneePosition);

  delay((int)((float)_servoSpeed * speedMod));
}

void SpiderLeg::move(short mountServoAngle, short hipServoAngle, short kneeServoAngle) {
  move(mountServoAngle, hipServoAngle, kneeServoAngle, false, 1.0);
}

void SpiderLeg::standBy(byte orientation, unsigned int standByDelay) {
  _orientation = orientation;
  move(90, 90, 90);
  delay(standByDelay);
}

void SpiderLeg::standBy(byte orientation) {
  standBy(orientation, 1000);
}

void SpiderLeg::setSpeed(byte speed) {
  _servoSpeed = speed;
}

// TODO
// Добавить аргумент servoDelay, чтоб первый шаг роисходил с задержкой(для шагания нескольких ног)
void SpiderLeg::stepForward(byte numberOfLegs = 1) {
  const byte mountPositions[][4] = {
    { 90, 45, 45, 135 }, // Forward Left
    { 90, 135, 135, 45 }, // Forward Right
    { 90, 45, 45, 135 }, // Backward Left
    { 90, 135, 135, 45 } // Backward Right
  };
  const byte hipPositions[][4] = {
    { 60, 115, 135, 95 },
    { 60, 115, 135, 95 },
    { 60, 30, 60, 95 },
    { 60, 30, 60, 95 }
  };
  const byte kneePositions[][4] = {
    { 100, 145, 145, 50 },
    { 100, 145, 145, 50 },
    { 50, 45, 45, 145 },
    { 50, 45, 45, 145 }
  };

  const bool isSync = true;
  // В данном шаге последний аргумент это время на змеле, остальные - время в воздухе
  const float stepSpeedMods[] = { 1.0, 1.0, 1.0, (float)numberOfLegs * 3 - 3 };

  if (_stepStage > 3) {
    _stepStage = 0;
  }

  move(
    mountPositions[_orientation][_stepStage],
    hipPositions[_orientation][_stepStage],
    kneePositions[_orientation][_stepStage],
    isSync,
    stepSpeedMods[_stepStage]

  );

  if (isLegReady()) {
    _stepStage ++;
  }
}

// Проверить
void SpiderLeg::stepBackward() {
  const byte mountPositions[][4] = {
    { 90, 135, 135, 45 }, // Forward Left
    { 90, 45, 45, 135 }, // Forward Right
    { 90, 135, 135, 45 }, // Backward Left
    { 90, 45, 45, 135 } // Backward Right
  };
  const byte hipPositions[][4] = {
    { 60, 30, 60, 95 },
    { 60, 30, 60, 95 },
    { 60, 115, 135, 95 },
    { 60, 115, 135, 95 }
  };
  const byte kneePositions[][4] = {
    { 50, 45, 45, 145 },
    { 50, 45, 45, 145 },
    { 100, 145, 145, 50 },
    { 100, 145, 145, 50 }
  };

  if (_stepStage > 3) {
    _stepStage = 0;
  }

  move(
    mountPositions[_orientation][_stepStage],
    hipPositions[_orientation][_stepStage],
    kneePositions[_orientation][_stepStage]
  );

  if (isLegReady()) {
    _stepStage ++;
  }
}
