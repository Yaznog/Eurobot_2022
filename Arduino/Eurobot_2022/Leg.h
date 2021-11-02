#ifndef LEG_H
#define LEG_H

#include <Arduino.h>
#include "Adafruit_PWMServoDriver.h"

#define LEG_FRONT_LEFT 0
#define LEG_FRONT_RIGHT 1
#define LEG_BACK_LEFT 2
#define LEG_BACK_RIGHT 3

#define SERVOMIN  90 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  460 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50

class Leg
{
  public:
  
    Leg(int8_t servoTopPin, int8_t servoMidPin, int8_t servoBotPin, int16_t servoTopOffset, int16_t servoMidOffset, int16_t servoBotOffset, Adafruit_PWMServoDriver* pwm);
    ~Leg();
    
    void SetServoOffset(int16_t servoTopOffset, int16_t servoMidOffset, int16_t servoBotOffset);
    void Calibrate_Servo();
    void raiseLeg(uint8_t leg);
    
    void SetCoordinateTarget(float x, float y, float z);
    void SetCoordinatePolarTarget(float module, float argument, float z);

    float GetServoTopAngle();
    float GetServoMidAngle();
    float GetServoBotAngle();
    float MaxAngle(float value);
        
    void MoveLegToTarget(uint8_t leg);

    void marche(int leg);
    
  private:

    Adafruit_PWMServoDriver* mPwm;
    
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
