#include "Coordinate_Calculator.h"
#include <Arduino.h>
#include <math.h>

Coordinate_Calculator::Coordinate_Calculator(unsigned int leg_Mid_Length, unsigned int leg_Bot_Length)
{
  set_Leg_Mid_Length(leg_Mid_Length);
  set_Leg_Bot_Length(leg_Bot_Length);

}

// Legs Data-----------------------------------------------------

void Coordinate_Calculator::set_Leg_Top_Length(unsigned int length_Value)
{
  m_Leg_Top_Length = length_Value;
}

void Coordinate_Calculator::set_Leg_Mid_Length(unsigned int length_Value)
{
  m_Leg_Mid_Length = length_Value;
}

void Coordinate_Calculator::set_Leg_Bot_Length(unsigned int length_Value)
{
  m_Leg_Bot_Length = length_Value;
}

unsigned int Coordinate_Calculator::get_Leg_Top_Length()
{
  return m_Leg_Top_Length;
}

unsigned int Coordinate_Calculator::get_Leg_Mid_Length()
{
  return m_Leg_Mid_Length;
}

unsigned int Coordinate_Calculator::get_Leg_Bot_Length()
{
  return m_Leg_Bot_Length;
}

// Coordinates---------------------------------------------------

void Coordinate_Calculator::set_Coordinate_Target(float x, float y, float z)
{
  m_X_Coordinate = x;
  m_Y_Coordinate = y;
  m_Z_Coordinate = z;

  m_Module_Coordinate = sqrt( square(x) + square(y) );
  m_Argument_Coordinate = asin(y/m_Module_Coordinate);
}

void Coordinate_Calculator::set_Coordinate_Polar_Target(float module, float argument, float z)
{
  m_Module_Coordinate = module;
  m_Argument_Coordinate = argument;
  m_Z_Coordinate = z;

  m_X_Coordinate = cos(m_Argument_Coordinate) * m_Module_Coordinate;
  m_Y_Coordinate = sin(m_Argument_Coordinate) * m_Module_Coordinate;
}

float Coordinate_Calculator::get_X_Coordinate()
{
  return m_X_Coordinate;
}

float Coordinate_Calculator::get_Y_Coordinate()
{
  return m_Y_Coordinate;
}

float Coordinate_Calculator::get_Z_Coordinate()
{
  return m_Z_Coordinate;
}

float Coordinate_Calculator::get_Module_Coordinate()
{
  return m_Module_Coordinate;
}

float Coordinate_Calculator::get_Argument_Coordinate()
{
  return m_Argument_Coordinate;
}

// Angles----------------------------------------------------

float Coordinate_Calculator::get_Servo_Top_Angle()
{
  return m_Argument_Coordinate;
}

float Coordinate_Calculator::get_Servo_Mid_Angle()
{
  float c = sqrt( (square(m_Module_Coordinate) + square(m_Z_Coordinate)) );
  return acos( ( -square(m_Leg_Mid_Length) + square(m_Leg_Bot_Length) + square(c) ) / (2*m_Leg_Bot_Length*c) );
}

float Coordinate_Calculator::get_Servo_Bot_Angle()
{
  float c = sqrt( (square(m_Module_Coordinate) + square(m_Z_Coordinate)) );
  return acos( ( -square(m_Leg_Bot_Length) + square(m_Leg_Mid_Length) + square(c) ) / (2*m_Leg_Mid_Length*c) );
}
