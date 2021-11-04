#include "Music.h"

//#define DEBUG

Music::Music()
{
  #ifdef DEBUG 
    Serial.println("New Music"); 
  #endif
  
}

Music::~Music()
{
  #ifdef DEBUG 
    Serial.println("Music deleted"); 
  #endif
}

void Music::useBuzzer(uint8_t buzzerNumber)
{
  if(buzzerNumber == 0)
  {
    noTone(mPinBuzzer_0);
    tone(mPinBuzzer_0, 440, 100);
  }
  if(buzzerNumber == 1)
  {
    noTone(mPinBuzzer_1);
    tone(mPinBuzzer_1, 440, 100);
  }
  if(buzzerNumber == 2)
  {
    noTone(mPinBuzzer_2);
    tone(mPinBuzzer_2, 440, 100);
  }
  if(buzzerNumber == 3)
  {
    noTone(mPinBuzzer_3);
    tone(mPinBuzzer_3, 440, 100);
  }
}

void Music::useBuzzer(uint8_t buzzerNumber, uint16_t frequency)
{
  if(buzzerNumber == 0)
  {
    noTone(mPinBuzzer_0);
    tone(mPinBuzzer_0, frequency, 100);
  }
  if(buzzerNumber == 1)
  {
    noTone(mPinBuzzer_1);
    tone(mPinBuzzer_1, frequency, 100);
  }
  if(buzzerNumber == 2)
  {
    noTone(mPinBuzzer_2);
    tone(mPinBuzzer_2, frequency, 100);
  }
  if(buzzerNumber == 3)
  {
    noTone(mPinBuzzer_3);
    tone(mPinBuzzer_3, frequency, 100);
  }
}

void Music::badApple()
{
  Serial.println("Bad Apple"); 
  musicPlayed_flag = true;
  uint8_t line = 0;
  float lastMillis = millis();

  noTone(mPinBuzzer_0);
  noTone(mPinBuzzer_1);
  noTone(mPinBuzzer_2);
  noTone(mPinBuzzer_3);

  while(musicPlayed_flag)
  {
    if(millis() - mDeltaT_BadApple >= lastMillis)
    {
      if(mMusic_BadApple[line][0]) tone(mPinBuzzer_0, 264, mDeltaT_BadApple - 10);
      if(mMusic_BadApple[line][1]) tone(mPinBuzzer_1, 349, mDeltaT_BadApple - 10);
      if(mMusic_BadApple[line][2]) tone(mPinBuzzer_2, 392, mDeltaT_BadApple - 10);
      if(mMusic_BadApple[line][3]) tone(mPinBuzzer_3, 440, mDeltaT_BadApple - 10);
  
      lastMillis += mDeltaT_BadApple;
      line++;
      if(line>=mLength_BadApple)
      {
        musicPlayed_flag = false;
        return 0;
      }
    }
  }
}
void Music::crazyFrog()
{
  Serial.println("Crazy Frog"); 
  uint8_t line = 0;
  musicPlayed_flag = true;
  float lastMillis = millis();
  
  noTone(mPinBuzzer_0);
  noTone(mPinBuzzer_1);
  noTone(mPinBuzzer_2);
  noTone(mPinBuzzer_3);
  
  while(musicPlayed_flag)
  {
    if(millis() - mDeltaT_CrazyFrog >= lastMillis)
    {
      if(mMusic_CrazyFrog[line][0]) tone(mPinBuzzer_0, 264, mDeltaT_CrazyFrog - 10);
      if(mMusic_CrazyFrog[line][1]) tone(mPinBuzzer_1, 349, mDeltaT_CrazyFrog - 10);
      if(mMusic_CrazyFrog[line][2]) tone(mPinBuzzer_2, 392, mDeltaT_CrazyFrog - 10);
      if(mMusic_CrazyFrog[line][3]) tone(mPinBuzzer_3, 440, mDeltaT_CrazyFrog - 10);
  
      //----------
      
      if(line==14) tone(mPinBuzzer_0, 262, mDeltaT_CrazyFrog - 10);
      if(line==26) tone(mPinBuzzer_1, 466, mDeltaT_CrazyFrog - 10);
      if(line==36) tone(mPinBuzzer_2, 587, mDeltaT_CrazyFrog - 10);
      if(line==39) tone(mPinBuzzer_3, 262, mDeltaT_CrazyFrog - 10);
      if(line==41) tone(mPinBuzzer_0, 262, mDeltaT_CrazyFrog - 10);
      if(line==42) tone(mPinBuzzer_1, 220, mDeltaT_CrazyFrog - 10);
      if(line==44) tone(mPinBuzzer_2, 330, mDeltaT_CrazyFrog - 10);
      
      lastMillis += mDeltaT_CrazyFrog;
      line++;
      if(line>=mLength_CrazyFrog)
      {
        musicPlayed_flag = false;
        return 0;
      }
    }
  }
}
