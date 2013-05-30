#include <Wire.h>

#include <WireSram.h>

//ram i2c address
int addr = 82; //B1010011;

//string to write
byte str[] = "arduino_related";
byte buffer[20] = {0};

WireSram sram(addr, 6);

void setup()
{
  Serial.begin(9600); 
  Serial.println("Saving String to sram");
  //write str to ram
  sram.writeBytes(0, (byte*) "Sram Test. Dr. Who", 19);
  Serial.println("Sleeping...");
  sram.sleep();
  delay(1000);
}

void loop()
{
  Serial.print("Is sram sleeping? ");
  Serial.println(sram.isSleeping());
  Serial.println("Waking up Sram");
  sram.wake();
  Serial.print("Is sram sleeping? ");
  Serial.println(sram.isSleeping());
  sram.readBytes(0, buffer, 19);
  Serial.print((char*)buffer);
  Serial.println(" is awesome.");
  Serial.println("Sleeping...");
  sram.sleep();
  delay(500);
}

