#include <Wire.h>
#include <PCA9685.h>
PCA9685 ledDrv;

#define PWM_FREQ      200
#define PCA9685_ADDR  0x01 //0x41
#define pinOE         A3 //Low-state active
#define pinDebug      8

void setup()
{
  Serial.begin(9600); // set up serial
  Serial.print("\r\n\r\nStart\r\n");

  pinMode(pinOE, OUTPUT);
  digitalWrite(pinOE, HIGH);

  ledDrv.begin(PCA9685_ADDR);
  
  Serial.print("init() : ");
  Serial.print(ledDrv.init());
  ledDrv.tests();
  
  digitalWrite(pinOE, LOW);
}

void loop()
{    
  for(int level=5;level>=0;level--)  {
    for(int i=0; i<16; i++)  {
      ledDrv.setLEDDimmed(i,level*20);
      delay(10);     
    }
  }
  for(int level=0;level<=5;level++)  {
    for(int i=0; i<16; i++)  {
      ledDrv.setLEDDimmed(i,level*20);
      delay(10);     
    }
  }

}//loop()













