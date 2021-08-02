#include "Ohmmeter.h"
#include <Arduino.h>
#include <math.h>

Ohmmeter::Ohmmeter(float KnownResistor_Value, int Out_Tension_Pin)
{
  set_KnownResistor_Value(KnownResistor_Value);
  set_Out_Tension_Pin(Out_Tension_Pin);
}

// Known Resistor ----------------------------------------------------------

void Ohmmeter::set_KnownResistor_Value(float value)
{
  if(value >= 1 && value <= 1000000)
    m_KnownResitor = value;
}

float Ohmmeter::get_KnownResistor_Value()
{
  return m_KnownResitor;
}

// Unknown Resistor --------------------------------------------------------

float Ohmmeter::get_KnownResistor_Tension_Value()
{
  return analogRead(m_Out_Tension_Pin)*5.0/1023.0;
}

float Ohmmeter::get_UnknownResistor_Value()
{
  return m_KnownResitor * ( m_In_Tension_Value / get_KnownResistor_Tension_Value() - 1 );
}

// Normalized Value --------------------------------------------------------

float Ohmmeter::get_Normalized_Value(float value)
{
  for(int power=0;power<=6;power++)
  {
    for(int index=0;index<12;index++)
    {
      if( value>(E12[index] * pow(10.0,power) * (1-m_Error_Percent)) && value<( E12[index] * pow(10.0,power) * (1+m_Error_Percent) ) ) return (E12[index]* pow(10.0,power) );
    }
  }
  return 35505;
}

// Pin ---------------------------------------------------------------------

void Ohmmeter::set_Out_Tension_Pin(int pin)
{
  if(pin >= A0 && pin <= A5)
    m_Out_Tension_Pin = pin;
}
