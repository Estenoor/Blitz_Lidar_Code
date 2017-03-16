#include <Wire.h>
#include <OneWire.h>
#include "Ds18x20.h"

//Declare DSTemp Object
DSTemp Ds;

float sendArray[4];
  
void setup() 
{ 
  //Initialize Serial Communication for Debugging
  Serial.begin(9600);
  
  //Get Addresses of DS Sensors
  Ds.getADDR();

  //Initialize I2C Communication with the robot
  Wire.begin(0x01);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() 
{
  /*
  Ds.getTemp();
  Ds.convertTemp(sendArray);
  delay(1000);
  /**/
}

void requestEvent()
{
  for (int x = 0; x < 4; x++)
  {
    Wire.write((byte)sendArray[x]);
  }
}

void receiveEvent()
{
  
}

