// Importerer nødvendige biblioteker
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <string>

// Importerer header fil, hvor konstantene er
#include "espOnZumoConstants.h"

void setup() {

  // Begynner seriell kommunikasjon over usb, med en baud-rate på 9600
  Serial.begin(9600);

  // Begynner seriell kommunikasjon med Zumo, med en baud-rate på 9600
  //  over de spesifikke pinnene 16 og 17
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // starter wifi
  setup_wifi();

  // initialiserer mqtt connection
  client.setServer(mqtt_server, 1883);

  // definerer hvilken funksjon som skal kjøres når beskjed mottas over mqtt
  client.setCallback(callback);
}

void loop() {

  // mottar data fra Zumo hvert 1000ms
  if (millis() - recieveTime > 1000){
    recieveFromZumo();
    recieveTime = millis();
  }

  // sender data til Rpi hvert 1000ms
  if (millis() - rpiTime > 1000){
    sendToRpi();
    rpiTime = millis();
  }

  // hvis mister kontakt med mqtt, reconnect
  if (!client.connected()){
    reconnect();
  }

  // opprettholder kontakt med mqtt server
  client.loop();
}

// funksjon for mottagelse fra Zumo
void recieveFromZumo(){

  // hvis sendingen er riktig størrelse, lagre alle verdiene i en array
  if (Serial2.available() >= 4){
  int numBytes = Serial2.readBytes((uint8_t*)recievedData, sizeof(recievedData));
  }
}

// funksjon for sending til Zumo
void sendToZumo(){

  // sender array med verdier hentet fra Rpi
  int sendingArraySize = sizeof(sendingData) / sizeof(float);
  Serial2.write((uint8_t*)sendingData, sendingArraySize * sizeof(float));
}

// funksjon for å starte wifi connection
void setup_wifi(){
  delay(10); // vent 10ms 

  // begynn wifi med navn og passord
  WiFi.begin(ssid, password);

  // så lenge wifi ikke er connecta, vent
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }
}

// funksjon som kjøres hver gang besked mottas fra Rpi over mqtt
void callback(char* topic, byte* message, unsigned int length){

  // lager en String for å kunne lagre beskjeden
  String nodeRedPackage;

  // legger beskjeden inn i stringen
  for (int i = 0; i < length; i++){
    nodeRedPackage += (char)message[i];
  }

  // Hvis beskjeden ble sendt over emnet HouseDelivery
  if (String(topic) == "HouseDelivery"){

    // Gjør om til float, og setter inn i arrayen som sendes til Zumo
    sendingData[0] = nodeRedPackage.toFloat();
  }

  // Hvis beskjeden ble sendt over emnet batteryFinishedOut
  if (String(topic) == "batteryFinishedOut"){

    // Gjør om til float, og setter inn i arrayen som sendes til Zumo
    sendingData[1] = nodeRedPackage.toFloat();
  }

  // Hvis beskjeden ble sendt over emnet batteryNewOut
  if (String(topic) == "batteryNewOut"){

    // Gjør om til float, og setter inn i arrayen som sendes til Zumo
    sendingData[2] = nodeRedPackage.toFloat();
  }

  // sender med en gang til Zumo hver gang ny beskjed mottas fra Rpi
  sendToZumo();
}

// funksjon for å reconnecte med mqtt
void reconnect(){

  // så lenge ikke connecta
  while(!client.connected()){

    // hvis brukernavn og passord stemmer
    if (client.connect("espOnZumo", mqttUser, mqttPassword)){

      // abonnere på følgende emner
      client.subscribe("HouseDelivery");
      client.subscribe("batteryFinishedOut");
      client.subscribe("batteryNewOut");
    }
  }
}

// funksjon for å sende til Rpi
void sendToRpi(){

  // lager en array med characters
  char avgSpeed[8];
  // gjør om floatverdiene som er i mottagelsespakken fra Zumo
  // til String, og sender til Rpi på emnet "avgSpeed"
  dtostrf(recievedData[3], 3, 5, avgSpeed);
  client.publish("avgSpeed", avgSpeed);

  // lager en array med characters
  char charge[8];
  // gjør om floatverdiene som er i mottagelsespakken fra Zumo
  // til String, og sender til Rpi på emnet "charge"
  dtostrf(recievedData[0], 3, 5, charge);
  client.publish("chargeIn", charge);
  
  // lager en array med characters
  char batteryPres[8];
  // gjør om floatverdiene som er i mottagelsespakken fra Zumo
  // til String, og sender til Rpi på emnet "batteryPres"
  dtostrf(recievedData[2], 3, 4, batteryPres);
  client.publish("batteryIn", batteryPres);
  
  // lager en array med characters
  char delivery[8];
  // gjør om floatverdiene som er i mottagelsespakken fra Zumo
  // til String, og sender til Rpi på emnet "delivery"
  dtostrf(recievedData[1], 3, 5, delivery);
  client.publish("deliveryStatus", delivery);
}
