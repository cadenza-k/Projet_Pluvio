

#include <SPI.h>
#include <SD.h>

File Fichier;
String XmlSuffix = ".xml";
String FileName = "";

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

      // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  FileName = "Date" + XmlSuffix;
  Fichier = SD.open(FileName, FILE_WRITE); //Ajouter datage dans le nom

  // if the file opened okay, write to it:
  if (Fichier) {
    Serial.print("Writing to Date.xml...");
    Fichier.println("<?xml version = \"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>"); //échappement du prologue XML
    Fichier.println("<Pluviometre>");
    // close the file:
//    Fichier.close();

  }


}

void loop() {
//Rien pour l'instant
}


