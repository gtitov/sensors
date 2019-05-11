#include <SPI.h>
#include <LoRa.h>
#include <Ultrasonic.h>
#include <WEMOS_SHT3X.h>

Ultrasonic ultrasonic(11,12,8000); // (Trig PIN,Echo PIN)
SHT3X sht30(0x44);

int counter = 1;

  void setup() {
     
Serial.begin(9600);
  while (!Serial);
 Serial.println("LoRa Sender");
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  String l;
  String t;
  String h;
  String th;
    if ((ultrasonic.Ranging(CM)) != "137")
    {
    LoRa.beginPacket();
    l = String(counter) + "," + ultrasonic.Ranging(CM); 
    Serial.println(l);
    LoRa.beginPacket();
    LoRa.print(l);
    LoRa.endPacket();
    LoRa.beginPacket();
     if((sht30.get()==0)) 
  {
    t = sht30.cTemp;
    h = sht30.humidity;
    l = ultrasonic.Ranging(CM);
    th = String(counter) + "," + t + "," + h;
    counter ++;
    Serial.println(th);
    LoRa.print(th);
    LoRa.endPacket();
        delay(1000);}
      else
    {
    Serial.println("ERROR");
    }
    }
    else
    {
    Serial.println("ERROR");
    }
}
