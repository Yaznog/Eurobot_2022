#include <Wire.h>
#include <SoftwareSerial.h>
#include "Robot.h"
#include "Adafruit_PWMServoDriver.h"
#include "Music.h"

bool start_flag = false;
boolean jack;
//int8_t jack_Pin = -1;
const uint8_t buzzerPin = 8;

float x_Target;
float y_Target;
float z_Target;
float module_Target;
float argument_Target;

const uint8_t txPin = 9;
const uint8_t rxPin = 10;
char bluetoothData;

const uint16_t servoFreq = 50;

Adafruit_PWMServoDriver* servoDriver = new Adafruit_PWMServoDriver();
Music* music;
Robot* robot;
SoftwareSerial blueSerial(txPin, rxPin);

void setup() 
{
  //pinMode(jack_Pin, INPUT);
  Serial.begin(9600);
  Serial.println("SETUP");
  blueSerial.begin(9600);
  
  // PCA9685
  servoDriver->begin();
  servoDriver->setOscillatorFrequency(27000000);
  servoDriver->setPWMFreq(servoFreq);

  music = new Music(buzzerPin);
  Wire.begin();
  robot = new Robot(servoDriver);
}

void loop() 
{/*
  Serial.print("loop");
  if (!start_flag) 
  {
    //music->windows();
    start_flag = true;
  }*/

  //robot->CalibrateAllLegs();

  if (blueSerial.available()) 
  {
    bluetoothData=blueSerial.read(); 
    //music->useBuzzer();
    //tone(buzzerPin, 110, 100);
    parseCommand(bluetoothData);
  }
}

void parseCommand(char input) 
{
  switch (input) {
    case 'u': // UP
      Serial.println("UP");
      break;
    case 'd': // DOWN
      Serial.println("DOWN");
      break;
    case 'l': // LEFT
      Serial.println("LEFT");
      break;
    case 'r': // RIGHT
      Serial.println("RIGHT");
      break; 

    case 'm': // SELECT
      Serial.println("SELECT");
      break;
    case 'M': // START
      Serial.println("START");
      break; 
      
    case 'S': // SQUARE
      Serial.println("SQUARE");
      music->windows();
      break;
    case 'T': // TRIANGLE
      Serial.println("TRIANGLE");
      music->saxGuy();
      break;
    case 'C': // CROSS
      Serial.println("CROSS");
      music->badApple();
      break;
    case 'R': // ROUND
      Serial.println("ROUND");
      music->crazyFrog();
      break; 
  }
}


// Archive --------------------------------------------


/*
  if (nunchuk_read())
  {
    if(nunchuk_buttonC())
    {
      Serial.println("Button C");
      //if(music->musicPlayed_flag == false) music->saxGuy();
      robot->CalibrateAllLegs();
    }
    else if(nunchuk_buttonZ())
    {
      Serial.println("Button Z");
      //if(music->musicPlayed_flag == false) music->crazyFrog();
      robot->raiseAllLegs();
    }
    else if(JoystickForward())
    {
      Serial.println("Button Forward");
      //if(music->musicPlayed_flag == false) music->saxGuy();
      //robot->walkForward();
    }
    else if(JoystickRearward())
    {
      for(int i=0; i<100; i++)
      {
        //robot->MoveOneLegToCoordinatePolar(100, PI/4, 100, 0);
      }
      //robot->walkRearward();
    }
    else if(JoystickLeftSide())
    {
      //robot->rotateLeftSide();
    }
    else if(JoystickRightSide())
    {
      //robot->rotateRightSide();
    }
  }*/




/*
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
*/

/*
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
}*/

/*
void Print_LCDScreen_OhmmeterValue()
{
  Clear_LCDScreen();
  lcd.setCursor(0, 0);
  lcd.print("Ohmmeter:"); 
  lcd.setCursor(0, 1);
  lcd.print(ohmmeter.GetUnknownResistorValue());
  lcd.setCursor(8, 1);
  lcd.print( ohmmeter.GetNormalizedValue(ohmmeter.GetUnknownResistorValue()) );
}

void Clear_LCDScreen()
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}*/

/*
  jack = digitalRead(jack_Pin);
  if(jack)
  {
    
  }
  else 
  {
    
  }*/
