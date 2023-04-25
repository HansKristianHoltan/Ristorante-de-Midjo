
bool stateWait(unsigned long waitTime){
  if (millis() - previousMillis >= waitTime){
    i += 1;
    previousMillis = millis();
  }
}

void deliverPizza(){
  drivingState = notDriving;
  switch(i){
    case 0:
      previousMillis = millis();
      i += 1;
      break;
    case 1:
      motors.setSpeeds(100, -100);
      Serial.println("1");
      stateWait(1000);
      break;
    case 2:
      pizzaDelivered = true;
      motors.setSpeeds(0, 0);
      pizzaServo.write(120);
      Serial.println("2");
      stateWait(500);
      break;    
    case 3:
      motors.setSpeeds(-100,100);
      pizzaServo.write(10);
      Serial.println("3");
      stateWait(1000);
      break;
    case 4:
      Serial.println("4");
      pizzaDelivered = false;
      onDestination = false;
      destination = NULL;
      drivingState = drivingFast;
      i = 0;
      break;
  }
}

void isOnHouse(){
  lineSensors.read(houseSensor);
  if (houseSensor[2] < isOnHouseSensorTreshold || houseSensor[1] < isOnHouseSensorTreshold || houseSensor[3] < isOnHouseSensorTreshold || houseSensor[0] < isOnHouseSensorTreshold || houseSensor[4] < isOnHouseSensorTreshold){
    // registerer hvor den er hen
    if (millis() - houseMillis > 200){
      houseNum += 1;
    if (houseNum >= 7){
      houseNum = 1;
    }
    houseMillis = millis();
    }
}
  return houseNum;
}