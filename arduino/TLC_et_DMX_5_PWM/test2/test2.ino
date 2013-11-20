#include "twimaster.c"

#define PCA9685  0x41
#define SWRST  B00000110

//Register defines from data sheet
#define PCA9685_MODE1 0x00 // location for Mode1 register address
#define PCA9685_MODE2 0x01 // location for Mode2 reigster address
#define PCA9685_LED0 0x06 // location for start of LED0 registers


#define LED0 0x06 // location for start of LED0 registers
#define LEDCOUNT 15 // number of LEDS to light 15 max

int count = 0;

void setup()
{
  unsigned char ret = 0;
  Serial.begin(115200);
  Serial.write("\n------");

  i2c_init();                             // initialize I2C library
  delayMicroseconds(700);

  /*ret = i2c_start(0x00);     
   Serial.print("\ni2c_start(0x00) : 0x");
   Serial.print(ret,HEX);
   ret = i2c_write(SWRST);     
   Serial.write("\ni2c_write(SWRST) : 0x");
   Serial.print(ret,HEX);
   i2c_stop(); 
   delayMicroseconds(600);*/



  //restart 
  ret = i2c_start(PCA9685<<1+I2C_WRITE);     
  Serial.write("\ni2c_start(PCA9685<<1+I2C_WRITE) : 0x");
  Serial.print(ret,HEX);

  ret = i2c_write(PCA9685_MODE1);     
  Serial.write("\ni2c_write(PCA9685_MODE1) : 0x");
  Serial.print(ret,HEX);

  ret = i2c_write(0x01);     
  Serial.write("\ni2c_write(0x01) : 0x");
  Serial.println(ret,HEX);

  i2c_stop();
  delayMicroseconds(700);

  //auto increment
  ret = i2c_start(PCA9685<<1+I2C_WRITE);     
  Serial.write("\ni2c_start(PCA9685<<1+I2C_WRITE) : 0x");
  Serial.print(ret,HEX);

  ret = i2c_write(PCA9685_MODE2);     
  Serial.write("\ni2c_write(PCA9685_MODE2) : 0x");
  Serial.print(ret,HEX);

  ret = i2c_write(0x10);     
  Serial.write("\ni2c_write(0x10) : 0x");
  Serial.println(ret,HEX);
  
  i2c_stop();
  delayMicroseconds(700);

  //tristate
  ret = i2c_start(PCA9685<<1+I2C_WRITE);     
  Serial.write("\ni2c_start(PCA9685<<1+I2C_WRITE) : 0x");
  Serial.print(ret,HEX);

  ret = i2c_write(PCA9685_MODE1);     
  Serial.write("\ni2c_write(PCA9685_MODE1) : 0x");
  Serial.print(ret,HEX);

  ret = i2c_write(0xa1);     
  Serial.write("\ni2c_write(0xa1) : 0x");
  Serial.println(ret,HEX);

  i2c_stop();
  delayMicroseconds(700);

  // loop through and turn all on with a start of 0x0001 and stop of 003f
  for(int i = 0; i<=LEDCOUNT; i++)
  {
    i2c_start(PCA9685<<1+I2C_WRITE); 
    i2c_write(LED0 + 4 * i);
    i2c_write(0x00); // set to output start lsb
    i2c_write(0x00); // set to output start lmsb
    i2c_write(0x10); // set to output end lsb
    i2c_write(0x03); // set to output end msb
    i2c_stop();

  }// end for loop

}

void loop()
{
  for(int i = 0; i<=LEDCOUNT; i++)
  {
    i2c_start(PCA9685<<1+I2C_WRITE);
    i2c_write(LED0 + 4 * i);
    i2c_write(0x00); // set to output start lsb
    i2c_write(0x00); // set to output start lmsb
    i2c_write(0xff); // set to output end lsb
    i2c_write(count); // set to output end msb
    i2c_stop();
  }// end for loop

    count = count + 0x02; // sets count rate
  if( count == 0x0f){ 
    count = 0;
  } // reset the counter when upper nibble reaches full scale

  delay(10); // slows count rate, but serial print statements have a large influence on the count rate
}








