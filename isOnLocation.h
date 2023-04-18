
bool stateWait(unsigned long waitTime){
  if (millis() - previousMillis >= waitTime){
    i += 1;
    previousMillis = millis();
  }
}

void deliverPizza(){
  drivingState = notDriving;
  switch(i){
    case 1:
      motors.setSpeeds(100, -100);
      stateWait(1000);
      Serial.print("case 1");
      break;
    case 2:
      motors.setSpeeds(0, 0);
      pizzaServo.write(167);
      stateWait(500);
      Serial.println("test 2");
      break;    
    case 3:
      motors.setSpeeds(-100,100);
      pizzaServo.write(62);
      stateWait(1000);
      break;
    case 4:
      destination = NULL;
      drivingState = drivingForwards;
      i = 1;
      break;
  }
}

void isOnHouse(){
  lineSensors.read(houseSensor);
  if (houseSensor[4] < 300 || houseSensor[0] < 300){

    // registerer hvor den er hen
    if (millis() - houseMillis > 300){
      houseNum += 1;
    if (houseNum >= 7){
      houseNum = 0;
    }
    houseMillis = millis();
    }
  if (houseNum == destination){
    if (destination != 6){
      deliverPizza();
    }
    else{
      chargeBattery();
    }
  }
}
  return houseNum;
}