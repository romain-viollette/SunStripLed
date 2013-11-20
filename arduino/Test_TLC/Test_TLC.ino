#include <Tlc5940.h>
#include <tlc_animations.h>
#include <tlc_config.h>
#include <tlc_fades.h>
#include <tlc_progmem_utils.h>
#include <tlc_servos.h>
#include <tlc_shifts.h>

//#include <DMXSerial.h>

void setup()
{
  Tlc.init();

}

void loop()
{
  for(int greyscale=0 ; greyscale <4096; greyscale++)
  {
    Tlc.clear();
    for(int chanel = 0; chanel<4; chanel++)
    {
      Tlc.set(chanel, greyscale) ;
    }
    Tlc.update();
    delay(1);
  }
}

