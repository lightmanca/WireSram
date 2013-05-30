/*
  WireSram.cpp - Library for I2c Sram, PCF8570P/FS,112
  Warning: Manufacturer says this chip will discontinuted.
  
  Created by Sam Weiss, May 15, 2013.
  Released into the public domain.
*/

#include <Wire.h>
#include "Arduino.h"
#include "WireSram.h"

//sleepPin can be set to -1 if you do not want sleep function.
WireSram::WireSram(int i2cAddress, int sleepPin, bool initializeWire) {
    _i2cAddress = i2cAddress;
    _sleepPin = sleepPin;
    _isSleeping = false;
    if(_sleepPin > 0) {
        pinMode(_sleepPin, OUTPUT);
        digitalWrite(_sleepPin, LOW);
    }
    if(initializeWire)
        Wire.begin();
}

void WireSram::sleep() {
    if(_sleepPin < 0)
        return;
    digitalWrite(_sleepPin, HIGH);
    _isSleeping=true;
}

void WireSram::wake() {
    if(_sleepPin < 0) 
        return;
    digitalWrite(_sleepPin, LOW);
    delayMicroseconds(55);
    _isSleeping=false;
}

bool WireSram::isSleeping() {
    return _isSleeping;
}

//Write 1 byte to i2c SRAM
void WireSram::writeByte(word address, byte data)
{
  Wire.beginTransmission(_i2cAddress);
  Wire.write((byte)lowByte(address)); 
  Wire.write((byte)highByte(address)); 
  Wire.write(data); 
  Wire.endTransmission(); 
}

//Write data buffer to i2c SRAM
void WireSram::writeBytes(word address, byte* data, int len)
{
  Wire.beginTransmission(_i2cAddress);
  Wire.write((byte)lowByte(address)); 
  Wire.write((byte)highByte(address)); 
  Wire.write(data, len);
  Wire.endTransmission(); 
}

//Read byte from i2c SRAM
byte WireSram::readByte(word address)
{
  Wire.beginTransmission(_i2cAddress);
  Wire.write((byte)lowByte(address)); 
  Wire.write((byte)highByte(address)); 
  Wire.endTransmission();
  Wire.requestFrom(_i2cAddress,1); //only one byte

  if(Wire.available())
  { return Wire.read(); } 
  return B00000000; //FIXME - Report an error here
}

//Read from i2c SRAM into data buffer
void WireSram::readBytes(word address, byte* buffer, int len)
{
  Wire.beginTransmission(_i2cAddress);
  Wire.write((byte)lowByte(address)); 
  Wire.write((byte)highByte(address)); 
  Wire.endTransmission();
  Wire.requestFrom(_i2cAddress, len); //only one byte
  int i = 0;
  while(Wire.available() && i < len) {
    *(buffer + i) = Wire.read(); 
    i++;
  } 
}

void WireSram::Erase(int startAddress, int numBytes) {
    for(int i = startAddress; i <= numBytes; i++)
        writeByte(i, (byte)'\0');
}
