#include "Music.h"

//#define DEBUG

Music::Music(uint8_t buzzerPin)
{
#ifdef DEBUG
  Serial.println("New Music");
#endif
  mBuzzerPin = buzzerPin;
}

Music::~Music()
{
#ifdef DEBUG
  Serial.println("Music deleted");
#endif
}

void Music::useBuzzer()
{
  tone(mBuzzerPin, 110, 100);
}

void Music::useBuzzer(uint16_t frequency)
{
  tone(mBuzzerPin, frequency, 100);
}

void Music::windows()
{
#ifdef DEBUG
  Serial.println("Music Windows");
#endif
  musicPlayed_flag = true;
  uint8_t line = 0;
  float lastMillis = millis();

  while (musicPlayed_flag)
  {
    if (millis() - mDeltaT_Windows >= lastMillis)
    {
      if (mMusic_Windows[line][0]) tone(mBuzzerPin, 622, 2 * mDeltaT_Windows - 10);
      if (mMusic_Windows[line][1]) tone(mBuzzerPin, 311, mDeltaT_Windows - 10);
      if (mMusic_Windows[line][2]) tone(mBuzzerPin, 466, 3 * mDeltaT_Windows - 10);
      if (mMusic_Windows[line][3]) tone(mBuzzerPin, 415, 2 * mDeltaT_Windows - 10);

      lastMillis += mDeltaT_Windows;
      line++;
      if (line >= mLength_Windows)
      {
        musicPlayed_flag = false;
        break;
      }
    }
  }
}

void Music::windowsConnection()
{
#ifdef DEBUG
  Serial.println("Music Windows_Connection");
#endif
  musicPlayed_flag = true;
  uint8_t line = 0;
  float lastMillis = millis();

  while (musicPlayed_flag)
  {
    if (millis() - mDeltaT_Windows_Connection >= lastMillis)
    {
      if (mMusic_Windows_Connection[line][0]) tone(mBuzzerPin, 262, mDeltaT_Windows_Connection - 10);
      if (mMusic_Windows_Connection[line][1]) tone(mBuzzerPin, 220, mDeltaT_Windows_Connection - 10);
      if (mMusic_Windows_Connection[line][2]) tone(mBuzzerPin, 175, mDeltaT_Windows_Connection - 10);
      if (mMusic_Windows_Connection[line][3]) tone(mBuzzerPin, 330, mDeltaT_Windows_Connection - 10);

      lastMillis += mDeltaT_Windows_Connection;
      line++;
      if (line >= mLength_Windows_Connection)
      {
        musicPlayed_flag = false;
        break;
      }
    }
  }
}

void Music::windowsDisconnection()
{
#ifdef DEBUG
  Serial.println("Music Windows_Disconnection");
#endif
  musicPlayed_flag = true;
  uint8_t line = 0;
  float lastMillis = millis();

  while (musicPlayed_flag)
  {
    if (millis() - mDeltaT_Windows_Disconnection >= lastMillis)
    {
      if (mMusic_Windows_Disconnection[line][0]) tone(mBuzzerPin, 440, mDeltaT_Windows_Disconnection - 10);
      if (mMusic_Windows_Disconnection[line][1]) tone(mBuzzerPin, 349, mDeltaT_Windows_Disconnection - 10);
      if (mMusic_Windows_Disconnection[line][2]) tone(mBuzzerPin, 330, mDeltaT_Windows_Disconnection - 10);

      lastMillis += mDeltaT_Windows_Disconnection;
      line++;
      if (line >= mLength_Windows_Disconnection)
      {
        musicPlayed_flag = false;
        break;
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

  while (musicPlayed_flag)
  {
    if (millis() - mDeltaT_SaxGuy >= lastMillis)
    {
      if (mMusic_SaxGuy[line][0]) tone(mBuzzerPin, 440, mDeltaT_SaxGuy - 10);
      if (mMusic_SaxGuy[line][1]) tone(mBuzzerPin, 392, mDeltaT_SaxGuy - 10);
      if (mMusic_SaxGuy[line][2]) tone(mBuzzerPin, 349, mDeltaT_SaxGuy - 10);
      if (mMusic_SaxGuy[line][3]) tone(mBuzzerPin, 294, mDeltaT_SaxGuy - 10);

      //----------

      if (line == 35) tone(mBuzzerPin, 523, mDeltaT_SaxGuy - 10); //C5
      if (line == 54) tone(mBuzzerPin, 330, mDeltaT_SaxGuy - 10); //E4

      lastMillis += mDeltaT_SaxGuy;
      line++;
      if (line >= mLength_SaxGuy)
      {
        musicPlayed_flag = false;
        break;
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

  while (musicPlayed_flag)
  {
    if (millis() - mDeltaT_BadApple >= lastMillis)
    {
      if (mMusic_BadApple[line][0]) tone(mBuzzerPin, 65, mDeltaT_BadApple - 10);
      if (mMusic_BadApple[line][1]) tone(mBuzzerPin, 131, mDeltaT_BadApple - 10);
      if (mMusic_BadApple[line][2]) tone(mBuzzerPin, 262, mDeltaT_BadApple - 10);
      if (mMusic_BadApple[line][3]) tone(mBuzzerPin, 523, mDeltaT_BadApple - 10);

      lastMillis += mDeltaT_BadApple;
      line++;
      if (line >= mLength_BadApple)
      {
        musicPlayed_flag = false;
        break;
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

  while (musicPlayed_flag)
  {
    if (millis() - mDeltaT_CrazyFrog >= lastMillis)
    {
      if (mMusic_CrazyFrog[line][0]) tone(mBuzzerPin, 294, mDeltaT_CrazyFrog - 10); //D4
      if (mMusic_CrazyFrog[line][1]) tone(mBuzzerPin, 349, mDeltaT_CrazyFrog - 10); //F4
      if (mMusic_CrazyFrog[line][2]) tone(mBuzzerPin, 392, mDeltaT_CrazyFrog - 10); //G4
      if (mMusic_CrazyFrog[line][3]) tone(mBuzzerPin, 440, mDeltaT_CrazyFrog - 10); //A4

      //----------

      if (line == 14) tone(mBuzzerPin, 262, mDeltaT_CrazyFrog - 10); //C4
      if (line == 26) tone(mBuzzerPin, 466, mDeltaT_CrazyFrog - 10); //A#4
      if (line == 36) tone(mBuzzerPin, 587, mDeltaT_CrazyFrog - 10); //D5
      if (line == 39) tone(mBuzzerPin, 262, mDeltaT_CrazyFrog - 10); //C4
      if (line == 41) tone(mBuzzerPin, 262, mDeltaT_CrazyFrog - 10); //C4
      if (line == 42) tone(mBuzzerPin, 220, mDeltaT_CrazyFrog - 10); //A3
      if (line == 44) tone(mBuzzerPin, 330, mDeltaT_CrazyFrog - 10); //E4

      lastMillis += mDeltaT_CrazyFrog;
      line++;
      if (line >= mLength_CrazyFrog)
      {
        musicPlayed_flag = false;
        break;
      }
    }
  }
}
