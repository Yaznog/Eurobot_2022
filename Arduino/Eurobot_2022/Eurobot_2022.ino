#include <LiquidCrystal.h>
#include <Servo.h>
#include <Wire.h>
#include <math.h>

#include "Ohmmeter.h"
#include "Nunchuk.h"
#include "Coordinate_Calculator.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Ohmmeter ohmmeter(9800.0, A0);
Coordinate_Calculator coordinate_Calculator(41, 100, 171);

int16_t nunchuk_X_Value = 0;
int16_t nunchuk_Y_Value = 0;

float x_Target;
float y_Target;
float z_Target;
float module_Target;
float argument_Target;

Servo servo_Top;
Servo servo_Mid;
Servo servo_Bot;

void setup() 
{
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

  lcd.begin(16, 2);
  Serial.begin(9600);

  Wire.begin();
  nunchuk_init();
  servo_Top.attach(9);
  servo_Mid.attach(10);
  servo_Bot.attach(11);
}

void loop() 
{
  Calibrate_Servo();
  while(true)
  {
    if (nunchuk_read())
    {
      if(nunchuk_accelY_raw()>600)
      {
        Calibrate_Servo();
      }
      else 
      {
        nunchuk_X_Value = Joystick_DeadZone( nunchuk_joystickX() );
        nunchuk_Y_Value = Joystick_DeadZone( nunchuk_joystickY() );
    
        if(nunchuk_buttonZ()) z_Target = 180.0;
        else if(nunchuk_buttonC()) z_Target = 100.0;
        else z_Target = 140.0;

        coordinate_Calculator.set_Coordinate_Target(Value_To_Coordinate(nunchuk_X_Value)+90, Value_To_Coordinate(nunchuk_Y_Value), z_Target);
        //coordinate_Calculator.set_Coordinate_Target(100.0, 100.0, 150.0);
        //coordinate_Calculator.set_Coordinate_Polar_Target(100.0, PI/2.0, 150.0);
  
        servo_Top.write( Servo_Top_Forbidden_Value(coordinate_Calculator.get_Servo_Top_Angle() * 180/PI + 90) );
        servo_Mid.write( Servo_Mid_Forbidden_Value(coordinate_Calculator.get_Servo_Mid_Angle() * 180/PI + 90) );
        servo_Bot.write( Servo_Bot_Forbidden_Value(coordinate_Calculator.get_Servo_Bot_Angle() * 180/PI + 90) );
        /*
        Serial.print("X Value : ");
        Serial.println(coordinate_Calculator.get_X_Coordinate());
        Serial.print("Y Value : ");
        Serial.println(coordinate_Calculator.get_Y_Coordinate());
        Serial.print("Z Value : ");
        Serial.println(coordinate_Calculator.get_Z_Coordinate());
        Serial.print("Module Value : ");
        Serial.println(coordinate_Calculator.get_Module_Coordinate());
        Serial.print("Argument Value : ");
        Serial.println(coordinate_Calculator.get_Argument_Coordinate() * 180/PI);
        Serial.print("servo_Top Angle : ");
        Serial.println(coordinate_Calculator.get_Servo_Top_Angle() * 180/PI);
        Serial.print("servo_Mid Angle : ");
        Serial.println(coordinate_Calculator.get_Servo_Mid_Angle() * 180/PI);
        Serial.print("servo_Bot Angle : ");
        Serial.println(coordinate_Calculator.get_Servo_Bot_Angle() * 180/PI);*/
      }
    }
  }
}

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
}

void Print_LCDScreen_OhmmeterValue()
{
  Clear_LCDScreen();
  lcd.setCursor(0, 0);
  lcd.print("Ohmmeter:"); 
  lcd.setCursor(0, 1);
  lcd.print(ohmmeter.get_UnknownResistor_Value());
  lcd.setCursor(8, 1);
  lcd.print( ohmmeter.get_Normalized_Value(ohmmeter.get_UnknownResistor_Value()) );
}

void Clear_LCDScreen()
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

int16_t Joystick_DeadZone(int16_t value)
{
  int16_t deadzone_Min = 3;
  int16_t deadzone_Max = 90;
  
  if( value<deadzone_Min && value>-deadzone_Min ) return 0;
  if(value>deadzone_Max) return(deadzone_Max);
  if(value<-deadzone_Max) return(-deadzone_Max);
  return(value);
}

void Print_Joystick_Value(int16_t X, int16_t Y)
{
  Serial.print("X = ");
  Serial.print(X);
  Serial.print("   Y = ");
  Serial.println(Y);
}

void Calibrate_Servo()
{
  servo_Top.write(90);
  servo_Mid.write(90);
  servo_Bot.write(90);
}

float Value_To_Coordinate(int16_t value)
{
  float value_Max = 90;
  float coordinate_Max = 90;
  return (value/value_Max * coordinate_Max);
}

float Servo_Top_Forbidden_Value(float value)
{
  if(value<10.0) return (float)10.0;
  if(value>170.0) return (float)170.0;
  return value;
}

float Servo_Mid_Forbidden_Value(float value)
{
  if(value<30.0) return (float)30.0;
  if(value>140.0) return (float)140.0;
  return value;
}

float Servo_Bot_Forbidden_Value(float value)
{
  if(value<30.0) return (float)30.0;
  if(value>160.0) return (float)160.0;
  return value;
}
