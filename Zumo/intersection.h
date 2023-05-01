/*

///////////////////////////////////////////
///////////////////////////////////////////
/////           brukes ikke         ///////
///////////////////////////////////////////
///////////////////////////////////////////
void isOnIntersection(){
  switch (intersectionState){
    case leftTurnFound:
      Serial.println("venstre sving");
      drivingState = notDriving;
      motors.setSpeeds(0, 100);
      if (millis() - turnTime > 1000){
        motors.setSpeeds(0,0);
        drivingState = drivingFast;
        intersectionState = noIntersection;
        turnTime = millis();
      }
    break;

    case rightTurnFound:
      Serial.println("høyre sving");
      drivingState = notDriving;
      motors.setSpeeds(100, 0);
      if (millis() - turnTime1 > 1000){
        motors.setSpeeds(0,0);
        drivingState = drivingFast;
        intersectionState = noIntersection;
        turnTime1 = millis();
      }
    break;

    case threeOrFourWayIntersectionFound:
      Serial.println("stort kryss");
      drivingState = notDriving;
      motors.setSpeeds(100, 0);
      if (millis() - turnTime2 > 1000){
        motors.setSpeeds(0,0);
        drivingState = drivingFast;
        intersectionState = noIntersection;
        turnTime2 = millis();
    }
      break;

    case noRoad:
      Serial.println("ingen vei");
      drivingState = notDriving;
      motors.setSpeeds(100, -100);
      if (millis() - turnTime3 > 2000){
        motors.setSpeeds(0, 0);
        drivingState = drivingFast;
        intersectionState = noIntersection;
        turnTime3 = millis();
    }
      break;
    case noIntersection:
      lineSensors.read(lineSensorValues);
      if (lineSensorValues[0] > onLineTreshold && lineSensorValues[1] > onLineTreshold && lineSensorValues[2] > onLineTreshold && lineSensorValues[3] > onLineTreshold && lineSensorValues[4] > onLineTreshold){
        if (millis() - onIntersectionTime > 200){
        intersectionState = threeOrFourWayIntersectionFound;
        onIntersectionTime = millis();
        }
      }
      if (lineSensorValues[1] < offLineTreshold && lineSensorValues[2] < offLineTreshold && lineSensorValues[3] < offLineTreshold){
        if (millis() - onIntersectionTime1 > 1000){
        intersectionState = noRoad;
        onIntersectionTime1 = millis();
        }
      }
      if (lineSensorValues[0] > onLineTreshold && lineSensorValues[1] > onLineTreshold && lineSensorValues[2] > onLineTreshold && lineSensorValues[4] < offLineTreshold){
        if (millis() - onIntersectionTime2 > 200){
        intersectionState = leftTurnFound;
        onIntersectionTime3 = millis();
        }
      }
      if (lineSensorValues[0] < offLineTreshold && lineSensorValues[2] > onLineTreshold && lineSensorValues[3] > onLineTreshold && lineSensorValues[4] > onLineTreshold){
        if (millis() - onIntersectionTime3 > 200){
        intersectionState = rightTurnFound;
        onIntersectionTime3 = millis();
        }
      }     
      break;
  }
}

*/