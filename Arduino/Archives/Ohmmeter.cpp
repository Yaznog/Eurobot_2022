#include "Ohmmeter.h"
#include <Arduino.h>
#include <math.h>

Ohmmeter::Ohmmeter(float KnownResistorValue, int Out_Tension_Pin)
{
  SetKnownResistorValue(KnownResistorValue);
  SetOutTensionPin(Out_Tension_Pin);
}

// Known Resistor ----------------------------------------------------------

void Ohmmeter::SetKnownResistorValue(float value)
{
  if(value >= 1 && value <= 1000000)
    mKnownResitor = value;
}

float Ohmmeter::GetKnownResistorValue()
{
  return mKnownResitor;
}

// Unknown Resistor --------------------------------------------------------

float Ohmmeter::GetKnownResistorTensionValue()
{
  return analogRead(mOutTensionPin)*5.0/1023.0;
}

float Ohmmeter::GetUnknownResistorValue()
{
  return mKnownResitor * ( mInTensionValue / GetKnownResistorTensionValue() - 1 );
}

// Normalized Value --------------------------------------------------------

float Ohmmeter::GetNormalizedValue(float value)
{
  for(int power=0;power<=6;power++)
  {
    for(int index=0;index<12;index++)
    {
      if( value>(E12[index] * pow(10.0,power) * (1-mErrorPercent)) && value<( E12[index] * pow(10.0,power) * (1+mErrorPercent) ) ) return (E12[index]* pow(10.0,power) );
    }
  }
  return 35505;
}

// Pin ---------------------------------------------------------------------

void Ohmmeter::SetOutTensionPin(int pin)
{
  if(pin >= A0 && pin <= A5)
    mOutTensionPin = pin;
}
