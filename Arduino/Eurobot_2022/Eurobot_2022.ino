#include <Wire.h>
#include "Robot.h"
#include "HCPCA9685.h"
#include <LiquidCrystal.h>
#include "Ohmmeter.h"
#include "Nunchuk.h"

#define  I2CAdd 0x40

HCPCA9685 *hcpca9685;
Robot *robot;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Ohmmeter ohmmeter(9800.0, A0);

uint16_t servo_pulse_duration;

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
  hcpca9685 = new HCPCA9685(I2CAdd);
  hcpca9685->Init(SERVO_MODE);
  hcpca9685->SetPeriodFreq(50);
  hcpca9685->Sleep(false);
  lcd.begin(16, 2);
  Wire.begin();
  nunchuk_init();
  robot = new Robot(hcpca9685);
}

void loop() 
{
  Serial.print("loop");
  int c = 1;
  
  if (nunchuk_read())
  {
    if(nunchuk_buttonC())
    {
      robot->CalibrateAllLegs();
    }
    else if(nunchuk_buttonZ())
    {
      robot->raiseAllLegs();
    }
    else if(JoystickForward())
    {
      robot->walkForward();
    }
    else if(JoystickRearward())
    {
      //robot->walkRearward();
    }
    else if(JoystickLeftSide())
    {
      robot->rotateLeftSide();
    }
    else if(JoystickRightSide())
    {
      //robot->rotateRightSide();
    }
  }
}

// Archive --------------------------------------------

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
