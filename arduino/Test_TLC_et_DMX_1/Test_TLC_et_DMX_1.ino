#include <Tlc5940.h>
#include <tlc_animations.h>
#include <tlc_config.h>
#include <tlc_fades.h>
#include <tlc_progmem_utils.h>
#include <tlc_servos.h>
#include <tlc_shifts.h>

#include <DMXSerial.h>

void setup()
{
  Tlc.init();
DMXSerial.init(DMXReceiver);
}

void loop()
{
    Tlc.clear();
    for(int chanel = 0; chanel<4; chanel++)
    {
      Tlc.set(chanel, DMXSerial.read(chanel+1)*16) ;
    }
    Tlc.update();
}

