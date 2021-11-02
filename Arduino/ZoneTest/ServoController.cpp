#include "ServoController.h"

//#define DEBUG

ServoController::ServoController()
{
  #ifdef DEBUG 
    Serial.println("New ServoController"); 
  #endif
}

ServoController::~ServoController()
{
  #ifdef DEBUG 
    Serial.println("ServoController deleted"); 
  #endif
}
