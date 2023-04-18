// Importerer de nødvendige biblitekene
#include <Zumo32U4.h>
#include <Wire.h>
#include <ArduinoJson.h>

// NB! gå inn i biblioteket /src/avr/ServoTimer.h og endre _timer1 til _timer3 og use_timer1 til use_timer3
#include <Servo.h>

// Importer header filene
#include "ZUMOconstants.h" // konstanter
#include "lineFollower.h" // funksjoner for generell kjøring
#include "batteryStuff.h" // batteriet, og hvordan bilen skal handle i henhold til batterinivået
#include "isOnLocation.h" // hvilket hus zumo er på, og hvordan den skal handle i henhold til det
#include "ESPcommuncation.h" // kommunikasjon med esp
#include "intersection.h"

void setup() {
  // starter seriekommunikasjon med PC, med en baud-rate på 9600
  Serial.begin(9600);
  // starter seriekommunikasjon med ESP32, med en baud-rate på 9600
  Serial1.begin(9600);

  // initaliserer alle 5 linjesensorer
  lineSensors.initFiveSensors();
  lineSensors.emittersOn();

  // funksjon for å kalibrere sensorene (finnes i "lineFollower.h")
  calibrateSensors();

  pizzaServo.attach(22);  
  pizzaServo.write(62);

  drivingState = drivingBackwards;

  turnState = turn;
  
}

void loop()  {
  // Hvert 500ms sender og mottar data til/fra Esp (begge funksjonene finner sted i "ESPcommunication.h")  
  if (millis() - recieveTime > 500){
    recieveFromEsp();
    recieveTime = millis();
  }
  
  if (0 < batteryPrecentage < batteryMin){
    if (drivingState == drivingForwards){
      drivingState = turning;
      }
      destination = 6;
  }
  if (batteryPrecentage <= 0){
    drivingState = notDriving;
  }

  switch (drivingState){
    case drivingForwards:
      isDrivingBackwards = false;
      lineFollower();
      break;            
    case drivingBackwards:
      isDrivingBackwards = true;
      lineFollowerRev();
      break;
    case turning:
      turnAround();
      break;
    case notDriving:
      break;
    
  }
  
  isOnIntersection();

  // Registrer hvor Zumo er i henhold til husene og ladestasjonen (funksjonen er i "isOnLocation.h")
  isOnHouse();

  // Simulerer batteri (funksjonen er i "batteryStuff.h")
  SWbattery();
  
  if (millis() - sendTime > 500){
    sendToEsp();
    sendTime = millis();
  }
}

