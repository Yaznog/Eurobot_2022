#include "Toolbox.h"
#include <Arduino.h>


Toolbox::Toolbox(int un)
{
}

float Toolbox::Power(float value, int power)
{
  float value_Power = 1.0;
  for(int i=1;i<=power;i++)
  {
    value_Power = value_Power * value;
  }
  return value_Power;
}
