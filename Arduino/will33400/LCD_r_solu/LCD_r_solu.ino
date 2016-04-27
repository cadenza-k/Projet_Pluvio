
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;

int led = 3;

int bp = 2;
boolean state = true;

void setup() {
 lcd.begin(16, 2);
pinMode(led, OUTPUT);


}
void loop() {
  if (digitalRead (bp) == HIGH) {
     if (state == false) {
       
digitalWrite (led, HIGH); 
lcd.noDisplay();
lcd.display();
lcd.print("C'est... GOUPIX!");

}
else {
  
digitalWrite (led, LOW);

lcd.clear();
delay(10);
}
Serial.println(" ");
state = !state;
delay (200);
}
}
