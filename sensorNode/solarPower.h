void chargePowerBank() {
sunValue = map(analogRead(sunSensor),0 , 1100, 1, 100); //omgjør verdien fra lyssensoren til en verid som er lettere å bruke. disse verdiene ble funnet ved å teste sensoren i lys og mørke
solarChargeSpeed = 1000/sunValue; //Regner ut en ladehastighet som gjør at mye lys => hurtigere lading (1000 / 100 >  1000/50)
//Serial.println(sunValue);
//Serial.println(analogRead(sunSensor));
  if (!isCharging){
    
    if (sunValue >= sunThreshold){ //Om zumoen ikke skal lade og solverdien er over minsteverdi skal powerbank batteriet lades.
    if(powerBankBattery < 501) { //tillater bare switch case å kjøre om batteriet er lavere enn 500      
      if(powerBankBattery < 0){
        powerBankBattery = 0;      
      }
        
      
    switch (powerBankBattery) {
      case 0 ... 150:
        if(millis() - powerBankTimer >= solarChargeSpeed){
          powerBankBattery += 1; // for hver iterasjon vil powerBankBattery øke med 1.
          powerBankTimer = millis(); //resetter timer så den er klar for å telle neste iterasjon
          //Serial.println(sunValue);
          //Serial.println(powerBankBattery);
        }
      break;        
      case 151 ... 380:
        if(millis() - powerBankTimer >= (1.25 * solarChargeSpeed)){ //powerBank batteriet lades saktere når det nermer seg fult
          powerBankBattery += 1; // for hver iterasjon vil powerBankBattery øke med 1.
          powerBankTimer = millis(); //resetter timer så den er klar for å telle neste iterasjon
          //Serial.println(sunValue);
          //Serial.println(powerBankBattery);
        }
      break;
      case 381 ... 499:
        if(millis() - powerBankTimer >= (1.5 * solarChargeSpeed)){ //powerBank batteriet lades saktere når det nermer seg fult
          powerBankBattery += 1; // for hver iterasjon vil powerBankBattery øke med 1.
          powerBankTimer = millis(); //resetter timer så den er klar for å telle neste iterasjon
          //Serial.println(sunValue);
          //Serial.println(powerBankBattery);
        }
      break; 
      case 500:

      break;         
   }
    }
    }
    
lightbarpBB (); // kjører funksjonen som illustrerer ladenivå

 }
}
