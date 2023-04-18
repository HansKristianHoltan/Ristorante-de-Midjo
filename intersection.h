
void isOnIntersection(){
  lineSensors.read(lineSensorValues);
  if (lineSensorValues[0] > 1000 && lineSensorValues[4] > 1000){
    drivingState = notDriving;
    motors.setSpeeds(-100, 100);
    if (millis() - turnTime > 1000){
      motors.setSpeeds(0,0);
      drivingState = drivingForwards;
      turnTime = millis();
    }
  }
  if (lineSensorValues[0] > 1000 && lineSensorValues[4] < 1000){
    drivingState = notDriving;
    motors.setSpeeds(-100, 100);
    if (millis() - turnTime1 > 1000){
      motors.setSpeeds(0,0);
      drivingState = drivingForwards;
      turnTime1 = millis();
    }
  }
  if (lineSensorValues[0] < 1000 && lineSensorValues[4] > 1000){
    drivingState = notDriving;
    motors.setSpeeds(100, -100);
    if (millis() - turnTime2 > 1000){
      motors.setSpeeds(0,0);
      drivingState = drivingForwards;
      turnTime2 = millis();
    }    
  }
  if (lineSensorValues[0] < 1000 && lineSensorValues[1] < 1000 && lineSensorValues[2] < 1000 && lineSensorValues[3] < 1000 &&lineSensorValues[4] < 1000){
    drivingState = notDriving;
    motors.setSpeeds(100, -100);
    if (millis() - turnTime3 > 2000){
      motors.setSpeeds(0,0);
      drivingState = drivingForwards;
      turnTime3 = millis();
    }        
  }
}