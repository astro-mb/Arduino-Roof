// Gestion de l'ouverture/fermeture du toit de l'obs mb
// Script pour Arduino NANO (compatible avec NANO ELEGOO V2 et V3)
// fonctionne avec le driver ASCOM mbRoof
// V1.1 du 08/12/2024
// Matthieu Bachschmidt
const byte RELAY = 5; // Relais du moteur
const byte CAPTEUROUVERT = 2; // capteur ouvert
const byte CAPTEURFERME = 3; // capteur fermé
int STATUS;
int MOVE=0; // 1 -> openning ; 2 -> closing ; 0 -> error
void setup() 
{
  // initialisation de la liaison série
  Serial.begin(9600);
  Serial.flush();
  pinMode(RELAY, OUTPUT);
  pinMode(CAPTEUROUVERT, INPUT_PULLUP);
  pinMode(CAPTEURFERME,  INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(CAPTEUROUVERT), OnOpened, FALLING);
  attachInterrupt(digitalPinToInterrupt(CAPTEURFERME), OnClosed, FALLING);
}

void loop()
{
  String cmd;
  if (Serial.available() >0)
  {
    cmd = Serial.readStringUntil('#');
    if (cmd=="OPEN")
    {
      //int CapteurCLOSE = digitalRead(CAPTEUROUVERT);
      // if (digitalRead(CAPTEUROUVERT) == LOW) // le toit est déjà ouvert
      // {
      //   Serial.println(1, DEC);
      // }
      // else
      // {
        digitalWrite(RELAY, HIGH);
        MOVE=1;
        delay(1000);
        digitalWrite(RELAY, LOW);
    //  }
    }
    if (cmd=="CLOSE")
    {
      // if (digitalRead(CAPTEURFERME) == LOW) // le toit est déjà fermé
      // {
      //   Serial.println(2, DEC);
      // }
      // else
      // {
        digitalWrite(RELAY, HIGH);
        MOVE=2;
        delay(1000);
        digitalWrite(RELAY, LOW);
     // }
    }
    if (cmd=="STATUS")
    {
      int COPEN = digitalRead(CAPTEUROUVERT);
      int CCLOSE = digitalRead(CAPTEURFERME);
      if (COPEN == LOW)
      {
        Serial.println(1, DEC); // le toit est fermé
      }
      else if (CCLOSE == LOW)
      {
        Serial.println(2, DEC); // le toit est ouvert
      }
      else {
        if (MOVE==2)
        {
          Serial.println(3, DEC); // Closing
        }
        else if (MOVE==1)
         {
          Serial.println(4, DEC); // Opening
        }
        else
        {
          Serial.println(5, DEC); // error
        }

      }
    }
  }
}
void OnOpened()
{
  delay(20); // antiparasites
  int COPEN = digitalRead(CAPTEUROUVERT);
  if (COPEN == LOW)
  {
    MOVE=0;
  }
}

void OnClosed()
{
  delay(20);// antiparasites
  int CCLOSE = digitalRead(CAPTEURFERME);
  if (CCLOSE == LOW)
  {
     MOVE=0;
  }
}