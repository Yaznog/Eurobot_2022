#ifndef OHMMETER_H
#define OHMMETER_H

class Ohmmeter
{
  public:
    Ohmmeter(float KnownResistor_Value, int Out_Tension_Pin);
    void set_KnownResistor_Value(float value);
    void set_Out_Tension_Pin(int pin);

    float get_KnownResistor_Value();
    float get_KnownResistor_Tension_Value();
    float get_UnknownResistor_Value();

    float get_Normalized_Value(float value);
    const float E12[12] = { 1.0 , 1.2 , 1.5 , 1.8 , 2.2 , 2.7 , 3.3 , 3.9 , 4.7 , 5.6 , 6.8 , 8.2 };
    
  private:
    float m_KnownResitor;
    const float m_In_Tension_Value = 5.0;
    int m_In_Tension_Pin = -1;
    int m_Out_Tension_Pin = -1;
    
    float m_Error_Percent = 0.09;
};

#endif
