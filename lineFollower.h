void calibrateSensors()
{
  delay(1000);
  for(int i = 0; i < 120; i++)
  {
    motors.setSpeeds(-200, 200);

    lineSensors.calibrate();
  }
  motors.setSpeeds(0, 0);
}


void lineFollower(){
  
  motors.flipLeftMotor(false);
  motors.flipRightMotor(false);

  int16_t position = lineSensors.readLine(lineSensorValues);
  
  int error = position -2000;

  speedDifference = error / 4 +  6* (error - lastError);

  lastError = error;

  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;

  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  motors.setSpeeds(leftSpeed, rightSpeed);
}

void lineFollowerRev(){
  motors.flipLeftMotor(true);
  motors.flipRightMotor(true);

  double position = lineSensors.readLine(lineSensorValues);

  unsigned long now = millis();
  double dt = (double)(now - lastTime) / 1000.0;

  double error = setpoint - position;
  integral += error * dt;
  double derivative = (error - lastError) / dt;

  double output = Kp * error + Ki * integral + Kd * derivative;
  output = constrain(output, -400, 400);

  int16_t leftSpeed = -200 + output;
  int16_t rightSpeed = -200 - output;

  motors.setSpeeds(leftSpeed, rightSpeed);

  lastError = error;
  lastTime = now;

 /*

  int16_t position = lineSensors.readLine(lineSensorValues);
  
  int error = position -2000;

  speedDifference = -error / 4 -  6* (error - lastError);

  lastError = error;

  int16_t leftSpeed = (int16_t)maxSpeed - speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed + speedDifference;

  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  motors.setSpeeds(-leftSpeed, -rightSpeed); 
  */
}

void turnAround(){
  motors.setSpeeds(100,-100);
  if (millis() - turnAroundTime > 1000){
    if (isDrivingBackwards == true){
      drivingState = drivingForwards;
  }
    else{
      drivingState = drivingBackwards;
    }
    turnAroundTime = millis();
  }
  return drivingState;
}

