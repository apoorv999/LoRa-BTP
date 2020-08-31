/*
  This is a simple example show the Heltec.LoRa recived data in OLED.

  The onboard OLED display is SSD1306 driver and I2C interface. In order to make the
  OLED correctly operation, you should output a high-low-high(1-0-1) signal by soft-
  ware to OLED's reset pin, the low-level signal at least 5ms.

  OLED pins to ESP32 GPIOs via this connecthin:
  OLED_SDA -- GPIO4
  OLED_SCL -- GPIO15
  OLED_RST -- GPIO16
  
  by Aaron.Lee from HelTec AutoMation, ChengDu, China
  成都惠利特自动化科技有限公司
  www.heltec.cn
  
  this project also realess in GitHub:
  https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series
*/
#include "heltec.h" 
#include "images.h"

#define BAND    868E6  //you can set band here directly,e.g. 868E6,915E6
String rssi = "RSSI --";
String packSize = "--";
String packet ;

void logo(){
  Heltec.display->clear();
  Heltec.display->drawXbm(0,5,logo_width,logo_height,logo_bits);
  Heltec.display->display();
}

void LoRaData(){
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0 , 10 , "Received "+ packSize + " bytes");
  Heltec.display->drawStringMaxWidth(0 , 21 , 128, packet);
  Heltec.display->drawString(0 , 34 , "counter:- ");
  Heltec.display->drawString(0 , 44 , "Lat:- ");
  Heltec.display->drawString(0 , 54 , "Long:- ");
  int i=0;
  char str_array[packet.length()];
  packet.toCharArray(str_array, packet.length());
  char *p = str_array;
 char *str;
 while ((str = strtok_r(p, ":", &p)) != NULL){ // delimiter is the semicolon
   switch(i){
    case 0: Heltec.display->drawString(50 , 34 ,  str);break;
    case 1: Heltec.display->drawString(50 , 44 , str);break;
    case 2: Heltec.display->drawString(50 , 54 , str);break;
    default: Heltec.display->drawString(50 , 63 , str);
   }
   i++;
}
//  char* token=strtok(str_array,":");
//  while (token != NULL) {
//        Heltec.display->drawString(0 , 34+(10*i) , token);
//        i++;
//        token = strtok(NULL, ":"); 
//    }
  Heltec.display->drawString(0, 0, rssi);  
  Heltec.display->display();
}

void cbk(int packetSize) {
  packet ="";
  packSize = String(packetSize,DEC);
  for (int i = 0; i < packetSize; i++) { packet += (char) LoRa.read(); }
  rssi = "RSSI " + String(LoRa.packetRssi(), DEC) ;
  LoRaData();
}

void setup() { 
   //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  LoRa.setSpreadingFactor(11);
  Serial.begin(9600);
  Serial.println("waiting...");
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  logo();
  delay(1500);
  Heltec.display->clear();
  
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->drawString(0, 10, "Wait for incoming data...");
  Heltec.display->display();
  delay(1000);
  //LoRa.onReceive(cbk);
  LoRa.receive();
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) { cbk(packetSize);  }
  delay(10);
}
