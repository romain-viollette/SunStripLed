static const uint8_t L1   = 14;
static const uint8_t L2   = 10;
static const uint8_t L3   = 6;
static const uint8_t A    = 17;
static const uint8_t B    = 2;
static const uint8_t C    = 9;
static const uint8_t D    = 16;
static const uint8_t E    = 15;
static const uint8_t F    = 4;
static const uint8_t G    = 3;
static const uint8_t LED1 = 7;
static const uint8_t LED2 = 8;

static const uint8_t segmentPinTable[7] = {A, B, C, D, E, F, G};

static uint8_t displayCtr = 0;
static uint8_t segmentCtr = 0;

static uint8_t displayValue[3];

void setup()
{
  for(displayCtr=0; displayCtr<3; displayCtr++)
  {
    for(segmentCtr=0; segmentCtr<7; segmentCtr++)
    {
      displayValue[displayCtr]= 1;
    }
  }
  displayCtr=0;
  segmentCtr=0;

  Serial.begin(9600);
  delay(1);
  Serial.println("\n-= Affichage 7 segments =-");
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);

  digitalWrite(L1, HIGH);
  digitalWrite(L2, HIGH);
  digitalWrite(L3, HIGH);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
}

void loop()
{
  digitalWrite(segmentPinTable[segmentCtr], LOW);
  
  
  digitalWrite(L1, displayValue[0] & (1<<segmentCtr));
  digitalWrite(L2, displayValue[1] & (1<<segmentCtr));
  digitalWrite(L3, displayValue[2] & (1<<segmentCtr));

  segmentCtr++;
  if(segmentCtr>=7)
  {
    segmentCtr=0;
    displayCtr++;
    if(displayCtr>=3)
      displayCtr=0;
  }

  if(millis()%1000==0)
  {
    Serial.print(".");
    static byte inc=0;
    displayValue[inc%3]= 0;
    displayValue[(inc-1)%3]= 1;
    inc++;
  }

}








