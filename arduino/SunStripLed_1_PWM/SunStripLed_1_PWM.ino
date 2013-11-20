

#include <Wire.h>
#include <PCA9685_ESIEESPACE.h>

#define OEpin A3

PCA9685_ESIEESPACE pwm = PCA9685_ESIEESPACE(0x41);

void setup() {
  pinMode(OEpin, OUTPUT);
  digitalWrite(OEpin, LOW);
  Serial.begin(9600);
  Serial.println("\n----\n16 channel PWM test!");

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!

  pwm.begin();
  pwm.setPWMFreq(500);  //  maximum PWM frequency = 1600 Hz
    
  // save I2C bitrate
  uint8_t twbrbackup = TWBR;
  // must be changed after calling Wire.begin() (inside pwm.begin())
  TWBR = 12; // upgrade to 400KHz!
  
  pwm.test();
    
}

void loop() {
  // Drive each PWM in a 'wave'
  for (uint16_t i=0; i<4096; i += 8) {
    for (uint8_t pwmnum=0; pwmnum < 16; pwmnum++) {
      pwm.setPWM(pwmnum, 0, (i + (4096/16)*pwmnum) % 4096 );
    }
  }
}
