#include "Robot.h"

#define NEUTRAL_PIN -1
#define NEUTRAL_OFFSET 0

#define DEBUG

Robot::Robot(Adafruit_PWMServoDriver* pwm)
{
  #ifdef DEBUG 
    Serial.println("New Robot"); 
  #endif
  
  // Create leg (pinTop, pinMid, pinBot, offsetTop, offsetMid, offsetBot, hcpca9685)
  legFrontLeft  = new Leg(4, 5, 6, 10, 8,  13, pwm);
  legFrontRight = new Leg(0, 1, 2, 5, 10,  5, pwm);
  legBackLeft   = new Leg(8, 9, 10, 15, NEUTRAL_OFFSET,  NEUTRAL_OFFSET, pwm);
  legBackRight  = new Leg(12, 13, 14, -3, -15,  5, pwm);

  mLastMillis = millis();

  //CalibrateAllLegs();
  raiseAllLegs();/*
  for(int i=0;i<4;i++) 
  {
    mStartingStep[i] = 0;
    mWalkStep[i] = 0;
    mWalkPolarStep[i] = 0;
    mStoppingStep[i] = 0;
  }*/
  
  /*
  WalkOneLeg(0, LEG_FRONT_LEFT);
  WalkOneLeg(0, LEG_FRONT_RIGHT);
  WalkOneLeg(0, LEG_BACK_LEFT);
  WalkOneLeg(0, LEG_BACK_RIGHT);*/
}

Robot::~Robot()
{
  #ifdef DEBUG 
    Serial.println("Robot deleted"); 
  #endif
  
  legFrontLeft->~Leg();
  legFrontRight->~Leg();
  legBackLeft->~Leg();
  legBackRight->~Leg();
}

void Robot::MoveOneLegToCoordinate(float x, float y, float z, uint8_t leg)
{
  #ifdef DEBUG 
    Serial.print("MoveOneLegToCoordinate : ");
    Serial.println(leg);
  #endif
  if(leg==LEG_FRONT_LEFT) 
  {
    legFrontLeft->SetCoordinateTarget(x, y, z);
    legFrontLeft->MoveLegToTarget(leg);
  }
  else if(leg==LEG_FRONT_RIGHT) 
  {
    legFrontRight->SetCoordinateTarget(x, -y, z);
    legFrontRight->MoveLegToTarget(leg);
  }
  else if(leg==LEG_BACK_LEFT) 
  {
    legBackLeft->SetCoordinateTarget(-x, -y, z);
    legBackLeft->MoveLegToTarget(leg);
  }
  else if(leg==LEG_BACK_RIGHT) 
  {
    legBackRight->SetCoordinateTarget(-x, y, z);
    legBackRight->MoveLegToTarget(leg);
  }
}

void Robot::MoveOneLegToCoordinatePolar(float module, float argument, float z, uint8_t leg)
{
  #ifdef DEBUG 
    Serial.print("MoveOneLegToCoordinatePolar : ");
    Serial.println(leg);
  #endif
  if(leg==LEG_FRONT_LEFT) 
  {
    legFrontLeft->SetCoordinatePolarTarget(module, argument, z);
    legFrontLeft->MoveLegToTarget(leg);
  }
  else if(leg==LEG_FRONT_RIGHT) 
  {
    legFrontRight->SetCoordinatePolarTarget(module, -argument, z);
    legFrontRight->MoveLegToTarget(leg);
  }
  else if(leg==LEG_BACK_LEFT) 
  {
    legBackLeft->SetCoordinatePolarTarget(module, -argument, z);
    legBackLeft->MoveLegToTarget(leg);
  }
  else if(leg==LEG_BACK_RIGHT) 
  {
    legBackRight->SetCoordinatePolarTarget(module, argument, z);
    legBackRight->MoveLegToTarget(leg);
  }
}

void Robot::raiseOneLeg(uint8_t leg)
{
  #ifdef DEBUG 
    Serial.print("raiseOneLeg : ");
    Serial.println(leg);
  #endif
  if(leg==LEG_FRONT_LEFT)       legFrontLeft->raiseLeg(LEG_FRONT_LEFT);
  else if(leg==LEG_FRONT_RIGHT) legFrontRight->raiseLeg(LEG_FRONT_RIGHT);
  else if(leg==LEG_BACK_LEFT)   legBackLeft->raiseLeg(LEG_BACK_LEFT);
  else if(leg==LEG_BACK_RIGHT)  legBackRight->raiseLeg(LEG_BACK_RIGHT);
}

void Robot::raiseAllLegs()
{
  #ifdef DEBUG 
    Serial.println("raiseAllLegs");
  #endif
  legFrontLeft->raiseLeg(LEG_FRONT_LEFT);
  legFrontRight->raiseLeg(LEG_FRONT_RIGHT);
  legBackLeft->raiseLeg(LEG_BACK_LEFT);
  legBackRight->raiseLeg(LEG_BACK_RIGHT);
}

void Robot::WalkOneLeg(uint8_t walkStep, uint8_t leg)
{
  #ifdef DEBUG 
    Serial.print("walkForward : ");
    Serial.println(leg);
  #endif
  if(walkStep==-1)      MoveOneLegToCoordinate(mMovementStop.x,   mMovementStop.y,  mMovementStop.z,  leg);
  else if(walkStep==0)  MoveOneLegToCoordinate(mMovementStep0.x,  mMovementStep0.y, mMovementStep0.z, leg);
  else if(walkStep==1)  MoveOneLegToCoordinate(mMovementStep1.x,  mMovementStep1.y, mMovementStep1.z, leg);
  else if(walkStep==2)  MoveOneLegToCoordinate(mMovementStep2.x,  mMovementStep2.y, mMovementStep2.z, leg);
  else if(walkStep==3)  MoveOneLegToCoordinate(mMovementStep3.x,  mMovementStep3.y, mMovementStep3.z, leg);

  mWalkStep[leg] = walkStep;
}

void Robot::WalkOneLegPolar(uint8_t walkPolarStep, uint8_t leg)
{
  if(mWalkPolarStep==-1)      MoveOneLegToCoordinatePolar(mMovementPolarStop.module,   mMovementPolarStop.argument,  mMovementPolarStop.z,  leg);
  else if(mWalkPolarStep==0)  MoveOneLegToCoordinatePolar(mMovementPolarStep0.module,  mMovementPolarStep0.argument, mMovementPolarStep0.z, leg);
  else if(mWalkPolarStep==1)  MoveOneLegToCoordinatePolar(mMovementPolarStep1.module,  mMovementPolarStep1.argument, mMovementPolarStep1.z, leg);
  else if(mWalkPolarStep==2)  MoveOneLegToCoordinatePolar(mMovementPolarStep2.module,  mMovementPolarStep2.argument, mMovementPolarStep2.z, leg);
  else if(mWalkPolarStep==3)  MoveOneLegToCoordinatePolar(mMovementPolarStep3.module,  mMovementPolarStep3.argument, mMovementPolarStep3.z, leg);

  mWalkPolarStep[leg] = walkPolarStep;
}

void Robot::walkForward()
{
  #ifdef DEBUG 
    Serial.println("walkForward");
  #endif
  if(millis() - mDeltaT >= mLastMillis)
  {
    //Serial.print("etape : ");
    //Serial.println(mWalkStep[1]);
    switch(mWalkStep[LEG_FRONT_LEFT])
    {
      case -1:// Millieu bas
        WalkOneLeg(1,LEG_FRONT_LEFT);
        WalkOneLeg(2,LEG_FRONT_RIGHT);
        WalkOneLeg(3,LEG_BACK_LEFT);
        WalkOneLeg(0,LEG_BACK_RIGHT);
        break;
        
      case 0:// Arrière bas
        WalkOneLeg(1,LEG_FRONT_LEFT);
        WalkOneLeg(3,LEG_FRONT_RIGHT);
        WalkOneLeg(0,LEG_BACK_LEFT);
        WalkOneLeg(2,LEG_BACK_RIGHT);
        break;
        
      case 1:// Millieu haut
        WalkOneLeg(2,LEG_FRONT_LEFT);
        WalkOneLeg(0,LEG_FRONT_RIGHT);
        WalkOneLeg(1,LEG_BACK_LEFT);
        WalkOneLeg(3,LEG_BACK_RIGHT);
        break;
        
      case 2:// Avant bas
        WalkOneLeg(3,LEG_FRONT_LEFT);
        WalkOneLeg(1,LEG_FRONT_RIGHT);
        WalkOneLeg(2,LEG_BACK_LEFT);
        WalkOneLeg(0,LEG_BACK_RIGHT);
        break;
        
      case 3:// Millieu bas
        WalkOneLeg(0,LEG_FRONT_LEFT);
        WalkOneLeg(2,LEG_FRONT_RIGHT);
        WalkOneLeg(3,LEG_BACK_LEFT);
        WalkOneLeg(1,LEG_BACK_RIGHT);
        break;
    }
    //mLastMillis = mLastMillis + mDeltaT;
    mLastMillis = millis();
    //Serial.println(mLastMillis);
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
  if(millis() - mDeltaT >= mLastMillis)
  {
    switch(mWalkPolarStep[LEG_FRONT_LEFT])
    {
      case -1:// Millieu bas
        WalkOneLegPolar(1,LEG_FRONT_LEFT);
        WalkOneLegPolar(2,LEG_FRONT_RIGHT);
        WalkOneLegPolar(3,LEG_BACK_LEFT);
        WalkOneLegPolar(0,LEG_BACK_RIGHT);
        break;
        
      case 0:// Arrière bas
        WalkOneLegPolar(1,LEG_FRONT_LEFT);
        WalkOneLegPolar(3,LEG_FRONT_RIGHT);
        WalkOneLegPolar(0,LEG_BACK_LEFT);
        WalkOneLegPolar(2,LEG_BACK_RIGHT);
        break;
        
      case 1:// Millieu haut
        WalkOneLegPolar(2,LEG_FRONT_LEFT);
        WalkOneLegPolar(0,LEG_FRONT_RIGHT);
        WalkOneLegPolar(1,LEG_BACK_LEFT);
        WalkOneLegPolar(3,LEG_BACK_RIGHT);
        break;
        
      case 2:// Avant bas
        WalkOneLegPolar(3,LEG_FRONT_LEFT);
        WalkOneLegPolar(1,LEG_FRONT_RIGHT);
        WalkOneLegPolar(2,LEG_BACK_LEFT);
        WalkOneLegPolar(0,LEG_BACK_RIGHT);
        break;
        
      case 3:// Millieu bas
        WalkOneLegPolar(0,LEG_FRONT_LEFT);
        WalkOneLegPolar(2,LEG_FRONT_RIGHT);
        WalkOneLegPolar(3,LEG_BACK_LEFT);
        WalkOneLegPolar(1,LEG_BACK_RIGHT);
        break;
    }
    mLastMillis = millis();
  }
}

void Robot::rotateRightSide()
{
  
}

void Robot::CalibrateOneLeg(uint8_t leg)
{
  #ifdef DEBUG 
    Serial.print("CalibrateOneLeg : ");
    Serial.println(leg);
  #endif
  if(leg==0)      legFrontLeft->Calibrate_Servo();
  else if(leg==1) legFrontRight->Calibrate_Servo();
  else if(leg==2) legBackLeft->Calibrate_Servo();
  else if(leg==3) legBackRight->Calibrate_Servo();
}

void Robot::CalibrateAllLegs()
{
  #ifdef DEBUG 
    Serial.println("CalibrateAllLegs");
  #endif
  legFrontLeft->Calibrate_Servo();
  legFrontRight->Calibrate_Servo();
  legBackLeft->Calibrate_Servo();
  legBackRight->Calibrate_Servo();
}

void Robot::marche()
{
  legFrontLeft->marche(1);
  legFrontRight->marche(-1);
}
