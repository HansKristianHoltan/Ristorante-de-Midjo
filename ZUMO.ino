// Importerer de nødvendige biblitekene
#include <Zumo32U4.h>
#include <Wire.h>
#include <ArduinoJson.h>

// NB! gå inn i biblioteket /src/avr/ServoTimer.h og endre _timer1 til _timer3 og use_timer1 til use_timer3
#include <Servo.h>

// Importer header filene
#include "ZUMOconstants.h" // konstanter
#include "motorFunctions.h" // funksjoner for generell kjøring
#include "BMS.h" // batteriet, og hvordan bilen skal handle i henhold til batterinivået
#include "location.h" // hvilket hus zumo er på, og hvordan den skal handle i henhold til det
#include "ESPcommuncation.h" // kommunikasjon med esp
#include "intersection.h" // hvordan zumoen skal handle dersom den treffer et kryss

void setup() {
  // starter seriekommunikasjon over usb, med en baud-rate på 9600
  Serial.begin(9600);
  // starter seriekommunikasjon med ESP32, med en baud-rate på 9600
  Serial1.begin(9600);

  // initaliserer alle 5 linjesensorer
  lineSensors.initFiveSensors();
  lineSensors.emittersOn();

  // funksjon for å kalibrere sensorene
  calibrateSensors();

  // servo settes til analog pin 4, og setter servo i startposisjon
  pizzaServo.attach(22);  
  pizzaServo.write(10);

  // start states til kjøring og intersection
  drivingState = drivingFast;
  intersectionState = noIntersection;
}

void loop()  {
  // mottar data fra esp, dette skjer kun når esp mottar fra RPI
  recieveFromEsp();

  // sjekker om batteri prosenten er over 0, om over 0, stop all motorfunksjon
  if (batteryPercentage <= 0){
    drivingState = notDriving;
  }
  elapsedTime = millis() - stateTime;
  lineSensors.read(lineSensorValues);
  // switch case for å enkelt endre motorfunksjonene basert på "drivingState"
  switch (drivingState){
    case start:
      break;
    case drivingFast:
      lineFollower(); // normal linjefølgingsfunksjon
      // Hvis batteryprosenten er under en minimumsgrense, kjør saktere
      if (batteryPercentage < batteryMin){
        drivingState = drivingSlow;
        destination = 6; // setter destination til 6, som er ladestasjonen
      }
      if (lineSensorValues[0] > onLineTreshold && lineSensorValues[1] > onLineTreshold && lineSensorValues[2] > onLineTreshold  && lineSensorValues[3] > onLineTreshold  && lineSensorValues[4] > onLineTreshold){
        if (millis() - turnTime > 200){
        drivingState = turningLeft;
        stateTime = millis();
        turnTime = millis();
        }
      }
      
      if (lineSensorValues[0] < offLineTreshold && lineSensorValues[1] < offLineTreshold && lineSensorValues[2] < offLineTreshold  && lineSensorValues[3] < offLineTreshold && lineSensorValues[4] < offLineTreshold){
        if (millis() - turnTime1 > 2000){
        drivingState = turningAround;
        stateTime = millis();
        turnTime1 = millis();
        }
      }
      
      break;            
    case drivingSlow:
      lineFollowerSlow(); // linjefølingsfunksjon, men med redusert fart
      break;
    case turningAround:
      if (leftSpeed > 0){
        motors.setSpeeds(100, -100);
      }
      else{
        motors.setSpeeds(-100, 100);
      }
      if (elapsedTime > 2000  || lineSensorValues[2] > onLineTreshold){
        motors.setSpeeds(0,0);
        drivingState = drivingFast;
      }
      break;
    case turningLeft:
      motors.setSpeeds(-25, 200);
      if (elapsedTime > 800){
        motors.setSpeeds(0,0);
        drivingState = drivingFast;
      }
      break;
    case notDriving:
      break;
    
  }
  //isOnIntersection(); // funksjon for å lete etter veikryss

  // Registrer hvor Zumo er i henhold til husene og ladestasjonen 
  if (onDestination == false){
    isOnHouse();
  }

  if (houseNum == destination){
    onDestination = true;
    if (destination == 6){
      chargeBattery();
    }
    else if (destination > 0){
      deliverPizza();
    }
  }
  
  // Simulerer batteri 
  SWbattery();

  // Hvert sekund sendes data til esp
  if (millis() - sendTime > 1000){
    sendToEsp();
    sendTime = millis();
  }
}

