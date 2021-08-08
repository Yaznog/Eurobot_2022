#ifndef OHMMETER_H
#define OHMMETER_H

class Ohmmeter
{
  public:
  
    Ohmmeter(float KnownResistorValue, int Out_Tension_Pin);
    void SetKnownResistorValue(float value);
    void SetOutTensionPin(int pin);

    float GetKnownResistorValue();
    float GetKnownResistorTensionValue();
    float GetUnknownResistorValue();

    float GetNormalizedValue(float value);
    const float E12[12] = { 1.0 , 1.2 , 1.5 , 1.8 , 2.2 , 2.7 , 3.3 , 3.9 , 4.7 , 5.6 , 6.8 , 8.2 };
    
  private:
  
    float mKnownResitor;
    const float mInTensionValue = 5.0;
    int mInTensionPin = -1;
    int mOutTensionPin = -1;
    
    float mErrorPercent = 0.09;
};

#endif
