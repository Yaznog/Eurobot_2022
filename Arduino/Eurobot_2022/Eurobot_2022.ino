#include <Wire.h>
#include <SoftwareSerial.h>
#include "Robot.h"
#include "Adafruit_PWMServoDriver.h"
#include "Music.h"

// PIN
#define JACK_PIN -1
#define STATE_PIN 3
#define BUZZER_PIN 8
#define TX_PIN 9
#define RX_PIN 10

// FLAG
bool startFlag = true;
bool jackFlag = true;
bool blueListenFlag = true;
bool blueSerialFlag = false;
bool blueConnectFlag = false;

// CONSTANTE
#define SERVO_FREQ 50
#define BAUD 9600
#define DELAY_1 500

char blueData;
float lastMillis;


//Adafruit_PWMServoDriver* servoDriver = new Adafruit_PWMServoDriver();
Music* music;
Robot* robot;
SoftwareSerial blueSerial(TX_PIN, RX_PIN);

void setup() 
{
  //pinMode(JACK_PIN, INPUT);
  Serial.begin(BAUD);
  pinMode(STATE_PIN, INPUT);
    
  // PCA9685
  //servoDriver->begin();
  //servoDriver->setOscillatorFrequency(27000000);
  //servoDriver->setPWMFreq(SERVO_FREQ);

  blueSerial.begin(BAUD);
  blueSerialFlag = true;

  music = new Music(BUZZER_PIN);
  //robot = new Robot(servoDriver);
  delay(300);
  music->windows();
  lastMillis = millis();
}

void loop() 
{
  if(millis() > lastMillis + DELAY_1)
  {
    testBlueConnection();
    lastMillis += DELAY_1;
  }
  
  
  /*
  if (!startFlag) 
  {
    //music->windows();
    startFlag = true;
  }*/
  //delay(2000);
  //tone(8, 110, 100);
  //robot->CalibrateAllLegs();

  if(blueListenFlag)
  {
    if(blueSerialFlag)
    {
      if (blueSerial.available()) 
      {
        blueData=blueSerial.read(); 
        parseCommand(blueData);
      }
    }
    else
    {
      blueSerial.begin(9600);
      blueSerialFlag = true;
    }
  }
  else
  {
    blueSerial.end();
    blueSerialFlag = false;
  }
}

void parseCommand(char input) 
{
  switch (input) {
    case 'u': // UP
      Serial.println("UP");
      music->useBuzzer();
      
      blueSerial.end();
      blueSerialFlag = false;
      
      robot->CalibrateAllLegs();

      blueSerial.begin(9600);
      blueSerialFlag = true;
      break;
    case 'd': // DOWN
      Serial.println("DOWN");
      music->useBuzzer();
      break;
    case 'l': // LEFT
      Serial.println("LEFT");
      music->useBuzzer();
      break;
    case 'r': // RIGHT
      Serial.println("RIGHT");
      music->useBuzzer();
      break; 

    case 'm': // SELECT
      Serial.println("SELECT");
      music->useBuzzer();
      break;
    case 'M': // START
      Serial.println("START");
      music->useBuzzer();
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

void testBlueConnection()
{
  if(digitalRead(STATE_PIN))
  {
    if(!blueConnectFlag)
    {
      Serial.println("Bluetooth : Connected");
      music->windowsConnection();
    }
    
    blueConnectFlag = true;
  }
  else
  {
    if(blueConnectFlag)
    {
      Serial.println("Bluetooth : Disconnected");
      music->windowsDisconnection();
    }
    
    blueConnectFlag = false;
  }
}
