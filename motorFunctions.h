void calibrateSensors()
{
  delay(1000);
  for(int i = 0; i < 100; i++)
  {
    motors.setSpeeds(-200, 200);

    lineSensors.calibrate();
  }
  motors.setSpeeds(0, 0);
}

void lineFollower(){

  int position = lineSensors.readLine(lineSensorValues);

  int error = position -2000;

  speedDifference = error / 2 +  3 * (error - lastError);

  lastError = error;

  leftSpeed = (int16_t)maxSpeed + speedDifference;
  rightSpeed = (int16_t)maxSpeed - speedDifference;

  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  motors.setSpeeds(leftSpeed, rightSpeed);

  return leftSpeed;
}

void lineFollowerSlow(){
 
  int position = lineSensors.readLine(lineSensorValues);

  int error = position -2000;

  speedDifference = error / 2 +  3 * (error - lastError);

  lastError = error;

  int16_t leftSpeed = (int16_t)maxSpeedSlow + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeedSlow - speedDifference;

  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeedSlow);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeedSlow);

  motors.setSpeeds(leftSpeed, rightSpeed);
}


