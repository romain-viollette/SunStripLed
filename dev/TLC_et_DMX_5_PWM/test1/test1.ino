#include <Wire.h>

// include the I2C code

/*
this works, and lights up all LEDS with the same amount of drive
it is a very simple program to configure the PCA9685 for auto index
addressing. and light up the LEDS with a ramp of light and restart
takes about 2 seconds to loop through

The intention is just as an introduction to the PCA9685 device setup
and configuration to save time for new users

The hardware is very simple A0 is tied high all other addresses low, LEDS are connected between DVDD and 
all outputs with no series resistor. EO is tied to ground, the clock pin is left open, when tieing off 
I2C addresses to ground don't forget A6 it is on the oposite side of the chip next to OE.

Notes on hardware:
I had a very difficult time without external resistors, used 110 ohms in series with each LED, and ran using 5 volts on arduino.

Best results were with an external supply for the LEDs.

*/


 
// Define some key items for the device
#define I2CADDRESS 0x0A // not required for this example, but sets up Arduino address to be master latter
#define PCA9685 0x40 //0x41 // I2C address for PCA9865 with all inputs at zero except A0 which is at DVDD
#define MODE1 0x00 // location for Mode1 register address
#define MODE2 0x01 // location for Mode2 reigster address
#define LED0 0x06 // location for start of LED0 registers
#define LEDCOUNT 15 // number of LEDS to light 15 max
byte count = 0;


#define pinOE         A3 //Low-state active
void setup()
{
  TWBR = 12; // I2C upgrade to 400KHz!
  
  pinMode(pinOE, OUTPUT);
  digitalWrite(pinOE, LOW);
Serial.begin(9600); // set up serial
Serial.print("Start\r\n");

Wire.begin(); // also set this device to address 4, not required


// set up for output
Wire.begin();
delay(1);
Wire.beginTransmission(PCA9685);
Wire.write(MODE1);
Wire.write(0x01); // reset the device
Wire.endTransmission();
delay(1);
// restart
Wire.beginTransmission(PCA9685);
Wire.write(MODE1);
//Wire.write(0x81); // set to output if you don't want auto increment
Wire.write(0xa1); // set up for auto increment
Wire.endTransmission();

// set up for tristate outputs
Wire.beginTransmission(PCA9685);
Wire.write(MODE2);
Wire.write(0x10); // set to output
Wire.endTransmission();
// loop through and turn all on with a start of 0x0001 and stop of 003f
for(int i = 0; i<=LEDCOUNT; i++) 
{

/*Serial.print(i, DEC);
Serial.print(" <= LED number ");
Serial.print(LED0 + 4 * i, DEC);
Serial.print(" <= start of LED register space ");
Serial.print(LED0 + 4 * i + 4, DEC);
Serial.print(" <= last register of LED space addressed ");
Serial.println();*/
Wire.beginTransmission(PCA9685);
Wire.write(LED0 + 4 * i);
Wire.write(0x00); // set to output start lsb
Wire.write(0x00); // set to output start lmsb
Wire.write(0x10); // set to output end lsb
Wire.write(0x03); // set to output end msb
Wire.endTransmission();

}// end for loop

}// end setup

void loop()
{
Serial.print(count, DEC);
Serial.print(" term count ");
Serial.println();
for(int i = 0; i<=LEDCOUNT; i++) 
{ 
Wire.beginTransmission(PCA9685);
Wire.write(LED0 + 4 * i);
Wire.write(0x00); // set to output start lsb
Wire.write(0x00); // set to output start lmsb
Wire.write(0xff); // set to output end lsb
Wire.write(count); // set to output end msb
Wire.endTransmission();
}// end for loop

count = count + 0x02; // sets count rate
if( count == 0x0f){ count = 0;} // reset the counter when upper nibble reaches full scale

delay(100); // slows count rate, but serial print statements have a large influence on the count rate

}// end loop()
