unsigned int NombreDeTic = 0;
unsigned int HauteurEau = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
    Serial.println(sensorValue);
  if(sensorValue == 1023) {
    //Ajouter une boucle d'une heure
    ++NombreDeTic;
    if(NombreDeTic == 5){
    ++HauteurEau;
    NombreDeTic = 0;
    }
  }
  delay(1000);        // delay in between reads for stability
}
