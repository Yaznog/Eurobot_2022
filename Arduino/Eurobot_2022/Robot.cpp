#include "Robot.h"

#define NEUTRAL_PIN -1
#define NEUTRAL_OFFSET 0

Robot::Robot(HCPCA9685 *hcpca9685)
{
  //Serial.println("new Robot");
  
  // Create leg (pinTop, pinMid, pinBot, offsetTop, offsetMid, offsetBot, hcpca9685)
  legFrontLeft  = new Leg(2, 3, 4, NEUTRAL_OFFSET, NEUTRAL_OFFSET,  NEUTRAL_OFFSET, hcpca9685);
  legFrontRight = new Leg(5, 6, 7, NEUTRAL_OFFSET, NEUTRAL_OFFSET,  NEUTRAL_OFFSET, hcpca9685);
  legBackLeft   = new Leg(NEUTRAL_PIN, NEUTRAL_PIN, NEUTRAL_PIN, NEUTRAL_OFFSET, NEUTRAL_OFFSET,  NEUTRAL_OFFSET, hcpca9685);
  legBackRight  = new Leg(NEUTRAL_PIN, NEUTRAL_PIN, NEUTRAL_PIN, NEUTRAL_OFFSET, NEUTRAL_OFFSET,  NEUTRAL_OFFSET, hcpca9685);

  mLastMillis = millis();
  /*
  WalkOneLeg(-1, 0);
  WalkOneLeg(-1, 1);
  WalkOneLeg(-1, 2);
  WalkOneLeg(-1, 3);*/
  
  WalkOneLeg(0, LEG_FRONT_LEFT);
  WalkOneLeg(0, 1);
  WalkOneLeg(0, 2);
  WalkOneLeg(0, 3);
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
  if(leg==LEG_FRONT_LEFT) 
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
  if(leg==LEG_FRONT_LEFT) 
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

void Robot::raiseOneLeg(uint8_t leg)
{
  if(leg==LEG_FRONT_LEFT)      legFrontLeft->raiseLeg();
  else if(leg==1) legFrontRight->raiseLeg();
  else if(leg==2) legBackLeft->raiseLeg();
  else if(leg==3) legBackRight->raiseLeg();
}

void Robot::raiseAllLegs()
{
  legFrontLeft->raiseLeg();
  legFrontRight->raiseLeg();
  legBackLeft->raiseLeg();
  legBackRight->raiseLeg();
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

void Robot::walkForward()
{
  if(millis() - mDeltaT >= mLastMillis)
  {
    Serial.println("etape");
  Serial.println(mWalkStep[1]);
    switch(mWalkStep[LEG_FRONT_LEFT])
    {/*
      case -1:// Millieu bas
        WalkOneLeg(1,0);
        WalkOneLeg(2,1);
        WalkOneLeg(3,2);
        WalkOneLeg(0,3);
        break;*/
        
      case 0:// Arrière bas
        WalkOneLeg(1,LEG_FRONT_LEFT);
        WalkOneLeg(3,1);
        WalkOneLeg(0,2);
        WalkOneLeg(2,3);
        break;
        
      case 1:// Millieu haut
        WalkOneLeg(2,LEG_FRONT_LEFT);
        WalkOneLeg(0,1);
        WalkOneLeg(1,2);
        WalkOneLeg(3,3);
        break;
        
      case 2:// Avant bas
        WalkOneLeg(3,LEG_FRONT_LEFT);
        WalkOneLeg(1,1);
        WalkOneLeg(2,2);
        WalkOneLeg(0,3);
        break;
        
      case 3:// Millieu bas
        WalkOneLeg(0,LEG_FRONT_LEFT);
        WalkOneLeg(2,1);
        WalkOneLeg(3,2);
        WalkOneLeg(1,3);
        break;
    }
    //Serial.println(mWalkStep[1]);
    mLastMillis = millis();
  }
}


void Robot::walkRearward()
{/*
  if(millis() - mDeltaT >= mLastMillis)
  {
    switch(mWalkStep[1])
    {
      case -1:// Millieu bas
        WalkOneLeg(1,0);
        WalkOneLeg(2,1);
        WalkOneLeg(1,2);
        WalkOneLeg(3,3);
        //Serial.println("-1");
        break;
        
      case 0:// Arrière bas
        WalkOneLeg(3,0);
        WalkOneLeg(2,1);
        WalkOneLeg(0,2);
        WalkOneLeg(3,3);
        //Serial.println("0");
        break;
        
      case 1:// Millieu haut
        WalkOneLeg(0,0);
        WalkOneLeg(3,1);
        WalkOneLeg(1,2);
        WalkOneLeg(0,3);
        //Serial.println("1");
        break;
        
      case 2:// Avant bas
        WalkOneLeg(1,0);
        WalkOneLeg(0,1);
        WalkOneLeg(2,2);
        WalkOneLeg(1,3);
        //Serial.println("2");
        break;
        
      case 3:// Millieu bas
        WalkOneLeg(2,0);
        WalkOneLeg(1,1);
        WalkOneLeg(3,2);
        WalkOneLeg(2,3);
        //Serial.println("3");
        break;
    }
    mLastMillis = millis();
  }*/
}

void Robot::rotateLeftSide()
{
  
}

void Robot::rotateRightSide()
{
  
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
