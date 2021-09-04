#ifndef LEG_H
#define LEG_H

#include <Arduino.h>
//#include <Servo.h>
#include "HCPCA9685.h"

class Leg
{
  public:
  
    Leg(int8_t servoTopPin, int8_t servoMidPin, int8_t servoBotPin, int16_t servoTopOffset, int16_t servoMidOffset, int16_t servoBotOffset, HCPCA9685 *hcpca9685);
    ~Leg();
    
    void SetServoOffset(int16_t servoTopOffset, int16_t servoMidOffset, int16_t servoBotOffset);
    void Calibrate_Servo();
    void raiseLeg();
    
    void SetCoordinateTarget(float x, float y, float z);
    void SetCoordinatePolarTarget(float module, float argument, float z);

    float GetServoTopAngle();
    float GetServoMidAngle();
    float GetServoBotAngle();
    float MaxAngle(float value);
        
    void MoveLegToTarget();

    void marche(int leg);
    
  private:
    /*
    Servo *mServoTop;
    Servo *mServoMid;
    Servo *mServoBot;*/

    HCPCA9685 *mHCPCA9685;
    
    int8_t mServoTopPin;
    int8_t mServoMidPin;
    int8_t mServoBotPin;
  
    int16_t mServoTopOffset = 0;
    int16_t mServoMidOffset = 0;
    int16_t mServoBotOffset = 0;

    const unsigned int mLegTopLength = 35;
    const unsigned int mLegMidLength = 80;
    const unsigned int mLegBotLength = 166;

    const int8_t mServoTopForbiddenValue = 10;
    const int8_t mServoMidForbiddenValue = 30;
    const int8_t mServoBotForbiddenValue = 30;

    float mXCoordinate;
    float mYCoordinate;
    float mZCoordinate;
    float mModuleCoordinate;
    float mArgumentCoordinate;

    int mEtatMarche = 0;
    const int INIT = 90;
    const int ROTATION = 45;
};

#endif
