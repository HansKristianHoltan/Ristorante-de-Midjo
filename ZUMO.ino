// Importerer de nødvendige biblitekene
#include <Zumo32U4.h>
#include <Wire.h>

// NB! gå inn i biblioteket /src/avr/ServoTimer.h og endre _timer1 til _timer3 og use_timer1 til use_timer3
#include <Servo.h>

// Importer header filene
#include "ZUMOconstants.h"    // konstanter
#include "motorFunctions.h"   // funksjoner for generell kjøring
#include "BMS.h"              // batteriet, og hvordan bilen skal handle i henhold til batterinivået
#include "location.h"         // hvilket hus zumo er på, og hvordan den skal handle i henhold til det
#include "ESPcommuncation.h"  // kommunikasjon med esp

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

  delay(1000);
  // servo settes til analog pin 4, og setter servo i startposisjon
  pizzaServo.attach(22);
  pizzaServo.write(40);

  // start states til kjøring og snu-retning
  drivingState = drivingFast;
  direction = right;
}

void loop() {
  // mottar data fra esp, dette skjer kun når esp mottar fra RPI
  recieveFromEsp();

  // sjekker om batteri prosenten er over 0, om over 0, stop all motorfunksjon
  if (batteryPercentage <= 0) {
    drivingState = notDriving;
  }

  // regner ut tiden det skal ta for 180 og 90 graders sving
  elapsedTime = millis() - stateTime;

  // Sjekker alle 5 sensorverdier, og lagrer det i en array
  lineSensors.read(lineSensorValues);

  // switch case for å enkelt endre motorfunksjonene basert på "drivingState"
  switch (drivingState) {

    // Tom state, for å få switch-casen til å kjøre mer smooth
    case start:
      break;

    // "default" state
    case drivingFast:

      // normal linjefølgingsfunksjon
      lineFollower();  

      // Hvis batteryprosenten er under en minimumsgrense, kjør saktere
      if (batteryPercentage < batteryMin) {
        drivingState = drivingSlow;
        destination = chargingStation;  // setter destination til ladestasjonen
      }

      // Hvis alle sensorer registrer at de er på en linje i mer enn 200ms
      // endre state til turningLeft, fordi da er Zumo ved et veikryss
      if (lineSensorValues[0] > onLineTreshold && lineSensorValues[1] > onLineTreshold && lineSensorValues[2] > onLineTreshold
          && lineSensorValues[3] > onLineTreshold && lineSensorValues[4] > onLineTreshold) {
        if (millis() - turnTime > 200) {
          drivingState = turningLeft;
          stateTime = millis();
          turnTime = millis();
        }
      }

      // Hvis alle sensorer registrer at det ikke er noe mer linje, og det ikke er et "hus" i mer enn 200ms
      // endre state til noRoad, fordi da har Zumo kjørt vekk fra linja
      if (lineSensorValues[0] < offLineTreshold && lineSensorValues[1] < offLineTreshold && lineSensorValues[2] < offLineTreshold
          && lineSensorValues[3] < offLineTreshold && lineSensorValues[4] < offLineTreshold && lineSensorValues[0] < onLineTreshold
          && lineSensorValues[1] < onLineTreshold && lineSensorValues[2] < onLineTreshold && lineSensorValues[3] < onLineTreshold && lineSensorValues[4] < onLineTreshold) {
        if (millis() - turnTime1 > 2000) {
          drivingState = noRoad;
          stateTime = millis();
          turnTime1 = millis();
        }
      }

      break;

    // State som Zumo havner i, om batteriet er under en viss prosent
    case drivingSlow:

      // linjefølingsfunksjon, men med redusert fart
      lineFollowerSlow();  

      break;

    // State som Zumo er i når den har møtt ett veikryss
    case turningLeft:
      
      // setter farten til -25 på venstre, og 200 på høyremotor
      // Zumo kjører da fortsatt litt fremover mens den roterer
      motors.setSpeeds(-25, 200);

      // hvis rotert i mer enn 800ms, stop å rotere
      // her tilsvarer 800ms 90 grader
      if (elapsedTime > 800) {
        motors.setSpeeds(0, 0);
        drivingState = drivingFast;
      }

      break;
      
    // State som Zumo er i når den ikke registerer noe linje
    case noRoad:
      
      // Hvis zumo allerede er i en sving til en retning, snu 180 grader i samme retning
      // setter farten til 100 og -100 til hver motor, avhengig av sving-retning
      if (leftSpeed < rightSpeed) {
        motors.setSpeeds(100, -100);
      } else {
        motors.setSpeeds(-100, 100);
      }

      // Hvis Zumo har rotert i mer enn 2000ms, som tilsvarer ca 180 grader
      // eller registerer at den er på linja igjen, stop å rotere
      if (elapsedTime > 2000 || lineSensorValues[2] > onLineTreshold) {
        motors.setSpeeds(0, 0);
        drivingState = drivingFast;
      }

      break;

    // State hvor Zumo ikke utfører noen kjørefunksjoner
    case notDriving: 
      break;
  }


  // Registrer hvor Zumo er i henhold til husene og ladestasjonen
  if (onDestination == false) {
    isOnHouse();
  }

  // Hvis huset Zumo er med er det samme som destinasjonen den skal kjøre til
  if (houseNum == destination) {

    // setter onDestination til true, slik at Zumo ikke lenger leter etter destinasjonen sin
    onDestination = true;

    // Swicth case for å få Zumo til å gjøre handling basert på hva destinasjonen er
    switch (destination) {

      // Hvis destinasjon er ladestasjonen
      case chargingStation:

        // "Lader" batteriet
        chargeBattery();

        break;

      // Hvis destinasjon er "hjem", som er pizza stedet
      case pizzaPlace:

        // skru av motorene
        motors.setSpeeds(0, 0);
        Serial.println("er på pizzastedet");

        drivingState = notDriving; 
        pizzaDelivered = false; // beskjed til RPI om at ny pizza kan leveres
        isOnPizzaPlace = true; 

        break;

      // Hvis destinasjon er et hus hvor pizza skal leveres
      case 1 ... 5:

        // Leverer pizza
        deliverPizza();

        break;
    }
  }
  // Hvis Zumo er på pizzastedet, og får ny bestilling
  else if (isOnPizzaPlace == true){
    drivingState = drivingFast;
    onDestination = false;
  }
 

  // Simulerer batteri
  SWbattery();

  // Hvert sekund sendes data til esp
  if (millis() - sendTime > 1000) {
    sendToEsp();
    sendTime = millis();
  }


  // Data for debugging
  /*
  Serial.print("husnummer: ");
  Serial.println(houseNum);
  Serial.print("destinasjon: ");
  Serial.println(destination);
  Serial.print("kjøreState: ");
  Serial.println(drivingState);
  Serial.print("pizzaDelivered: ");
  Serial.println(pizzaDelivered);
  Serial.print("faktisk batterinivå: ");
  Serial.println(readBatteryMillivolts());
  Serial.print("Swbatteri: ");
  Serial.println(batteryPercentage);
  Serial.println(" ");
  */
}
