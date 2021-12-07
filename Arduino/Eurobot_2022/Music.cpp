#include "Music.h"

//#define DEBUG

Music::Music()
{
  #ifdef DEBUG 
    Serial.println("New Music"); 
  #endif

  noTone(mPinBuzzer_0);
  noTone(mPinBuzzer_1);
  noTone(mPinBuzzer_2);
  noTone(mPinBuzzer_3);
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

void Music::windows()
{
  #ifdef DEBUG 
    Serial.println("Music Windows"); 
  #endif
  musicPlayed_flag = true;
  uint8_t line = 0;
  float lastMillis = millis();

  noTone(mPinBuzzer_0);
  noTone(mPinBuzzer_1);
  noTone(mPinBuzzer_2);
  noTone(mPinBuzzer_3);

  while(musicPlayed_flag)
  {
    if(millis() - mDeltaT_Windows >= lastMillis)
    {
      //if(mMusic_Windows[line][0]) tone(mPinBuzzer_0, 622, 2*mDeltaT_Windows - 10);
      //if(mMusic_Windows[line][1]) tone(mPinBuzzer_1, 311, mDeltaT_Windows - 10);
      //if(mMusic_Windows[line][2]) tone(mPinBuzzer_2, 466, 3*mDeltaT_Windows - 10);
      //if(mMusic_Windows[line][3]) tone(mPinBuzzer_3, 415, 2*mDeltaT_Windows - 10);
  
      lastMillis += mDeltaT_Windows;
      line++;
      if(line>=mLength_Windows)
      {
        musicPlayed_flag = false;
        return 0;
      }
    }
  }
}

void Music::saxGuy()
{
  #ifdef DEBUG 
    Serial.println("Music SaxGuy"); 
  #endif
  musicPlayed_flag = true;
  uint8_t line = 0;
  float lastMillis = millis();

  noTone(mPinBuzzer_0);
  noTone(mPinBuzzer_1);
  noTone(mPinBuzzer_2);
  noTone(mPinBuzzer_3);

  while(musicPlayed_flag)
  {
    if(millis() - mDeltaT_SaxGuy >= lastMillis)
    {
      if(mMusic_SaxGuy[line][0]) tone(mPinBuzzer_0, 622, mDeltaT_SaxGuy - 10);
      if(mMusic_SaxGuy[line][1]) tone(mPinBuzzer_0, 311, mDeltaT_SaxGuy - 10);
      if(mMusic_SaxGuy[line][2]) tone(mPinBuzzer_0, 466, mDeltaT_SaxGuy - 10);
      if(mMusic_SaxGuy[line][3]) tone(mPinBuzzer_0, 415, mDeltaT_SaxGuy - 10);
      
      //----------

      if(line==35) tone(mPinBuzzer_0, 523, mDeltaT_SaxGuy - 10);//C5
      if(line==54) tone(mPinBuzzer_1, 330, mDeltaT_SaxGuy - 10);//E4
  
      lastMillis += mDeltaT_SaxGuy;
      line++;
      if(line>=mLength_SaxGuy)
      {
        musicPlayed_flag = false;
        return 0;
      }
    }
  }
}

void Music::badApple()
{
  #ifdef DEBUG 
    Serial.println("Music BadApple"); 
  #endif
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
      //if(mMusic_BadApple[line][0]) tone(mPinBuzzer_0, 65, mDeltaT_BadApple - 10);
      //if(mMusic_BadApple[line][1]) tone(mPinBuzzer_1, 131, mDeltaT_BadApple - 10);
      //if(mMusic_BadApple[line][2]) tone(mPinBuzzer_2, 262, mDeltaT_BadApple - 10);
      //if(mMusic_BadApple[line][3]) tone(mPinBuzzer_3, 523, mDeltaT_BadApple - 10);
  
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
  #ifdef DEBUG 
    Serial.println("Music CrazyFrog"); 
  #endif
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
      if(mMusic_CrazyFrog[line][0]) tone(mPinBuzzer_0, 294, mDeltaT_CrazyFrog - 10);//D4
      if(mMusic_CrazyFrog[line][1]) tone(mPinBuzzer_1, 349, mDeltaT_CrazyFrog - 10);//F4
      if(mMusic_CrazyFrog[line][2]) tone(mPinBuzzer_2, 392, mDeltaT_CrazyFrog - 10);//G4
      if(mMusic_CrazyFrog[line][3]) tone(mPinBuzzer_3, 440, mDeltaT_CrazyFrog - 10);//A4
  
      //----------
      
      if(line==14) tone(mPinBuzzer_0, 262, mDeltaT_CrazyFrog - 10);//C4
      if(line==26) tone(mPinBuzzer_1, 466, mDeltaT_CrazyFrog - 10);//A#4
      if(line==36) tone(mPinBuzzer_2, 587, mDeltaT_CrazyFrog - 10);//D5
      if(line==39) tone(mPinBuzzer_3, 262, mDeltaT_CrazyFrog - 10);//C4
      if(line==41) tone(mPinBuzzer_0, 262, mDeltaT_CrazyFrog - 10);//C4
      if(line==42) tone(mPinBuzzer_1, 220, mDeltaT_CrazyFrog - 10);//A3
      if(line==44) tone(mPinBuzzer_2, 330, mDeltaT_CrazyFrog - 10);//E4
      
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
