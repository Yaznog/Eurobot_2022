#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include "Leg.h"
#include "Adafruit_PWMServoDriver.h"

#define LEG_FRONT_LEFT 0
#define LEG_FRONT_RIGHT 1
#define LEG_BACK_LEFT 2
#define LEG_BACK_RIGHT 3

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
  
    Robot(Adafruit_PWMServoDriver* pwm);
    ~Robot();

    void MoveOneLegToCoordinate(float x, float y, float z, uint8_t leg);
    void MoveOneLegToCoordinatePolar(float module, float argument, float z, uint8_t leg);
    void raiseOneLeg(uint8_t leg);
    void raiseAllLegs();
    void WalkOneLeg(uint8_t walkStep, uint8_t leg);
    void WalkOneLegPolar(uint8_t walkPolarStep, uint8_t leg);
    void walkForward();
    void walkRearward();
    void rotateLeftSide();
    void rotateRightSide();

    void CalibrateOneLeg(uint8_t leg);
    void CalibrateAllLegs();

    void marche();
    
  private:
  
    Leg *legFrontLeft;
    Leg *legFrontRight;
    Leg *legBackLeft;
    Leg *legBackRight;

    const Coordinate mMovementStop{85,35,120,0,0};// Millieu bas
/*
    const Coordinate mMovementStep0{50,70,120,0,0};// Arrière bas
    const Coordinate mMovementStep1{85,35,80,0,0};// Millieu haut
    const Coordinate mMovementStep2{120,0,120,0,0};// Avant bas
    const Coordinate mMovementStep3{85,35,120,0,0};// Millieu bas*/
    
    const Coordinate mMovementStep0{40+6.5,80+6.5,120,0,0};// Arrière bas
    const Coordinate mMovementStep1{125,45,80,0,0};// Millieu haut
    const Coordinate mMovementStep2{160+6.5,-40+6.5,120,0,0};// Avant bas
    const Coordinate mMovementStep3{125,45,120,0,0};// Millieu bas

    const Coordinate mMovementPolarStop{0,0,120,90,0};// Millieu bas

    const Coordinate mMovementPolarStep0{0,0,120,90,-PI/4};// Arrière bas
    const Coordinate mMovementPolarStep1{0,0,80,90,0};// Millieu haut
    const Coordinate mMovementPolarStep2{0,0,120,90,PI/4};// Avant bas
    const Coordinate mMovementPolarStep3{0,0,120,90,0};// Millieu bas

    const int mDeltaT = 800;// Time between 2 movements in milliseconds
    float mLastMillis;

    int8_t mStartingStep[4];
    int8_t mWalkStep[4];// One foreache leg
    int8_t mWalkPolarStep[4];// One foreache leg
    int8_t mStoppingStep[4];
};

#endif
