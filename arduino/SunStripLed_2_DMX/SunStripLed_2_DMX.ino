#include <Wire.h>
#include <PCA9685_ESIEESPACE.h>
#define PCA9685_OEpin A3

#include <DMXSerial.h>

PCA9685_ESIEESPACE pwm = PCA9685_ESIEESPACE(0x41);
uint8_t DIPpin[9] = {
  A2, A1, A0, 3 ,4 ,5 , 6, 7, 8};
uint16_t DIPstate = 0x00;
uint16_t DMX_addr = 0x00;


void setup() {
  //DIP SWITCH
  for(uint8_t pin=0; pin < 9; pin++)
  {
    pinMode(DIPpin[pin], INPUT);
    digitalWrite(DIPpin[pin], HIGH);
  }
  DMX_addr = getDIPstate();

  //PC9685
  pinMode(PCA9685_OEpin, OUTPUT);
  digitalWrite(PCA9685_OEpin, LOW);
  pwm.begin();
  pwm.setPWMFreq(500);  //  maximum PWM frequency = 1600 Hz
  TWBR = 12; // upgrade to 400KHz!

  //DMX

}

void loop() {
  if(DMX_addr<=0)
  { //DMXController
    DMXSerial.maxChannel(DMXSERIAL_MAX);
    DMXSerial.init(DMXController);
    int value = 0;
    while(1)
    {
      for(int chanel = 0; chanel <4*16; chanel++)
      {
        if(chanel<16)
        {
          if((chanel+1-16)%2)
            pwm.setPWM(chanel, 0, value<<4);
          else
            pwm.setPWM(chanel, 0, (255-value)<<4); 
        }
        else
        {
          if((chanel+1-16)%2)
            DMXSerial.write(chanel+1-16,value);
          else
            DMXSerial.write(chanel+1-16,255-value);
        }
      }
      value++;
      if (value > 255) value = 0;
      delayMicroseconds(5000);
      
      DMX_addr = getDIPstate();
      if(DMX_addr > 0) break;
      
    }//while(1)
  }//if - DMXController
  else
  { //DMXReceiver
    DMXSerial.init(DMXReceiver);
    while(1)
    {
      while(!DMXSerial.isIDLE());  
      for (uint8_t chanel=0; chanel < 16; chanel++)
      {
        pwm.setPWM(chanel, 0, DMXSerial.read(DMX_addr + chanel)<<4);
      }
      DMX_addr = getDIPstate();
      if(DMX_addr <=0) break;
    }
  }//else - DMXReceiver
}

uint16_t getDIPstate()
{
  DIPstate = 0x00;
  for(uint8_t pin=0; pin < 9; pin++)
  {
    DIPstate |= ((digitalRead(DIPpin[pin])?0:1)<<pin);
  }
  return DIPstate;
}





