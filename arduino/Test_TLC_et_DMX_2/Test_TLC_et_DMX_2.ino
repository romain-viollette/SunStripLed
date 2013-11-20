
#include <Tlc5940.h>

#include <DMXSerial.h>

void setup()
{
  Tlc.init();
  DMXSerial.init(DMXReceiver);
}

void loop()
{
  Tlc.clear();
  while(!DMXSerial.isIDLE());
  for(int chanel = 0; chanel<NUM_TLCS*16; chanel++)
  {
    Tlc.set(chanel, DMXSerial.read(chanel+1)<<4) ;
  }  

  //while(!DMXSerial.isIDLE());
  Tlc.update();  
}



