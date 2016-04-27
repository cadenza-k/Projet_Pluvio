 
#include <Wire.h>
#include "DS1307.h"

DS1307 clock;

#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>


byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
unsigned int localPort = 8888;

char timeServer[] = "time.nist.gov";

const int NTP_PACKET_SIZE = 48;

byte packetBuffer[ NTP_PACKET_SIZE];

int led = 3;
int bp = 2;
boolean state = true;

void setup()
{
   Serial.begin(9600);
  while (!Serial) {
    ;
  }

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
  
    for (;;)
      ;
  }
  Udp.begin(localPort);
}

   lcd.begin(16, 2);
  
  Serial.begin(9600);
  clock.begin();
  clock.fillByYMD(2013,1,19);
  clock.fillByHMS(15,28,30);
  clock.fillDayOfWeek(SAT);
  clock.setTime();

pinMode(led, OUTPUT);
}
void loop()
{
   sendNTPpacket(timeServer);

  delay(1000);
  if (Udp.parsePacket()) {
    Udp.read(packetBuffer, NTP_PACKET_SIZE);

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    Serial.print("Seconds since Jan 1 1900 = ");
    Serial.println(secsSince1900);

    Serial.print("Unix time = ");
    const unsigned long seventyYears = 2208988800UL;
    unsigned long epoch = secsSince1900 - seventyYears;
    Serial.println(epoch);
    Serial.print("The UTC time is ");
    Serial.print((epoch  % 86400L) / 3600);
    Serial.print(':');
    if (((epoch % 3600) / 60) < 10) {
      Serial.print('0');
    }
    Serial.print((epoch  % 3600) / 60); 
    Serial.print(':');
    if ((epoch % 60) < 10) {

      Serial.print('0');
    }
    Serial.println(epoch % 60);
  }

  delay(10000);
  Ethernet.maintain();
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
  switch (clock.dayOfWeek)
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

void sendNTPpacket(char* address) {
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  packetBuffer[0] = 0b11100011;
  packetBuffer[1] = 0;
  packetBuffer[2] = 6;
  packetBuffer[3] = 0xEC;
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  Udp.beginPacket(address, 123);
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

