/*#include <Tlc5940.h>
 #include <tlc_animations.h>
 #include <tlc_config.h>
 #include <tlc_fades.h>
 #include <tlc_progmem_utils.h>
 #include <tlc_servos.h>
 #include <tlc_shifts.h>
 */
#include <DMXSerial.h>

#define LedPin  A5

void setup()
{
  pinMode(LedPin, OUTPUT);
  digitalWrite(LedPin,HIGH);
  delay(500);
  digitalWrite(LedPin,LOW);
  DMXSerial.init(DMXReceiver);

}

void loop()
{  
  digitalWrite(LedPin,DMXSerial.read(1)<50?LOW:HIGH);
}


