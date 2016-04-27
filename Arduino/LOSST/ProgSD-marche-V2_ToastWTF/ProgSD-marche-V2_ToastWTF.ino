

#include <SPI.h>
#include <SD.h>

File Fichier;
char inputString [100];
char inputChar;
int stringIndex = 0; // String stringIndexing int;

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

//lblblblblblblblblblblblblbl

      // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  Fichier = SD.open("DATE.xml", FILE_WRITE); //Ajouter datage dans le nom

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
//Test
inputChar = Fichier.read(); // Gets one byte from serial buffer
  if (inputChar != '°') // define breaking char here (\n isnt working for some reason, i will follow this up later)
    {
    inputString[stringIndex] = inputChar; // Store it
    stringIndex++; // Increment where to write next
  }
  else 
  {
    Serial.print("test: "); // shows that the program is cycling, for debugging only
    Serial.println(inputString);
    delay (1000);
    stringIndex = 0; // clear the value for the next cycle
    inputString [100]; // clear the value for the next cycle?
  }
}


