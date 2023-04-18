
void chargeBattery(){
  drivingState = notDriving;
  if (isFinishedCharging == true){
    drivingState = drivingForwards;
    isFinishedCharging = false;
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
    if(drivingState == drivingForwards){
      batteryPrecentage -= 0.0001 * abs(speedAvg);
  }
    else if(drivingState == drivingBackwards){
      batteryPrecentage -= 0.0005 * abs(speedAvg);
  }  
    else{
      batteryPrecentage -= 0.0015 * abs(speedAvg);
    }
  batteryTime = millis();
}
  return batteryPrecentage;
}