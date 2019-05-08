#include <WEMOS_SHT3X.h>
#include <SPI.h>
#include <LoRa.h>

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

  String t;
  String h;
  String th;
  if(sht30.get()==0){
    t = sht30.cTemp;
    h = sht30.humidity;
    th = String(counter) + "," + t + "," + h;
    Serial.println(th);
    LoRa.beginPacket();
    LoRa.print(th);
    LoRa.endPacket();
    counter ++;
    
  }
  else
  {
    Serial.println("Error!");
  }
  delay(1000);

}
