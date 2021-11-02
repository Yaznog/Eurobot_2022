#include <Wire.h>
#include "Robot.h"
#include "Adafruit_PWMServoDriver.h"
#include <LiquidCrystal.h>
#include "Ohmmeter.h"
#include "Nunchuk.h"

// PCA9685
Adafruit_PWMServoDriver* pwm = new Adafruit_PWMServoDriver();

uint8_t servonum = 0;


Robot *robot;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Ohmmeter ohmmeter(9800.0, A0);

boolean jack;
int8_t jack_Pin = 2;

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
  
  lcd.begin(16, 2);
  Wire.begin();
  nunchuk_init();
  robot = new Robot(pwm);
}

void loop() 
{
  Serial.print("loop");
  int c = 1;
  //robot->CalibrateAllLegs();
  
  if (nunchuk_read())
  {
    if(nunchuk_buttonC())
    {
      Serial.println("Button C");
      //pwm->setPWM(servonum, 0, map(45, 0, 180, SERVOMIN, SERVOMAX));
      robot->CalibrateAllLegs();
    }
    else if(nunchuk_buttonZ())
    {
      Serial.println("Button Z");
      //pwm->setPWM(servonum, 0, map(90, 0, 180, SERVOMIN, SERVOMAX));
      robot->raiseAllLegs();
    }
    else if(JoystickForward())
    {
      Serial.println("Button Forward");
      //pwm.setPWM(servonum, 0, map(180, 0, 180, SERVOMIN, SERVOMAX));
      robot->walkForward();
    }
    else if(JoystickRearward())
    {
      for(int i=0; i<100; i++)
      {
        robot->MoveOneLegToCoordinatePolar(100, PI/4, 100, 0);
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
  }
}

// Archive --------------------------------------------

/*
 * pwm->setPWM(mServoTopPin, 0, map(GetServoTopAngle(), 0, 180, SERVOMIN, SERVOMAX));
  pwm->setPWM(mServoMidPin, 0, map(GetServoMidAngle(), 0, 180, SERVOMIN, SERVOMAX));
  pwm->setPWM(mServoBotPin, 0, map(GetServoBotAngle(), 0, 180, SERVOMIN, SERVOMAX));
 */

/*
void Print_Joystick_Value(int16_t X, int16_t Y)
{
  Serial.print("X = ");
  Serial.print(X);
  Serial.print("   Y = ");
  Serial.println(Y);
}*/

/*
  SREG |= 128;

  //0.5Hz
  TCCR1A=0;
  TCCR1B=4;
  TIMSK1=1;s
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

  /*
  else if (nunchuk_read())
  {
    if(nunchuk_accelY_raw()>600)
    {
      //robot.CalibrateAllLegs();
    }
    else 
    {
      nunchuk_X_Value = joystick_DeadZone( nunchuk_joystickX() );
      nunchuk_Y_Value = joystick_DeadZone
      ( nunchuk_joystickY() );
  
      if(nunchuk_buttonZ()) z_Target = 180.0;
      else if(nunchuk_buttonC()) z_Target = 100.0;
      else z_Target = 140.0;

      //robot.MoveOneLegToCoordinate(ValueToCoordinate(nunchuk_X_Value)+90, ValueToCoordinate(nunchuk_Y_Value), z_Target, 1);
      //coordinate_Calculator.SetCoordinateTarget(ValueToCoordinate(nunchuk_X_Value)+90, ValueToCoordinate(nunchuk_Y_Value), z_Target);
      //coordinate_Calculator.SetCoordinateTarget(100.0, 100.0, 150.0);
      //coordinate_Calculator.SetCoordinatePolarTarget(100.0, PI/2.0, 150.0);
    }
  }*/
