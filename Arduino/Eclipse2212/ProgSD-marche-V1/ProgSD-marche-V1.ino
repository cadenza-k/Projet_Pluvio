

#include <SPI.h>
#include <SD.h>

File GOUPIX;

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

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  GOUPIX = SD.open("chibre.xml", FILE_WRITE);

  // if the file opened okay, write to it:
  if (GOUPIX) {
    Serial.print("Writing to chibre.xml...");
    GOUPIX.println("C'est énorme");
    // close the file:
    GOUPIX.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  GOUPIX = SD.open("chibre.xml");
  if (GOUPIX) {
    Serial.println("chibre.xml:");

    // read from the file until there's nothing else in it:
    while (GOUPIX.available()) {
      Serial.write(GOUPIX.read());
    }
    // close the file:
    GOUPIX.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {
  // nothing happens after setup
}


