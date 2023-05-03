// funksjon for å kalibrere sensor
void calibrateSensors()
{
  // vent 1000ms slik at en rekker å trekke seg vekk fra zumo
  delay(1000);

  // begynn å rotere, og kalibrere sensorene en gang hver itterasjon
  // 130 her tilsvarer 360 graders rotasjon  
  for(int i = 0; i < 130; i++)
  {
    motors.setSpeeds(-100, 100);

    lineSensors.calibrate();
  }
  // skrur av motorene igjen
  motors.setSpeeds(0, 0);
}

// generell linjefølgingsfunksjon
void lineFollower(){

  // henter posisjon basert på sensorverdier
  // 2000 når på linja, og 0 eller 4000 når av 
  // linja avhengig av hvilken side av linja zumo er på 
  int position = lineSensors.readLine(lineSensorValues);

  // endrer posisjon slik at 0 er på linja
  int error = position - 2000;

  // regner ut forskjellen i fart mellom venstre og høyre motor
  // dette gjøres ved hjelp av en PID regulator
  speedDifference = error / 2 +  3 * (error - lastError);

  // registrere forrige posisjon, slik at PID regulatoren har en feedback loop
  lastError = error;

  // regner ut farten til hver motor, med hensyn på maksimums fart, og fartsdifferansen
  leftSpeed = (int16_t)maxSpeed + speedDifference;
  rightSpeed = (int16_t)maxSpeed - speedDifference;

  // passer på at motoren ikke overstiger maksimumsfarten
  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  // setetr farten til motorene
  motors.setSpeeds(leftSpeed, rightSpeed);
}

// lik som funksjonen over, men maksimumsfarten er redusert
void lineFollowerSlow(){
 
  int position = lineSensors.readLine(lineSensorValues);

  int error = position - 2000;

  speedDifference = error / 2 +  3 * (error - lastError);

  lastError = error;

  int16_t leftSpeed = (int16_t)maxSpeedSlow + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeedSlow - speedDifference;

  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeedSlow);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeedSlow);

  motors.setSpeeds(leftSpeed, rightSpeed);
}


