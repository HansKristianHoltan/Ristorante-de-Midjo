void throwPizza(){
  motors.setSpeeds(100, -100);
  delay(1000);
  motors.setSpeeds(0, 0);
  delay(1000);
  motors.setSpeeds(-100, 100);
  delay(1000);
}

void deliverPizza(){
  if (houseNum == deliveryHouse){
    while(1){
      motors.setSpeeds(100,100);
      delay(100);
      motors.setSpeeds(0,0);
      delay(500);
      throwPizza();
      break;
    }
  }
}

void isOnHouse(){
  lineSensors.read(pizzaDeliverySensor);
  if (pizzaDeliverySensor[4] < 300){
    currentMillis = millis();
    if (currentMillis - previousMillis > 300){
      houseNum += 1;
    if (houseNum >= 6){
      houseNum = 0;
    }
    previousMillis = currentMillis;
    deliverPizza();
  }
}
  return houseNum;
}