#include <Arduino.h>
#include <OneWire.h>
#include "Ds18x20.h"

DSTemp::DSTemp()
{

}

/*
Convert the data to actual temperature
because the result is a 16 bit signed integer, it should
be stored to an "int16_t" type, which is always 16 bits
even when compiled on a 32 bit processor.
/**/
void DSTemp::convertTemp(float dumpArray[4])
{
  for (int x = 0; x < numDevice; x++)
  {
    LowByte = data[x][0];
    HighByte = data[x][1];
    TReading = (HighByte << 8) + LowByte;
    SignBit = TReading & 0x8000;  // test most sig bit
    if (SignBit) // negative
    {
      TReading = (TReading ^ 0xffff) + 1; // 2's comp
    }
    //TempF = (((((6 * TReading) + TReading / 4) * 9) / 5) + 32);    
    TempF = (6 * TReading) + TReading / 4;

    /*
    if (SignBit) //If negative make output negative
    {
      TempF = TempF * -1;
    }
    else //Else nothing happens
    {
      TempF = TempF;
    }
    /**/
    
    dumpArray[x] = TempF;
    
    Serial.print(x);
    Serial.print(": ");
    
    Whole = TempF / 100;  // separate off the whole and fractional portions
    Fract = TempF % 100;
    if (SignBit) // If its negative
    {
      Serial.print("-");
    }
    Serial.print(Whole);
    Serial.print(".");
    if (Fract < 10)
    {
      Serial.print("0");
    }
    Serial.print(Fract);

    Serial.print("\n");
  }
}

void DSTemp::getTemp()
{
  for (int x = 0; x < numDevice; x++)
  {
    if (OneWire::crc8(addr[x], 7) != addr[x][7])
    {
      Serial.println("CRC is not valid");
      return;
    }
    //Outputs what Family the Device is from
    if (addr[x][0] == 0x10)
    {
      Serial.println("Device is a DS18S20 family device.");
      return;
    }
    else if (addr[x][0] == 0x28) 
    {
      Serial.print("Device is a DS18B20 family device.\n");
    }
    else 
    {
      Serial.print("Device family is not recognized: 0x");
      Serial.println(addr[x][0],HEX);
      return;
    }
    
    ds.reset();
    ds.select(addr[x]);
    ds.write(0x44, 1);        // start conversion, with parasite power on at the end

    delay(750);              // maybe 750ms is enough, maybe not
    // we might do a ds.depower() here, but the reset will take care of it.

    ds.reset();
    ds.select(addr[x]);
    ds.write(0xBE);           // Read Scratchpad

    for (int i = 0; i < 9; i++)  // we need 9 bytes
    {
      data[x][i] = ds.read();
    }
  }
}

void DSTemp::printADDR()
{
  for (int x = 0; x < numDevice; x++)
  {
    for (int y = 0; y < 8; y++)
    {
      Serial.print(addr[x][y]);
    }
  }
}
