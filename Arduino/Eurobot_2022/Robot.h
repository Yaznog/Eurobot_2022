#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include "Leg.h"

struct Coordinate
{
  float x;
  float y;
  float z;
  float module;
  float argument;
};

class Robot
{
  public:
  
    Robot();
    ~Robot();

    void MoveOneLegToCoordinate(float x, float y, float z, uint8_t leg);
    void MoveOneLegToCoordinatePolar(float module, float argument, float z, uint8_t leg);
    void WalkOneLeg(uint8_t walkStep, uint8_t leg);
    void GotoCoordinate(float x, float y, float teta);

    void Walk();

    void CalibrateOneLeg(uint8_t leg);
    void CalibrateAllLegs();

    void marche();
    
  private:
  
    Leg *legFrontLeft;
    Leg *legFrontRight;
    Leg *legBackLeft;
    Leg *legBackRight;

    const Coordinate mMovementStop{0,80,150,0,0};

    const Coordinate mMovementStep0{-80,0,150,0,0};
    const Coordinate mMovementStep1{-40,40,120,0,0};
    const Coordinate mMovementStep2{0,80,150,0,0};
    const Coordinate mMovementStep3{-40,40,150,0,0};

    const int mDeltaT = 500;
    float mLastMillis;

    int8_t mWalkStep[4];
};

#endif
