#include <SoftwareSerial.h>
#include <SPI.h>
#include <LoRa.h>
SoftwareSerial GSMport(3, 4);

void setup() {
  Serial.begin(9600);  //скорость порта
  Serial.println("GPRS test");
  GSMport.begin(9600);
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(866E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
 
  int d = 500;
  int ATsCount = 7;
  String ATs[] = {  //массив АТ команд
    "AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"",  //Установка настроек подключения
    "AT+SAPBR=3,1,\"APN\",\"internet.mts.ru\"",
    "AT+SAPBR=3,1,\"USER\",\"mts\"",
    "AT+SAPBR=3,1,\"PWD\",\"mts\"",
    "AT+SAPBR=1,1",  //Устанавливаем GPRS соединение
    "AT+HTTPINIT",  //Инициализация http сервиса
    "AT+HTTPPARA=\"CID\",1"  //Установка CID параметра для http сессии
  };
  int ATsDelays[] = {6, 1, 1, 1, 3, 3, 1}; //массив задержек
  Serial.println("GPRG init start");
  for (int i = 0; i < ATsCount; i++) {
    Serial.println(ATs[i]);  //посылаем в монитор порта
    GSMport.println(ATs[i]);  //посылаем в GSM модуль
    delay(d * ATsDelays[i]);
    Serial.println(ReadGSM());  //показываем ответ от GSM модуля
    delay(d);
  }
  Serial.println("GPRG init complete");
  
}

void loop() {
  int packetSize = LoRa.parsePacket();
  String result;
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");
  int i = 0;

   while (LoRa.available()) {
    char  loraSignal = (char)LoRa.read();
    result[i++] = loraSignal;
    Serial.print(loraSignal);
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    delay(1000);
  }
  
  delay (5000);
  int d = 1000;
  Serial.println("Send start");
  Serial.println("setup url");
  String x = "55.51.24";
  String data = "1";
  String y = "37.35.43";
  GSMport.println("AT+HTTPPARA=\"URL\",\"http://35.231.157.13/get.php/?val="+ result + ";" + y +";" + data + "\"");
  delay(d * 2);
  Serial.println(ReadGSM());
  delay(d);
  Serial.println("GET url");
  GSMport.println("AT+HTTPACTION=0");
  delay(d * 2);
  Serial.println(ReadGSM());
  delay(d);
  Serial.println("Send done");  
}

String ReadGSM() {  //функция чтения данных от GSM модуля
  int c;
  String v;
  while (GSMport.available()) {  //сохраняем входную строку в переменную v
    c = GSMport.read();
    v += char(c);
    delay(10);
  }
  return v;
}
