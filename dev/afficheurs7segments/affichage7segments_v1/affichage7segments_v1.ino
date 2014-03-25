static const uint8_t L1 = 14;
static const uint8_t L2 = 10;
static const uint8_t L3 = 6;
static const uint8_t A = 17;
static const uint8_t B = 2;
static const uint8_t C = 9;
static const uint8_t D = 16;
static const uint8_t E = 15;
static const uint8_t F = 4;
static const uint8_t G = 3;
static const uint8_t LED1 = 7;
static const uint8_t LED2 = 8;

void setup()
{
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
  digitalWrite(G, LOW);

  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  digitalWrite(L1, LOW);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
}

void loop()
{
  
  int i,j;
  for(i=0; i<3; i++)
  {
    digitalWrite(L1, (i==0)?HIGH:LOW);
    digitalWrite(L2, (i==1)?HIGH:LOW);
    digitalWrite(L3, (i==2)?HIGH:LOW);
    for(j=0; j<7; j++)
    {
      digitalWrite(A, (j==5)?LOW:HIGH);
      digitalWrite(B, (j==6)?LOW:HIGH);
      digitalWrite(C, (j==1)?LOW:HIGH);
      digitalWrite(D, (j==2)?LOW:HIGH);
      digitalWrite(E, (j==3)?LOW:HIGH);
      digitalWrite(F, (j==4)?LOW:HIGH);
      digitalWrite(G, (j==0)?LOW:HIGH);
      
      digitalWrite(LED1, digitalRead(LED1)?LOW:HIGH);
      digitalWrite(LED2, digitalRead(LED2)?LOW:HIGH);
      
      delay(300);
      Serial.print(".");
    } 
  }

}



