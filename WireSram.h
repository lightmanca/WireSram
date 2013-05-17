/*
  WireSram.h - Library for I2c Sram, PCF8570P/FS,112
  Warning: Manufacturer says this chip will discontinuted.
  
  Created by Sam Weiss, May 15, 2013.
  Released into the public domain.
*/
#ifndef WireSram_h
#define WireSram_h

#include "Arduino.h"
#include <Wire.h>

class WireSram
{
  public:
    WireSram(int i2cAddress, int sleepPin, bool initializeWire = true);
    void writeByte (int i2c_addr,  word dataAddress, byte data);
    void writeBytes(int i2c_addr, word dataAddress, byte* data, int len);
    byte readByte  (int i2c_addr,   word dataAddress);
    void readBytes (int i2c_addr,  word dataAddress, byte* buffer, int len);
    void sleep();
    void wake();
    bool isSleeping();

  private:
    int _i2cAddress;
    int _sleepPin;
    bool _isSleeping;
};

#endif