
const int ShiftPWM_latchPin=3;
const bool ShiftPWM_invertOutputs = true;
const bool ShiftPWM_balanceLoad = false;
#include <ShiftPWM.h>

#include <DMXSerial.h>
#define DMXModeSelectorPin 4


const int pwmFrequency = 75;
const unsigned char pwmMaxValue = 255;
const int numRegisters = 1;
// Function prototypes (telling the compiler these functions exist).
void oneByOne(void);
void inOutTwoLeds(void);
void inOutAll(void);
void alternatingColors(void);
void hueShiftAll(void);
void randomColors(void);
void fakeVuMeter(void);
void rgbLedRainbow(unsigned long cycleTime, int rainbowWidth);
void printInstructions(void);

void setup()
{
  ShiftPWM.SetAmountOfRegisters(numRegisters);
  ShiftPWM.Start(pwmFrequency,pwmMaxValue);
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
        if(chanel<8) //<16
        {
         if(chanel%2)
          ShiftPWM.SetOne(chanel, value);
         else
          ShiftPWM.SetOne(chanel, 255-value); 
        }
        else
        {
          if(chanel%2)
            DMXSerial.write(chanel+1-16,value);
          else
              DMXSerial.write(chanel+1-16,255-value);
        }
      }
      value++;
      if (value > 255) value = 0;
      delayMicroseconds(10000);
    }//while(1)
  }//if - DMXController
  else
  {
    DMXSerial.init(DMXReceiver);
    while(1)
    {
      while(!DMXSerial.isIDLE());
      for(int chanel = 0; chanel<8; chanel++)
      {
         ShiftPWM.SetOne(chanel, DMXSerial.read(chanel+1));
      }  

      //while(!DMXSerial.isIDLE());
    }//while(1)
  }//else - DMXReceiver
}//loop()








