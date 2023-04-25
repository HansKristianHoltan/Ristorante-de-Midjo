void SWbattery(){
  while(true){
    if (isDrivingBackwards == false){
      batteryPrecentage -= 0.3;
      delay(400);
      return batteryPrecentage;
    }
    else if(isDrivingBackwards == true){
      batteryPrecentage -= 0.1;
      delay(400);
      return batterPrecentage;
    }
  }
}

void setSpeedsReverse(){
  int16_t leftSpeed = (int16_t)maxSpeedRev + speedDifferenceRev;
  int16_t rightSpeed = (int16_t)maxSpeedRev - speedDifferenceRev;

  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeedRev);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeedRev);

  motors.setSpeeds(-leftSpeed, -rightSpeed); 
}

void turnAround(){
  if(isDrivingBackwards == false){
    isDrivingBackwards = true;
    motors.setSpeeds(100, -100);
    delay(2000);
  }
  return isDrivingBackwards;
}
