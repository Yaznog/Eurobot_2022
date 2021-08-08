#include "Robot.h"

#define NEUTRAL_PIN -1
#define NEUTRAL_OFFSET 0

Robot::Robot()
{
  Serial.println("new Robot");
  
  // Create leg (pinTop, pinMid, pinBot, offsetTop, offsetMid, offsetBot)
  legFrontLeft  = new Leg(3, NEUTRAL_PIN, NEUTRAL_PIN, NEUTRAL_OFFSET, NEUTRAL_OFFSET,  NEUTRAL_OFFSET);
  legFrontRight = new Leg(9, 10, 11, NEUTRAL_OFFSET, NEUTRAL_OFFSET,  NEUTRAL_OFFSET/*15, -4,  -11*/);
  legBackLeft   = new Leg(5, NEUTRAL_PIN, NEUTRAL_PIN, NEUTRAL_OFFSET, NEUTRAL_OFFSET,  NEUTRAL_OFFSET);
  legBackRight  = new Leg(NEUTRAL_PIN, NEUTRAL_PIN, NEUTRAL_PIN, NEUTRAL_OFFSET, NEUTRAL_OFFSET,  NEUTRAL_OFFSET);

  mLastMillis = millis();
  
  WalkOneLeg(-1, 0);
  WalkOneLeg(-1, 1);
  WalkOneLeg(-1, 2);
  WalkOneLeg(-1, 3);
}

Robot::~Robot()
{
  legFrontLeft->~Leg();
  legFrontRight->~Leg();
  legBackLeft->~Leg();
  legBackRight->~Leg();
}

void Robot::MoveOneLegToCoordinate(float x, float y, float z, uint8_t leg)
{
  if(leg==0) 
  {
    legFrontLeft->SetCoordinateTarget(x, y, z);
    legFrontLeft->MoveLegToTarget();
  }
  else if(leg==1) 
  {
    legFrontRight->SetCoordinateTarget(x, -y, z);
    legFrontRight->MoveLegToTarget();
  }
  else if(leg==2) 
  {
    legBackLeft->SetCoordinateTarget(-x, -y, z);
    legBackLeft->MoveLegToTarget();
  }
  else if(leg==3) 
  {
    legBackRight->SetCoordinateTarget(-x, y, z);
    legBackRight->MoveLegToTarget();
  }
}

void Robot::MoveOneLegToCoordinatePolar(float module, float argument, float z, uint8_t leg)
{
  if(leg==0) 
  {
    legFrontLeft->SetCoordinatePolarTarget(module, argument, z);
    legFrontLeft->MoveLegToTarget();
  }
  else if(leg==1) 
  {
    legFrontRight->SetCoordinatePolarTarget(module, -argument, z);
    legFrontRight->MoveLegToTarget();
  }
  else if(leg==2) 
  {
    legBackLeft->SetCoordinatePolarTarget(module, -argument, z);
    legBackLeft->MoveLegToTarget();
  }
  else if(leg==3) 
  {
    legBackRight->SetCoordinatePolarTarget(module, argument, z);
    legBackRight->MoveLegToTarget();
  }
}

void Robot::WalkOneLeg(uint8_t walkStep, uint8_t leg)
{
  if(walkStep==-1)      MoveOneLegToCoordinate(mMovementStop.x,   mMovementStop.y,  mMovementStop.z,  leg);
  else if(walkStep==0)  MoveOneLegToCoordinate(mMovementStep0.x,  mMovementStep0.y, mMovementStep0.z, leg);
  else if(walkStep==1)  MoveOneLegToCoordinate(mMovementStep1.x,  mMovementStep1.y, mMovementStep1.z, leg);
  else if(walkStep==2)  MoveOneLegToCoordinate(mMovementStep2.x,  mMovementStep2.y, mMovementStep2.z, leg);
  else if(walkStep==3)  MoveOneLegToCoordinate(mMovementStep3.x,  mMovementStep3.y, mMovementStep3.z, leg);

  mWalkStep[leg] = walkStep;
}

void Robot::Walk()
{
  if(millis() - mDeltaT >= mLastMillis)
  {
    Serial.print("Walk : ");
    switch(mWalkStep[1])
    {
      case -1:
        WalkOneLeg(1,0);
        WalkOneLeg(1,1);
        WalkOneLeg(1,2);
        WalkOneLeg(1,3);
        Serial.println("-1");
        break;
        
      case 0:
        WalkOneLeg(1,0);
        WalkOneLeg(1,1);
        WalkOneLeg(1,2);
        WalkOneLeg(1,3);
        Serial.println("0");
        break;
        
      case 1:
        WalkOneLeg(2,0);
        WalkOneLeg(2,1);
        WalkOneLeg(2,2);
        WalkOneLeg(2,3);
        Serial.println("1");
        break;
        
      case 2:
        WalkOneLeg(3,0);
        WalkOneLeg(3,1);
        WalkOneLeg(3,2);
        WalkOneLeg(3,3);
        Serial.println("2");
        break;
        
      case 3:
        WalkOneLeg(0,0);
        WalkOneLeg(0,1);
        WalkOneLeg(0,2);
        WalkOneLeg(0,3);
        Serial.println("3");
        break;
    }
    mLastMillis = millis();
  }
}

void Robot::CalibrateOneLeg(uint8_t leg)
{
  if(leg==0)      legFrontLeft->Calibrate_Servo();
  else if(leg==1) legFrontRight->Calibrate_Servo();
  else if(leg==2) legBackLeft->Calibrate_Servo();
  else if(leg==3) legBackRight->Calibrate_Servo();
}

void Robot::CalibrateAllLegs()
{
  legFrontLeft->Calibrate_Servo();
  legFrontRight->Calibrate_Servo();
  legBackLeft->Calibrate_Servo();
  legBackRight->Calibrate_Servo();
}

void Robot::marche(){
  legFrontLeft->marche(1);
  legFrontRight->marche(-1);
}
