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
  if (millis() - recieveTime){
    recieveFromZumo();
    recieveTime = millis();
  }

  if (millis() - rpiTime){
    sendToRpi();
    rpiTime = millis();
  }
  if (!client.connected()){
    reconnect();
  }
  client.loop();

  if (millis() - sendTime){
    sendToZumo();
    sendTime = millis();
  }
}

void recieveFromZumo(){
  if(Serial2.available()){
    recievedData = Serial2.readStringUntil('\n');    
  }
  deserializeJson(doc, recievedData);
  fromZumo.avarageSpeed = doc["avarageSpeed"];
  fromZumo.isOnChargingStation = doc["onCharginStation"];
  batteryPrecentage = doc["batteryPrecentage"];
  fromZumo.pizzaDelivered = doc["pizzaDelivered"];
  Serial.println(batteryPrecentage);
}

void sendToZumo(){
  doc["deliveryHouseNum"] = toZumo.deliveryHouseNum;
  doc["batteryPrecentage"] = toZumo.batteryPrecentage;
  doc["isFinishedCharging"] = toZumo.isFinishedCharging;
  Serial.println(toZumo.deliveryHouseNum);
  String sendingData;
  serializeJson(doc, sendingData);
  Serial2.println(sendingData);
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
    toZumo.deliveryHouseNum = nodeRedPackage.toInt();
    Serial.println(nodeRedPackage);
  }
}

void reconnect(){
  while(!client.connected()){
    if (client.connect("espOnZumo", mqttUser, mqttPassword)){
      client.subscribe("HouseDelivery");
    }
  }
}

void sendToRpi(){

  char avgSpeed[8];
  itoa(fromZumo.avarageSpeed, avgSpeed, 10);
  client.publish("avgSpeed", avgSpeed);

  byte byteCharge = fromZumo.isOnChargingStation ? 1:0;
  client.publish("charge", &byteCharge, 1);
  
  char batteryPres[8];
  dtostrf(batteryPrecentage, 3, 4, batteryPres);
  client.publish("battery", batteryPres);
  

  byte byteDelivery = fromZumo.pizzaDelivered ? 1:0;
  client.publish("deliveryStatus", &byteDelivery, 1);
}
