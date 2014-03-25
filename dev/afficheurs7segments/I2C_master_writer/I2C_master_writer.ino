// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup()
{
  Wire.begin(1); // join i2c bus (address optional for master)
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
}

byte x = 0;

void loop()
{
  digitalWrite(8, LOW);
  digitalWrite(7, !digitalRead(7));

  Wire.beginTransmission(2);
  Wire.print(x);
  Wire.write('\n');  
  Wire.endTransmission();  

  digitalWrite(8, HIGH);
  x++;
  delay(500);
}

