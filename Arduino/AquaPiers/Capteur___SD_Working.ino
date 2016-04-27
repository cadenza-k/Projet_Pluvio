

#include <SPI.h>
#include <SD.h>

File Fichier;
//File Fichier2; 

String XmlSuffix = ".xml";
String FileName = "";

unsigned int NombreDeTic = 0;
unsigned int HauteurEau = 0;

//
//DEMANDER ADAM NOM VARIABLE DATE RTC
//

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  //Code Perso
//Fichier2 =  CreateFile();

  // close the file:
  //Fichier.close();
   FileName = "Date1" + XmlSuffix;
  Fichier = SD.open(FileName, FILE_WRITE); //Ajouter datage dans le nom
//Serial.print(Fichier);
  // if the file opened okay, write to it:
  
  if (Fichier) {
    Serial.print("Writing to " + FileName + "...");
    Fichier.println("<?xml version = \"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>"); //échappement du prologue XML
    Fichier.println("<Pluviometre>");

}
  while (Fichier.available()) {
      Serial.write(Fichier.read());
   // delay(1000);
    }
    Fichier.close();
}

void loop() {
  // read the input on analog pin 0:
//  int sensorValue = analogRead(A0);
//  // print out the value you read:
//  Serial.println(sensorValue);
//  if (sensorValue > 500) {
//    if (sensorValue == 0) {
//      //Ajouter une boucle d'une heure
//      NombreDeTic++;
//      if (NombreDeTic == 5) {
//        HauteurEau++;
//        NombreDeTic = 0;
//      }
//    }
//  }
  delay(1);// delay in between reads for stability
  //Serial.println(NombreDeTic);
//  Fichier.println(NombreDeTic);
//  
//  while (Fichier.available()) {
//      Serial.write(Fichier.read());
//    delay(1000);
//    }
}

File CreateFile() {
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  FileName = "Date1" + XmlSuffix;
  Fichier = SD.open(FileName, FILE_WRITE); //Ajouter datage dans le nom

  // if the file opened okay, write to it:
  if (Fichier) {
    Serial.print("Writing to " + FileName + "...");
    Fichier.println("<?xml version = \"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>"); //échappement du prologue XML
    Fichier.println("<Pluviometre>");
return Fichier; 
  }
}
