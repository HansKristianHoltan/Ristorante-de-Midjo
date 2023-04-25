#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <string>
#include "espOnZumoConstants.h"

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (millis() - recieveTime > 1000){
    recieveFromZumo();
    recieveTime = millis();
  }
  if (millis() - rpiTime > 1000){
    sendToRpi();
    rpiTime = millis();
  }
  if (!client.connected()){
    reconnect();
  }
  client.loop();
}

void recieveFromZumo(){
  if (Serial2.available() >= 4){
  int numBytes = Serial2.readBytes((uint8_t*)recievedData, sizeof(recievedData));
  }
}

void sendToZumo(){

  int sendingArraySize = sizeof(sendingData) / sizeof(float);
  Serial2.write((uint8_t*)sendingData, sendingArraySize * sizeof(float));
}

void setup_wifi(){
  delay(10);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }
  Serial.println("connecta til wifi hvertfall");
}

void callback(char* topic, byte* message, unsigned int length){
  String nodeRedPackage;
  for (int i = 0; i < length; i++){
    nodeRedPackage += (char)message[i];
  }
  if (String(topic) == "HouseDelivery"){
    sendingData[0] = nodeRedPackage.toFloat();
    Serial.print("hus: ");
    Serial.println(sendingData[0]);
  }

  if (String(topic) == "batteryFinishedOut"){
    sendingData[1] = nodeRedPackage.toFloat();
    Serial.print("batteryFerdig: ");
    Serial.println(sendingData[1]);

  }

  if (String(topic) == "batteryNewOut"){
    sendingData[2] = nodeRedPackage.toFloat();
    Serial.print("batteriNy: ");
    Serial.println(sendingData[2]);
  }

  sendToZumo();
}

void reconnect(){
  while(!client.connected()){
    if (client.connect("espOnZumo", mqttUser, mqttPassword)){
      client.subscribe("HouseDelivery");
      client.subscribe("batteryFinishedOut");
      client.subscribe("batteryNewOut");
    }
  }
}

void sendToRpi(){

  char avgSpeed[8];
  dtostrf(recievedData[3], 3, 5, avgSpeed);
  client.publish("avgSpeed", avgSpeed);

  char charge[8];
  dtostrf(recievedData[0], 3, 5, charge);
  client.publish("chargeIn", charge);
  
  char batteryPres[8];
  dtostrf(recievedData[2], 3, 4, batteryPres);
  client.publish("batteryIn", batteryPres);
  
  char delivery[8];
  dtostrf(recievedData[1], 3, 5, delivery);
  client.publish("deliveryStatus", delivery);
}
