#include <SPI.h>
#include <LoRa.h>
#include <SD.h>
#include <iarduino_RTC.h>   

iarduino_RTC time(RTC_DS1307);
  
const int chipSelect = 4;

void setup() {
  Serial.begin(9600);
  time.begin(); 
  while (!Serial);


  Serial.println("LoRa Receiver");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }


  /*SD*/
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
 
  Serial.println("card initialized.");

}

void loop() {
  String message;
  String a;
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet

    // read packet
    while (LoRa.available()) {
      char symbol = (char)LoRa.read();
      message += String(symbol);
      a = message + "," + time.gettime(" d-m-Y,H:i:s, D");
    }
    Serial.println(a);
    /*SD*/
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    if (dataFile) {
      dataFile.println(a);
      dataFile.close();
    }
    else {
      Serial.println("error opening datalog.txt");
    }
  }
}
