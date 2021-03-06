#include <SoftwareSerial.h>
#include "heltec.h"
#include "images.h"
#include <TinyGPS++.h>
SoftwareSerial gpsSerial(23,17); //tx of the gps is connected to 23; rx of the gps is connected to 17
TinyGPSPlus gps;
float lattitude,longitude;
unsigned int counter = 0;
#define BAND    868E6

void logo()
{
  Heltec.display->clear();
  Heltec.display->drawXbm(0,5,logo_width,logo_height,logo_bits);
  Heltec.display->display();
}

void setup() {

 gpsSerial.begin(9600);
 Serial.begin(9600);
 Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
 
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  logo();
  delay(1500);
  Heltec.display->clear();
  
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->display();
  delay(1000);
  }

void loop()
{
//  while (!gpsSerial.available());
  while (gpsSerial.available()){
    int data = gpsSerial.read();
    gps.encode(data);
    delay(1);
//    Serial.println("Hello!!!");  //this line helped before adding 1ms delay
    }
//    Serial.println("i am here!!!!!!");
      lattitude = (gps.location.lat());
      longitude = (gps.location.lng());
      Serial.print ("lattitude: ");
      Serial.println (lattitude,6);
      Serial.print ("longitude: ");
      Serial.println (longitude,6);
      LoRa.beginPacket();
  LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print(counter);
  LoRa.print(":");
  LoRa.print(lattitude,6);
  LoRa.print(":");
  LoRa.print(longitude,6);
  LoRa.print(":");
  LoRa.endPacket();
      Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  
  Heltec.display->drawString(0, 0, "Sending packet: ");
  Heltec.display->drawString(90, 0, String(counter));
  Heltec.display->drawString(0, 30, "Lat: "+String(lattitude,6));
  Heltec.display->drawString(0, 50, "Long: "+String(longitude,6));
  Heltec.display->display();
  counter++;  
  delay(1000);
  }
