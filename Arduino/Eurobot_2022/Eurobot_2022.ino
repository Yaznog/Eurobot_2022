#include <Wire.h>
#include "Robot.h"
#include "Adafruit_PWMServoDriver.h"
#include <LiquidCrystal.h>
#include "Ohmmeter.h"
#include "Nunchuk.h"
#include "Music.h"

Adafruit_PWMServoDriver* pwm = new Adafruit_PWMServoDriver();
Music *music = new Music();
Robot *robot;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Ohmmeter ohmmeter(9800.0, A0);

bool start_flag = false;
boolean jack;
int8_t jack_Pin = 2;
int incomingByte = 0;

float x_Target;
float y_Target;
float z_Target;
float module_Target;
float argument_Target;

void setup() 
{
  pinMode(jack_Pin, INPUT);
  Serial.begin(9600);
  Serial.println("SETUP");
  
  // PCA9685
  pwm->begin();
  pwm->setOscillatorFrequency(27000000); 
  pwm->setPWMFreq(SERVO_FREQ);

  music->useBuzzer(0);
  
  lcd.begin(16, 2);
  Wire.begin();
  nunchuk_init();
  robot = new Robot(pwm);
}

void loop() 
{
  Serial.print("loop");
  if(!start_flag)
  {
    //music->windows();
    start_flag = true;
  }
  
  //robot->CalibrateAllLegs();

  if(Serial.available())
  {
    incomingByte = Serial.read();
    switch(incomingByte)
    {
      case 122://z
      {
        Serial.print("z");
        //robot->walkForward();
        break;
      }
      case 113://q
      {
        Serial.print("q");
        break;
      }
      case 115://s
      {
        Serial.print("s");
        break;
      }
      case 100://d
      {
        Serial.print("d");
        break;
      }
      case 97://a
      {
        Serial.print("a");
        robot->CalibrateAllLegs();
        break;
      }
      case 101://e
      {
        Serial.print("e");
        robot->raiseAllLegs();
        break;
      }
    }
  }

  /*
  if (nunchuk_read())
  {
    if(nunchuk_buttonC())
    {
      Serial.println("Button C");
      //if(music->musicPlayed_flag == false) music->saxGuy();
      robot->CalibrateAllLegs();
    }
    else if(nunchuk_buttonZ())
    {
      Serial.println("Button Z");
      //if(music->musicPlayed_flag == false) music->crazyFrog();
      robot->raiseAllLegs();
    }
    else if(JoystickForward())
    {
      Serial.println("Button Forward");
      //if(music->musicPlayed_flag == false) music->saxGuy();
      //robot->walkForward();
    }
    else if(JoystickRearward())
    {
      for(int i=0; i<100; i++)
      {
        //robot->MoveOneLegToCoordinatePolar(100, PI/4, 100, 0);
      }
      //robot->walkRearward();
    }
    else if(JoystickLeftSide())
    {
      //robot->rotateLeftSide();
    }
    else if(JoystickRightSide())
    {
      //robot->rotateRightSide();
    }
  }*/
}

// Archive --------------------------------------------

/*
  SREG |= 128;

  //0.5Hz
  TCCR1A=0;
  TCCR1B=4;
  TIMSK1=1;
  TCNT1=2855;

  //10Hz
  TCCR2A=0;
  TCCR2B=7;
  TIMSK2=1;
  TCNT2=243;
*/

/*
//0.5Hz
ISR(TIMER1_OVF_vect)
{
  TCNT1=2855;
  Print_LCDScreen_OhmmeterValue();
}

//10Hz
ISR(TIMER2_OVF_vect)
{
  TCNT2=243;
}*/

/*
void Print_LCDScreen_OhmmeterValue()
{
  Clear_LCDScreen();
  lcd.setCursor(0, 0);
  lcd.print("Ohmmeter:"); 
  lcd.setCursor(0, 1);
  lcd.print(ohmmeter.GetUnknownResistorValue());
  lcd.setCursor(8, 1);
  lcd.print( ohmmeter.GetNormalizedValue(ohmmeter.GetUnknownResistorValue()) );
}

void Clear_LCDScreen()
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}*/

  /*
  jack = digitalRead(jack_Pin);
  if(jack)
  {
    
  }
  else 
  {
    
  }*/
