# SpiderLeg
Library to control spider robot leg


## What it for?
Main purpose is to control spider-type robot leg of three servo motors.


## How it works?
Including this lib, you will got access to SpiderLeg class


To initialize leg, you have to pass servo motors pins.

1st argument - mount pin (closest servo to robot body)

2nd argument - hip pin (middle servo)

3rd argument - knee pin

4th argument - servo speed (delay in ms between servo moves, the less the faster) : optional

Example:
```
SpiderLeg leg1(17, 16, 15);
```


## Main public methods:

### move(short mountServoAngle, short hipServoAngle, short kneeServoAngle, float speedMod, bool isSync = false)
Method to set custom position for each servo in leg

1st, 2nd, 3rd arguments - servo positions

4th argument - modificator of speed, 1.0 means that delays will be same as servo speed

5th argument - is all servos in leg moves in sync (all three servos start and end moving in same time)

### standBy(byte orientation, unsigned int standByDelay)

### setSpeed(byte speed)

### stepForward(byte numberOfLegs = 1)