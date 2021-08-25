#include "Leg.h"

Leg::Leg(int8_t servoTopPin, int8_t servoMidPin, int8_t servoBotPin, int16_t servoTopOffset, int16_t servoMidOffset, int16_t servoBotOffset, HCPCA9685 *hcpca9685)
{
  Serial.println("new Leg");
  
  mServoTop = new Servo();
  mServoMid = new Servo();
  mServoBot = new Servo();
    
  mServoTop->attach(servoTopPin/*, mServoTopForbiddenValue, 180-mServoTopForbiddenValue*/);
  mServoMid->attach(servoMidPin/*, mServoMidForbiddenValue, 180-mServoMidForbiddenValue*/);
  mServoBot->attach(servoBotPin/*, mServoBotForbiddenValue, 180-mServoBotForbiddenValue*/);

  SetServoOffset(servoTopOffset, servoMidOffset,  servoBotOffset);
  Calibrate_Servo();
}

Leg::~Leg()
{
  mServoTop->~Servo();
  mServoMid->~Servo();
  mServoBot->~Servo();
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
  mServoTop->write(90 + mServoMidOffset);
  mServoMid->write(90 + mServoMidOffset);
  mServoBot->write(90 + mServoBotOffset);
}

void Leg::raiseLeg()
{
  mServoTop->write(90 + mServoMidOffset);
  mServoMid->write(0 + mServoMidOffset);
  mServoBot->write(180 + mServoBotOffset);
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
  mServoTop->write( GetServoTopAngle() * 180/PI + 90 + mServoTopOffset);
  mServoMid->write( GetServoMidAngle() * 180/PI + 90 + mServoMidOffset);
  mServoBot->write( GetServoBotAngle() * 180/PI + 90 + mServoBotOffset);
}


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
  
}
