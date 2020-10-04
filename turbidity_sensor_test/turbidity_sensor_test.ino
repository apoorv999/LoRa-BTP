#include "heltec.h" 

String turbidity;

void LoRaData(){
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0 , 0 , turbidity);
  Heltec.display->display();
}


void setup() {
  // put your setup code here, to run once:
//  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Serial.begin(9600);
  Serial.println("waiting...");
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  delay(1500);
  Heltec.display->clear();
  
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->drawString(0, 10, "Wait for incoming data...");
  Heltec.display->display();
  
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int turb = analogRead(34);
  float turbf = turb * (5.0 / 4096.0);
  turbidity= String(turbf);
  Serial.println(turbf);
  LoRaData();
  delay(500);
}
