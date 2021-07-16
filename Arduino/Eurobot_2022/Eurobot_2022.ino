#include "Ohmmeter.h"
#include "Toolbox.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Toolbox toolbox(1);
Ohmmeter ohmmeter(9800.0, A0);

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
}

void loop() 
{
  for(int power=0;power<=6;power++)
  {
    for(int index=0;index<12;index++)
    {
      Serial.println( ohmmeter.E12[index] * toolbox.Power(10.0,power) );
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
