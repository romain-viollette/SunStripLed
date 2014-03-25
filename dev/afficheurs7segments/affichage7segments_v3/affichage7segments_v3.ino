static const uint8_t PIN_L1 =   0; //PC0  //14
static const uint8_t PIN_L2 =   2; //PB2  //10
static const uint8_t PIN_L3 =   6; //PD6; //6
static const uint8_t PIN_A =    3; //PC3; //17
static const uint8_t PIN_B =    2; //PD2; //2
static const uint8_t PIN_C =    1; //PB1; //9
static const uint8_t PIN_D =    2; //PC2; //16
static const uint8_t PIN_E =    1; //PC1; //15
static const uint8_t PIN_F =    4; //PD4; //4
static const uint8_t PIN_G =    3; //PD3; //3
static const uint8_t PIN_LED1 = 7; //PD7; //7
static const uint8_t PIN_LED2 = 0; //PB0; //8

/*

 PORT B
 MSB                              LSB
 | 7 | 6 | 5 | 4 | 3 | 2  | 1 | 0   |
 | . | . | . | . | . | L2 | C | LED2|
 
 PORT C
 MSB                            LSB
 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0  |
 | . | . | . | . | A | D | E | L1 |
 
 PORT D
 MSB                               LSB
 | 7    | 6  | 5 | 4 | 3 | 2 | 1 | 0 |
 | LED1 | L3 | . | F | G | B | . | . |
 
 
 SEVEN SEGMENT DISPLAYS:
 ___L1__       ___L2__       ___L3__ 
 |   A   |     |   A   |     |   A   |    displayValue[x] = 0ABCDEFG;
 |F     B|     |F     B|     |F     B|
 |   G   |     |   G   |     |   G   |
 |E     C|     |E     C|     |E     C|
 |___D___|     |___D___|     |___D___|
 
 
 */

static uint8_t A, B, C , D, E, F, G;    //Active High
static uint8_t L1, L2, L3, LED1, LED2;  //Active Low

static const uint8_t DDRB_ = (1<<PIN_L2) | (1<<PIN_C) | (1<<PIN_LED2);
static const uint8_t DDRC_ = (1<<PIN_A) | (1<<PIN_D) | (1<<PIN_E) | (1<<PIN_L1);
static const uint8_t DDRD_ = (1<<PIN_LED1) | (1<<PIN_L3) | (1<<PIN_F) | (1<<PIN_G) | (1<<PIN_B);

static uint8_t displayValue[3] = {0b01110111, 0b00011111, 0b01001110}; //text: AbC

static uint8_t segmentCounter = 0;

void setup()
{
  Serial.begin(9600);
  delay(1);
  Serial.println("\n-= Affichage 7 segments =-");

  A=B=C=D=E=F=G=0;
  L1=L2=L3=LED1=LED2=1;
  
  displayValue[0] = convertAscii2Segment('1');
  displayValue[1] = convertAscii2Segment('2');
  displayValue[2] = convertAscii2Segment('3');

  //settings pins as outputs:
  DDRB |= DDRB_;
  DDRC |= DDRC_;
  DDRD |= DDRD_;

  //initialize outputs:
  PORTB = (PORTB & ~DDRB_) | (L2<<PIN_L2) | (C<<PIN_C) | (LED2<<PIN_LED2);
  PORTC = (PORTC & ~DDRC_) | (A<<PIN_A) | (D<<PIN_D) | (E<<PIN_E) | (L1<<L1);
  PORTD = (PORTD & ~DDRD_) | (LED1<<PIN_LED1) | (L3<<PIN_L3) | (F<<PIN_F) | (G<<PIN_G) | (B<<PIN_B);

}

void loop()
{

  A= (segmentCounter==6)?LOW:HIGH;
  B= (segmentCounter==5)?LOW:HIGH;
  C= (segmentCounter==4)?LOW:HIGH;
  D= (segmentCounter==3)?LOW:HIGH;
  E= (segmentCounter==2)?LOW:HIGH;
  F= (segmentCounter==1)?LOW:HIGH;
  G= (segmentCounter==0)?LOW:HIGH;

  L1= (displayValue[0]&(1<<segmentCounter))?HIGH:LOW;
  L2= (displayValue[1]&(1<<segmentCounter))?HIGH:LOW;
  L3= (displayValue[2]&(1<<segmentCounter))?HIGH:LOW;

  //writting outputs:
  PORTB = (PORTB & ~DDRB_) | (L2<<PIN_L2) | (C<<PIN_C) | (LED2<<PIN_LED2);
  PORTC = (PORTC & ~DDRC_) | (A<<PIN_A) | (D<<PIN_D) | (E<<PIN_E) | (L1<<PIN_L1);
  PORTD = (PORTD & ~DDRD_) | (LED1<<PIN_LED1) | (L3<<PIN_L3) | (F<<PIN_F) | (G<<PIN_G) | (B<<PIN_B);

  segmentCounter++;
  if(segmentCounter >= 7)
    segmentCounter=0;

  delayMicroseconds(1000);
}



uint8_t convertAscii2Segment(char ascii)
{
  switch(ascii)
  {
    case '0' : return 0b01111110;
    case '1' : return 0b00110000;
    case '2' : return 0b01101101;
    case '3' : return 0b01111001;
    case '4' : return 0b00110011;
    case '5' : return 0b01011011;
    case '6' : return 0b01011111;
    case '7' : return 0b01110000;
    case '8' : return 0b01111111;
    case '9' : return 0b01110011;
    
    case 'a' :
    case 'A' : return 0b01110111;
    
    case 'b' :
    case 'B' : return 0b00011111;
    
    case 'c' : return 0b00001101;
    case 'C' : return 0b01001110;
    
    case 'd' :
    case 'D' : return 0b00111101;
    
    case 'e' :
    case 'E' : return 0b01001111;
    
    case 'f' :
    case 'F' : return 0b01000111;
    
    case 'g' :
    case 'G' : return 0b01011110;
    
    case 'h' : return 0b00010111;
    case 'H' : return 0b00110111;
    
    case 'i' :
    case 'I' : return 0b00000110;
    
    case 'j' :
    case 'J' : return 0b00111100;
    
    case 'k' :
    case 'K' : return 0b01010111;
    
    case 'l' : return 0b00000110;
    case 'L' : return 0b00001110;
    
    case 'm' :
    case 'M' : return 0b00111110;
    
    case 'n' :
    case 'N' : return 0b00111110;
    
    case 'o' : return 0b00011101;
    case 'O' : return 0b01111110;
    
    case 'p' :
    case 'P' : return 0b01100111;
    
    case 'q' :
    case 'Q' : return 0b01110011;
    
    case 'r' :
    case 'R' : return 0b00000101;
    
    case 's' :
    case 'S' : return 0b01011011;
    
    case 't' :
    case 'T' : return 0b00001111;
    
    case 'u' : return 0b00011100;
    case 'U' : return 0b00111110;
    
    case 'v' : return 0b00011100;
    case 'V' : return 0b00111110;
    
    case 'w' : return 0b00011100;
    case 'W' : return 0b00111110;
    
    case 'x' :
    case 'X' : return 0b00100101;
    
    case 'y' :
    case 'Y' : return 0b0111011;
    
    case 'z' :
    case 'Z' : return 0b01101100;
    

    case '-' : return 0b00000001;
    case '_' : return 0b00001000;
    case '=' : return 0b00001001;
    case '"' : return 0b00100010;
    case '\'': return 0b00100000;
    case '`' : return 0b00000010;
    case '.' : return 0b00010000;
    case ' ' : return 0b00000000;
    
    default:   return 0b00001000; //'_'
  } 
}







