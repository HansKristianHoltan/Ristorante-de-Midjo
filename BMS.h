
void chargeBattery(){
  motors.setSpeeds(0,0);
  drivingState = notDriving;
  onChargingStation = true;
  if (isFinishedCharging == 1){
    Serial.println("ferdig ladet");
    drivingState = drivingFast;
    onDestination = false;
    onChargingStation = false;
    isFinishedCharging = 0;
    destination = NULL;
  }
}

void getSpeed(){
  int leftCount = encoders.getCountsAndResetLeft();
  int rightCount = encoders.getCountsAndResetRight();
  
  int leftRev = leftCount / count_per_rev;
  int rightRev = rightCount / count_per_rev;    
  
  int speedLeft = leftRev * cm_per_rev;
  int speedRight = rightRev * cm_per_rev;

  speedAvg = (speedLeft + speedRight)/2;  
  
  return speedAvg;
}

float SWbattery(){
  if (millis() - batteryTime > 1000){

    getSpeed();
    batteryPercentage -= 0.023 * abs(speedAvg);
    batteryTime = millis();
}
  return batteryPercentage;
}