#include "Leg.h"

Leg::Leg(int8_t servoTopPin, int8_t servoMidPin, int8_t servoBotPin, int16_t servoTopOffset, int16_t servoMidOffset, int16_t servoBotOffset, HCPCA9685 *hcpca9685)
{
  Serial.println("new Leg");

  mHCPCA9685 = hcpca9685;
  
  mServoTopPin = servoTopPin;
  mServoMidPin = servoMidPin;
  mServoBotPin = servoBotPin;
  /*
  mServoTop = new Servo();
  mServoMid = new Servo();
  mServoBot = new Servo();
    
  mServoTop->attach(servoTopPin);
  mServoMid->attach(servoMidPin);
  mServoBot->attach(servoBotPin);*/

  SetServoOffset(servoTopOffset, servoMidOffset,  servoBotOffset);
  Calibrate_Servo();
}

Leg::~Leg()
{
  /*
  mServoTop->~Servo();
  mServoMid->~Servo();
  mServoBot->~Servo();*/
}

void Leg::SetServoOffset(int16_t servoTopOffset, int16_t servoMidOffset, int16_t servoBotOffset)
{
  mServoTopOffset = servoTopOffset;
  mServoMidOffset = servoMidOffset;
  mServoBotOffset = servoBotOffset;
}

void Leg::Calibrate_Servo()
{
  //Serial.println("Calibrate_Servo");
  mHCPCA9685->Servo(mServoTopPin, 180);
  mHCPCA9685->Servo(mServoMidPin, 180);
  mHCPCA9685->Servo(mServoBotPin, 180);
  /*
  mServoTop->write(90 + mServoMidOffset);
  mServoMid->write(90 + mServoMidOffset);
  mServoBot->write(90 + mServoBotOffset);*/
}

void Leg::raiseLeg()
{
  mHCPCA9685->Servo(mServoTopPin, 90 + mServoMidOffset);
  mHCPCA9685->Servo(mServoMidPin, 0 + mServoMidOffset);
  mHCPCA9685->Servo(mServoBotPin, 180 + mServoBotOffset);
  /*
  mServoTop->write(90 + mServoMidOffset);
  mServoMid->write(0 + mServoMidOffset);
  mServoBot->write(180 + mServoBotOffset);*/
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

  mXCoordinate = cos(mArgumentCoordinate) * mModuleCoordinate;
  mYCoordinate = sin(mArgumentCoordinate) * mModuleCoordinate;
}

// Angles----------------------------------------------------

float Leg::GetServoTopAngle()
{
  return MaxAngle( mArgumentCoordinate );
}

float Leg::GetServoMidAngle()
{
  float c = sqrt( (square(mModuleCoordinate) + square(mZCoordinate)) );
  float error = atan(mZCoordinate/mModuleCoordinate);
  return MaxAngle( error - acos( ( -square(mLegBotLength) + square(mLegMidLength) + square(c) ) / (2*mLegMidLength*c) ) );
}

float Leg::GetServoBotAngle()
{
  float c = sqrt( (square(mModuleCoordinate) + square(mZCoordinate)) );
  return MaxAngle( (-PI/2) + acos( ( -square(c) + square(mLegMidLength) + square(mLegBotLength) ) / (2*mLegMidLength*mLegBotLength) ) );
}

float Leg::MaxAngle(float value)
{
  if(value<(-PI/2)) return (-PI/2);
  if(value>(PI/2)) return (PI/2);
  return value;
}

// Movement Function----------------------------------------

void Leg::MoveLegToTarget()
{
  mHCPCA9685->Servo(mServoTopPin, (GetServoTopAngle() * 180/PI + 90)*2 + mServoTopOffset );
  mHCPCA9685->Servo(mServoMidPin, (GetServoMidAngle() * 180/PI + 90)*2 + mServoMidOffset );
  mHCPCA9685->Servo(mServoBotPin, (GetServoBotAngle() * 180/PI + 90)*2 + mServoBotOffset );

  /*
  mServoTop->write( GetServoTopAngle() * 180/PI + 90 + mServoTopOffset);
  mServoMid->write( GetServoMidAngle() * 180/PI + 90 + mServoMidOffset);
  mServoBot->write( GetServoBotAngle() * 180/PI + 90 + mServoBotOffset);*/
}

/*
void Leg::marche(int leg)
{

  switch(mEtatMarche){
    case 0: 
      mServoTop->write(INIT + 0);
      mEtatMarche++;
      break;

    case 1:
      mServoTop->write(INIT + 0);
      mEtatMarche++;
      break;

      case 2:
      mServoTop->write(INIT - (leg * ROTATION));
      mEtatMarche++;
      break;
      
      case 3:
      mServoTop->write(INIT - (leg * ROTATION));
      mEtatMarche++;
      break;
      
      case 4:
      mServoTop->write(INIT + 0);
      mEtatMarche++;
      break;
      
      case 5:
      mServoTop->write(INIT + (leg * ROTATION));
      mEtatMarche++;
      break;
      
      case 6:
      mServoTop->write(INIT + 0);
      mEtatMarche = 0;
      break;

  }
  
}*/
