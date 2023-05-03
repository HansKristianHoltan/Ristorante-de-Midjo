
// funksjon som kan brukes som en ikke blokkerende "delay"
// i en swich case state-maskin
bool stateWait(unsigned long waitTime){
  if (millis() - previousMillis >= waitTime){
    i += 1;
    previousMillis = millis();
  }
}

// funksjon for å levere pizza
void deliverPizza(){

  // skru av motor
  drivingState = notDriving;
  switch(i){
    case 0:
      stateWait(10);
      break;
    case 1:
      // begynner å rotere i 1000ms, i retning huset
      if (direction == right){
        motors.setSpeeds(100, -100);
      }
      else if (direction == left){
        motors.setSpeeds(-100, 100);
      }
      stateWait(1000);
      break;
    case 2:
      // stopper å rotere, og servo festet til utskytning dreies
      pizzaDelivered = true;
      motors.setSpeeds(0, 0);
      pizzaServo.write(150);
      // vent så 500ms
      stateWait(500);
      break;    
    case 3:
      // begynn å rotere i motsatt retning
      if (direction == right){
        motors.setSpeeds(-100, 100);
      }
      else if (direction == left){
        motors.setSpeeds(100, -100);
      }
      // setter servo tilbake til startposisjon
      pizzaServo.write(40);
      // venter 1000ms
      stateWait(1000);
      break;
    case 4:
      // pizza er ferdig levert
      // fortsett å kjøre som normalt, uten destinasjon
      motors.setSpeeds(0,0);
      onDestination = false;
      destination = pizzaPlace;
      drivingState = drivingFast;
      i = 0;
      break;
  }
}

// funksjon som sjekker om zumo er på et hus eller ikke
void isOnHouse(){
  // lagrer sensorverdier i array
  lineSensors.read(houseSensor);

  // hvis en av sensorene registrerer en hvit lapp (hus)
  if ((houseSensor[0] <= isOnHouseSensorTreshold || houseSensor[4] <= isOnHouseSensorTreshold) && allowCount == true){
      if (houseSensor[0] <= isOnHouseSensorTreshold){
        direction = left;
      }
      else if (houseSensor[4] <= isOnHouseSensorTreshold){
        direction = right;
      }
    // hvis lappen registreres konintuerlig i 200
    if (millis() - houseMillis > 200){
      // hus-teller går opp én fram til den treffer 8, da begynner den på 1 igjen
      houseNum += 1;
      if (houseNum > 7){
        houseNum = 1;
      }
      
    houseMillis = millis();

    // boolsk variabel for å forhindre at samme hus blir registrert to ganger
    allowCount = false;
    }
}
  // Hvis det ikke er registrert hvit lapp lenger, og vent 400ms før lapp kan registrers igjen
  else if (houseSensor[0] > isOnHouseSensorTreshold && houseSensor[4] > isOnHouseSensorTreshold && allowCount == false && drivingState != notDriving){
    if (millis() - noHouseMillis > 600){
      allowCount = true;
      noHouseMillis = millis();
    }
  }
}