#ifndef _DS18x20_hpp
#define _DS18x20_hpp

#include <Arduino.h>
#include <OneWire.h>

class DSTemp
{
  public:
    DSTemp();
    OneWire ds = OneWire(4);
    void getADDR();
    void getTemp();
    void convertTemp(float dumpArray[4]);
    

  private:
    int HighByte, LowByte, TReading, SignBit, TempF, Whole, Fract;
    const static int numDevice = 4;
    byte addr[numDevice][8];
    byte data[numDevice][12];
};

#endif

