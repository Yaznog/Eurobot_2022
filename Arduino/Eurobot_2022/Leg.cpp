#include "Leg.h"

Leg::Leg(int8_t servoTopPin, int8_t servoMidPin, int8_t servoBotPin, int16_t servoTopOffset, int16_t servoMidOffset, int16_t servoBotOffset, Adafruit_PWMServoDriver* pwm)
{
  Serial.println("new Leg");

  mPwm = pwm;
  
  mServoTopPin = servoTopPin;
  mServoMidPin = servoMidPin;
  mServoBotPin = servoBotPin;

  mServoTopOffset = servoTopOffset;
  mServoMidOffset = servoMidOffset;
  mServoBotOffset = servoBotOffset;

  //SetServoOffset(servoTopOffset, servoMidOffset,  servoBotOffset);
  Calibrate_Servo();
}

Leg::~Leg()
{
}

void Leg::SetServoOffset(int16_t servoTopOffset, int16_t servoMidOffset, int16_t servoBotOffset)
{
  //mServoTopOffset = servoTopOffset;
  //mServoMidOffset = servoMidOffset;
  //mServoBotOffset = servoBotOffset;
}

void Leg::Calibrate_Servo()
{
  //Serial.println("Calibrate_Servo");
  mPwm->setPWM(mServoTopPin, 0, map(90, 0, 180, SERVOMIN, SERVOMAX)+ mServoTopOffset);
  mPwm->setPWM(mServoMidPin, 0, map(90, 0, 180, SERVOMIN, SERVOMAX)+ mServoMidOffset);
  mPwm->setPWM(mServoBotPin, 0, map(90, 0, 180, SERVOMIN, SERVOMAX)+ mServoBotOffset);
}

void Leg::raiseLeg(uint8_t leg)
{
  mPwm->setPWM(mServoTopPin, 0, map(90, 0, 180, SERVOMIN, SERVOMAX)+ mServoTopOffset);
 
  //mHCPCA9685->Servo(mServoTopPin, 180 + mServoMidOffset);
  //int16_t highValue = 360;
  //int16_t lowValue = 0;
  
  if(leg==LEG_FRONT_LEFT || leg==LEG_BACK_RIGHT)
  {
    mPwm->setPWM(mServoMidPin, 0, map(180, 0, 180, SERVOMIN, SERVOMAX)+ mServoMidOffset);
    mPwm->setPWM(mServoBotPin, 0, map(0, 0, 180, SERVOMIN, SERVOMAX)+ mServoBotOffset);
    //mHCPCA9685->Servo(mServoMidPin, -(lowValue - 180) + 180 + mServoMidOffset);
    //mHCPCA9685->Servo(mServoBotPin, -(highValue - 180) + 180 + mServoBotOffset);
  }
  else if(leg==LEG_FRONT_RIGHT || leg==LEG_BACK_LEFT)
  {
    mPwm->setPWM(mServoMidPin, 0, map(0, 0, 180, SERVOMIN, SERVOMAX)+ mServoMidOffset);
    mPwm->setPWM(mServoBotPin, 0, map(180, 0, 180, SERVOMIN, SERVOMAX)+ mServoBotOffset);
    //mHCPCA9685->Servo(mServoMidPin, lowValue + mServoMidOffset);
    //mHCPCA9685->Servo(mServoBotPin, highValue + mServoBotOffset);
  }
}

// Coordinates---------------------------------------------------

void Leg::SetCoordinateTarget(float x, float y, float z)
{
  mXCoordinate = x;
  mYCoordinate = y;
  mZCoordinate = z;

  mModuleCoordinate = sqrt( square(x) + square(y) ) ;
  mArgumentCoordinate = asin(y/mModuleCoordinate);
}

void Leg::SetCoordinatePolarTarget(float module, float argument, float z)
{
  mModuleCoordinate = module;
  mArgumentCoordinate = argument;
  mZCoordinate = z;

  mXCoordinate = cos(mArgumentCoordinate) * (mModuleCoordinate - mLegTopLength);
  mYCoordinate = sin(mArgumentCoordinate) * (mModuleCoordinate - mLegTopLength);
}

// Angles----------------------------------------------------

float Leg::GetServoTopAngle()
{
  return MaxAngle( mArgumentCoordinate );
}

float Leg::GetServoMidAngle()
{
  float c = sqrt( (square(mModuleCoordinate - mLegTopLength) + square(mZCoordinate)) );
  float error = atan(mZCoordinate/(mModuleCoordinate - mLegTopLength));
  return MaxAngle( error - acos( ( -square(mLegBotLength) + square(mLegMidLength) + square(c) ) / (2*mLegMidLength*c) ) );
}

float Leg::GetServoBotAngle()
{
  float c = sqrt( (square(mModuleCoordinate - mLegTopLength) + square(mZCoordinate)) );
  return MaxAngle( (-PI/2) + acos( ( -square(c) + square(mLegMidLength) + square(mLegBotLength) ) / (2*mLegMidLength*mLegBotLength) ) );
}

float Leg::MaxAngle(float value)
{
  if(value<(-PI/2)) return (-PI/2);
  if(value>(PI/2)) return (PI/2);
  return value;
}

// Movement Function----------------------------------------

void Leg::MoveLegToTarget(uint8_t leg)
{ 
  mPwm->setPWM(mServoTopPin, 0, map((GetServoTopAngle() * 180/PI + 90), 0, 180, SERVOMIN, SERVOMAX) + mServoTopOffset);
  Serial.println(GetServoTopAngle());
  Serial.println(map(GetServoTopAngle() + 90, 0, 180, SERVOMIN, SERVOMAX));
  /*
  mHCPCA9685->Servo(mServoTopPin, (GetServoTopAngle() * 180/PI + 90)*2 + mServoTopOffset );
  mHCPCA9685->Servo(mServoMidPin, (GetServoMidAngle() * 180/PI + 90)*2 + mServoMidOffset );
  mHCPCA9685->Servo(mServoBotPin, (GetServoBotAngle() * 180/PI + 90)*2 + mServoBotOffset );*/

  //mHCPCA9685->Servo(mServoTopPin, (GetServoTopAngle() * 180/PI + 90)*2 + mServoTopOffset );
  
  if(leg==LEG_FRONT_LEFT || leg==LEG_BACK_RIGHT)
  {
    mPwm->setPWM(mServoMidPin, 0, map(90 - (GetServoBotAngle() * 180/PI ), 0, 180, SERVOMIN, SERVOMAX)+ mServoMidOffset);
    mPwm->setPWM(mServoBotPin, 0, map(90 - (GetServoBotAngle() * 180/PI ), 0, 180, SERVOMIN, SERVOMAX)+ mServoBotOffset);
    //mPwm->setPWM(mServoBotPin, 0, map(90 - GetServoBotAngle(), 0, 180, SERVOMIN, SERVOMAX)+ mServoBotOffset);
    //mHCPCA9685->Servo(mServoMidPin
    //mHCPCA9685->Servo(mServoBotPin, -((GetServoBotAngle() * 180/PI + 90)*2 - 180) + 180 + mServoBotOffset);
  }
  else if(leg==LEG_FRONT_RIGHT || leg==LEG_BACK_LEFT)
  {
    mPwm->setPWM(mServoMidPin, 0, map((GetServoBotAngle() * 180/PI ) + 90, 0, 180, SERVOMIN, SERVOMAX)+ mServoMidOffset);
    mPwm->setPWM(mServoBotPin, 0, map((GetServoBotAngle() * 180/PI ) + 90, 0, 180, SERVOMIN, SERVOMAX)+ mServoBotOffset);
    //mHCPCA9685->Servo(mServoMidPin, (GetServoMidAngle() * 180/PI + 90)*2 + mServoMidOffset );
    //mHCPCA9685->Servo(mServoBotPin, (GetServoBotAngle() * 180/PI + 90)*2 + mServoBotOffset );
  }
  /*
  mServoTop->write( GetServoTopAngle() * 180/PI + 90 + mServoTopOffset);
  mServoMid->write( GetServoMidAngle() * 180/PI + 90 + mServoMidOffset);
  mServoBot->write( GetServoBotAngle() * 180/PI + 90 + mServoBotOffset);*/
}
