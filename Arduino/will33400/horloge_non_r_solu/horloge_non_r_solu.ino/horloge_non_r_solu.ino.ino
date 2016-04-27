 
#include <Wire.h>
#include "DS1307.h"

DS1307 clock;//define a object of DS1307 class

#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;

int led = 3;
int bp = 2;
boolean state = true;

void setup()
{
   lcd.begin(16, 2);
  
  Serial.begin(9600);
  clock.begin();
  clock.fillByYMD(2013,1,19);//Jan 19,2013
  clock.fillByHMS(15,28,30);//15:28 30"
  clock.fillDayOfWeek(SAT);//Saturday
  clock.setTime();//write time to the RTC chip

pinMode(led, OUTPUT);
}
void loop()
{
  if (digitalRead (bp) == HIGH) {
     if (state == false) {
  digitalWrite (led, HIGH); 
lcd.noDisplay();
lcd.display();
lcd.print("C'est... GOUPIX!");
}
else {
lcd.clear();
delay(10);
}
state = !state;
delay (200);
  printTime();
}
}
/*Function: Display time on the serial monitor*/
void printTime()
{
  clock.getTime();
  Serial.print(clock.hour, DEC);
  Serial.print(":");
  Serial.print(clock.minute, DEC);
  Serial.print(":");
  Serial.print(clock.second, DEC);
  Serial.print("  ");
  Serial.print(clock.month, DEC);
  Serial.print("/");
  Serial.print(clock.dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(clock.year+2000, DEC);
  Serial.print(" ");
  Serial.print(clock.dayOfMonth);
  Serial.print("*");
  switch (clock.dayOfWeek)// Friendly printout the weekday
  {
    case MON:
      Serial.print("MON");
      break;
    case TUE:
      Serial.print("TUE");
      break;
    case WED:
      Serial.print("WED");
      break;
    case THU:
      Serial.print("THU");
      break;
    case FRI:
      Serial.print("FRI");
      break;
    case SAT:
      Serial.print("SAT");
      break;
    case SUN:
      Serial.print("SUN");
      break;
  }
  Serial.println(" ");
}



