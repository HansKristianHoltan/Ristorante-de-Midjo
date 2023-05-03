// funksjon for hva som skal skje når Zumo ankommer ladestasjon
// og trenger å lades
void chargeBattery(){
  // skru av motorene
  motors.setSpeeds(0,0);
  drivingState = notDriving;

  // setter lik true, slik at zumo selv vet at den er ved ladestasjonen
  onChargingStation = true;

  // hvis ferdig å lade
  if (isFinishedCharging == 1){
    Serial.println("ferdig ladet");
    // fortsett å kjøre
    drivingState = drivingFast;
    
    // ikke lenger destinasjon, eller lader
    onDestination = false;
    onChargingStation = false;
    isFinishedCharging = 0;
    destination = 6;
  }
}

// funksjon for å regne ut fart
void getSpeed(){

  // henter hvor counts fra encoder, på både høyre og venstre motor
  // reseter så counten
  int leftCount = encoders.getCountsAndResetLeft();
  int rightCount = encoders.getCountsAndResetRight();
  
  // regner ut omdregninger; omdregning = count / count per omdregning
  int leftRev = leftCount / count_per_rev;
  int rightRev = rightCount / count_per_rev;    
  
  // regner ut fart; fart = omdregninger * cm per omdregning
  int speedLeft = leftRev * cm_per_rev;
  int speedRight = rightRev * cm_per_rev;

  // gjennomsnittsfart mellom motorene
  speedAvg = (speedLeft + speedRight)/2;  
  
}

// batteri simulasjon
float SWbattery(){

  // Hvert sekund regner ut tap i batteriprosent
  if (millis() - batteryTime > 1000){

    // Henter farten
    getSpeed();
    
    // Dersom Zumo har fart, bruk farten til å regne ut ny batteriprosent
    if (speedAvg != 0){
    batteryPercentage -= 0.1 * abs(speedAvg);
    }

    // Dersom Zumo ikke har fart, og den ikke lader, reduser batterprosent med en liten kosntant.
    else if (onChargingStation == false){
      batteryPercentage -= 0.01;
    }
    batteryTime = millis();
}
}