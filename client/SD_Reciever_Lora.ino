#include <SPI.h>
#include <LoRa.h>
#include <SD.h>

const int chipSelect = 4;
void setup() {
  Serial.begin(9600);
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
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet

    // read packet
    while (LoRa.available()) {
      char symbol = (char)LoRa.read();
      message += String(symbol);
    }
    Serial.println(message);
    /*SD*/
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    if (dataFile) {
      dataFile.println(message);
      dataFile.close();
    }
    else {
      Serial.println("error opening datalog.txt");
    }
  }
}
