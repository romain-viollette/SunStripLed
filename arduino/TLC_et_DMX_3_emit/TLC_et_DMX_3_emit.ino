
#include <Tlc5940.h>

#include <DMXSerial.h>
#define DMXModeSelectorPin 4

void setup()
{
  Tlc.init();
  pinMode(DMXModeSelectorPin,INPUT);

}

void loop()
{
  if(digitalRead(DMXModeSelectorPin))
  {
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
          Tlc.set(chanel, value<<4) ;
         else
          Tlc.set(chanel, (255-value)<<4) ; 
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
      delayMicroseconds(10000);
      Tlc.update();
    }//while(1)
  }//if - DMXController
  else
  {
    DMXSerial.init(DMXReceiver);
    while(1)
    {
      Tlc.clear();
      while(!DMXSerial.isIDLE());
      for(int chanel = 0; chanel<NUM_TLCS*16; chanel++)
      {
        Tlc.set(chanel, DMXSerial.read(chanel+1)<<4) ;  
      }  

      //while(!DMXSerial.isIDLE());
      Tlc.update();   
    }//while(1)
  }//else - DMXReceiver
}//loop()








