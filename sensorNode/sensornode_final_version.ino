/********* INCLUDING NEEDED LIBRARIES *********/

#include <WiFi.h> //importerer wifi biblioteket
#include <PubSubClient.h> //importerer biblioteket som brukes til nodered kommunikasjon
#include <Wire.h> //brukes til I2C kommunikasjon
#include <Adafruit_Sensor.h> //for å bruke bme680 sensor
#include <Adafruit_BME680.h> //for å bruke bme680 sensor
Adafruit_BME680 bme; // Use I2C protocol
#include "Variables.h"
#include "sendData.h"
#include "setupWiFi.h"
#include <stdint.h> 
#include "lightBar.h"
#include "batteryCharge.h"
#include "solarPower.h"

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
        
      if (!isCharging && powerBankBattery >= 150) { // tillater bare lading om batterinivået på ladestasjonen er over 150/500
        if(millis() - chargeBlockerTimer >= chargeBlockerInterval)
        isCharging = true;
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
    batteryPer = atoi((char*)message); // koverterer char* message til en int og lagrer den i batteryPer
    
    if (batteryPer != lastBatteryPer){  // sjekker om batteryPer != lastBatteryPer, dette er for å printe batteriverdien bare når det skjer en endring
    Serial.print("Battery level: ");
    Serial.println(batteryPer);         // Printer verdien
    lastBatteryPer = batteryPer;        // Resetter verdien av lastBatteryPer    
  }
  }
  
  if (String(topic) == "HouseDelivery"){
    if(isCharging){
    abortCharge = true;  // setter abortcharge true om det kommer inn en pizza bestilling (denne blir resatt om bilen kommer på ladestasjonen)
    }
    houseNum = atoi((char*)message);   //ASCII til int (tekst streng til integer)
    Serial.print("Delivery to House: ");
    //Serial.println(houseNum); // printer houseNum i tilfelle feilsøking behøves
  
  if(newBatteryPer <= 60){ 
    Serial.println("Charge Abort In Progress: Charging Will Stop Once Battery Has Reached 60%");
  }
  }
  
  for (int i = 0; i < length; i++) {   // Leser igjennom meldingen karakter for karakter og lagrer meldingen i messageTemp 
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
}

void reconnect() {
  // Kjører funksjonen helt til mikrokontrolleren er tilkoblet
  Serial.print("Attempting MQTT connection...");
  while (!client.connected()) {
    
    // Attempt to connect
    if (client.connect("Sensornode", mqttUser, mqttPassword)) {  // tilkobling til mqtt serveren som "sensorNode"
      Serial.println("connected");
      
      // Subscribe
      client.subscribe("chargeOut"); //abonerer til topic "chargeOut" for å få ladestatus fra bilen
      
      client.subscribe("batteryOut"); //abonerer til topic "batteryOut" for å få batteridata fra bilen (0-100%)
      
      client.subscribe("HouseDelivery"); //abonerer til houseDelivery for å stoppe lading om bilen får en bestilling mens lading pågår 
      
    } else {
      Serial.print("failed, rc=");  //om tilkobling feiler, prøv igjen
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // venter 5 sekunder før neste gang
      delay(5000); 
    }
  }
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  // Init BME680 sensor
  bool status = bme.begin(I2Caddress);  
  if (!status) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1); // while(1); er alltid true, altså vil programmet stoppe om en sensor ikke blir funnet på addressen 0x77
  }

 setup_wifi(); // kjører setup_WiFi funksjonen
 
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

pinMode(LED1, OUTPUT);      //setter LED som utgang
pinMode(LED2, OUTPUT);      //setter LED som utgang
pinMode(LED3, OUTPUT);      //setter LED som utgang
pinMode(LED4, OUTPUT);      //setter LED som utgang
pinMode(LED5, OUTPUT);      //setter LED som utgang
pinMode(rLED, OUTPUT);      //setter LED som utgang
pinMode(sunSensor, INPUT);  // setter photoresistor som en analog input




    // Set up for å initialisere BME680 sensoren, med filtrering og klargjøring
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C i 150 ms

}
 
void loop() {
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); 

  chargeZumo(); // kjører funksjonen som styrer lading av zumo bil
  sendSensorData(); //kjører funksjonen som sender data til nodeRed
  chargePowerBank(); // kjører funksjonen som lader powerbank batteriet
   
}
