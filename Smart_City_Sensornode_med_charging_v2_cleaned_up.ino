/********* INCLUDING NEEDED LIBRARIES *********/

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
Adafruit_BME680 bme; // Use I2C protocol
#include "Variables.h"
#include "sendData.h"
#include "setupWiFi.h"
#include <stdint.h>
#include "batteryCharge.h"
#include "lightBar.h"

// Variable to store if sending data was successful
String success;


void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  
  String messageTemp;
  
    if (String(topic) == "chargeOut") {
    if (message[0] == '1') {
        abortCharge = false; 
        
      if (!isCharging) { 
        if(millis() - chargeBlockerTimer >= chargeBlockerInterval)
        isCharging = true;
        previous_chargemillis = millis();
        if (isCharging == true && lastChargeState == false){
         Serial.println("Charging started!"); 
         newBatteryPer = batteryPer;
         lastChargeState = true;
        }
      }  
       }
      
      if (message[0] == '0'){
        abortCharge = true;
      }
    } 
    
 if (String(topic) == "batteryOut") {
    message[length] = '\0';
    batteryPer = atoi((char*)message); // converts the char* message to int and stores it in batteryPer
    
    if (batteryPer != lastBatteryPer){  // checks if batteryPer != to lastBatteryPer, if true :
    Serial.print("Battery level: ");
    Serial.println(batteryPer);         // print value
    lastBatteryPer = batteryPer;        // refreshes the value of lastBatteryPer to batteryPer
    
  }
  }
  if (String(topic) == "HouseDelivery"){
    abortCharge = true;
    houseNum = atoi((char*)message);
    Serial.print("Delivery to House: ");
    //Serial.println(houseNum); // Printing housenum for troubleshooting purposes 
  }
  if((newBatteryPer <= 60) && (chargeState == true)){ 
    Serial.println("Charge Abort In Progress: Charging Will Stop Once Battery Has Reached 60%");
  }
  
  for (int i = 0; i < length; i++) {   // reads through the message character by character and saves the message to messageTemp. 
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
}







void reconnect() {
  // Loop until we're reconnected
  Serial.print("Attempting MQTT connection...");
  while (!client.connected()) {
    
    // Attempt to connect
    if (client.connect("Sensornode", mqttUser, mqttPassword)) {  // connect as Sensornode
      Serial.println("connected");
      // Subscribe
      client.subscribe("chargeOut"); //subscribe to a node-red topic that sends charging state from zumo car
      client.subscribe("batteryOut"); //subscribe to a node-red topic that sends a float value from 0 - 100 (battery percentage)
      client.subscribe("HouseDelivery"); // subscribe to a node-red topic that 
    } else {
      Serial.print("failed, rc=");  // if it cant connect, reconnect.
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000); 
    }
  }
}

struct_message BME680Readings; // creating a structured message with the defined flot names. (BME680Reading "hum" "temp" "gas" "pres"
/* This is not really needed, but makes it structured and easy to read */



void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  // Init BME680 sensor
  bool status = bme.begin(I2Caddress);  
  if (!status) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1); // 1 is allways true, loops an eternal "while" loop, while there is no valid BME680 sensor
  }

 setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);
pinMode(LED4, OUTPUT);
pinMode(LED5, OUTPUT);



    // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

}
 
void loop() {
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); 

  BME680Readings.temp = temperature;
  BME680Readings.hum = humidity;
  BME680Readings.pres = pressure;
  BME680Readings.gas = gasSens;
  
  lightBar();
  batteryCharge();
  sendData(); 

}
