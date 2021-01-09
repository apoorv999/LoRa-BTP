#include <SoftwareSerial.h>
#include "heltec.h"
#include "images.h"
#include <TinyGPS++.h>
SoftwareSerial gpsSerial(23,17); //tx of the gps is connected to 23; rx of the gps is connected to 17
TinyGPSPlus gps;
float lattitude,longitude,turbidity;
unsigned int counter = 0;
#define BAND    868E6
#define turbPin 37
#define lattitudex 28.655975
#define longitudex 77.131469
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
      turbidity = float(analogRead(turbPin));
      turbidity = 1.0 - (turbidity / 4095.0);
      Serial.print ("lattitude: ");
      Serial.println (lattitude,6);
      Serial.print ("longitude: ");
      Serial.println (longitude,6);
      Serial.print ("Turbidity: ");
      Serial.println(turbidity);
      LoRa.beginPacket();
      turbidity = 0.34;
      float ph = 7.34;
      float ec = 0.19;
  LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print(counter);
  LoRa.print(":");
  LoRa.print(lattitudex,6);
  LoRa.print(":");
  LoRa.print(longitudex,6);
  LoRa.print(":");
  LoRa.print(String(turbidity));
  LoRa.print(":");
  LoRa.print(String(ph));
  LoRa.print(":");
  LoRa.print(String(ec));
  LoRa.print(":");
  LoRa.endPacket();
      Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  
  Heltec.display->drawString(0, 0, "Sending packet: ");
  Heltec.display->drawString(90, 0, String(counter));
  Heltec.display->drawString(0, 20, "Lat: "+String(lattitudex,6));
  Heltec.display->drawString(0, 35, "Long: "+String(longitudex,6));
  Heltec.display->drawString(0, 50, "Turbidity: "+String(turbidity));

  Heltec.display->display();
  counter++;  
  delay(10000);
  }
