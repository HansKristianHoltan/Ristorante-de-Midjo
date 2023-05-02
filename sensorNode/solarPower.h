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
    if(powerBankBattery <= 150){
               if(millis()- lowBatError >= errLEDTime){  // blinker det røde lyset lfor å symbolisere lavt batterinivå på ladestasjonen
          lowBatError = millis(); 
          
          if(rLEDstate == off){        
          digitalWrite(rLED, HIGH); // Slår av lavt nivå varslingslys
          rLEDstate = on;
          }
          else if (rLEDstate == on){
            digitalWrite(rLED, LOW); // Slår av lavt nivå varslingslys
          rLEDstate = off; 
          }                           
        }
    }
    else{
      digitalWrite(rLED, LOW);
    }

     switch (powerBankBattery){ //Visualisering av powerBank batterinivå om Zumobilen ikke lader     
      case 0 ... 100: // 0 til 100 (0-20%) av brukelig nivå 
        digitalWrite(LED1, HIGH); // LED1 på
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, LOW);
       
      break;

      case 101 ... 200: // 101 til 200 (21-40%) av brukelig nivå 
        digitalWrite(LED1, HIGH); // LED1 på
        digitalWrite(LED2, HIGH); // LED2 på
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, LOW);
              
      break;

      case 201 ... 300: // 201 til 300 (41-60%) av brukelig nivå 
        digitalWrite(LED1, HIGH); // LED1 på
        digitalWrite(LED2, HIGH); // LED2 på
        digitalWrite(LED3, HIGH); // LED3 på
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, LOW);

      break;

      case 301 ... 400: // 301 til 400 (61-80%) av brukelig nivå 
        digitalWrite(LED1, HIGH); // LED1 på
        digitalWrite(LED2, HIGH); // LED2 på
        digitalWrite(LED3, HIGH); // LED3 på
        digitalWrite(LED4, HIGH); // LED4 på
        digitalWrite(LED5, LOW);
        
      break;

      case 401 ... 500: // 401 til 500 (81-100%) av brukelig nivå    
        digitalWrite(LED1, HIGH); // LED1 på
        digitalWrite(LED2, HIGH); // LED2 på
        digitalWrite(LED3, HIGH); // LED3 på
        digitalWrite(LED4, HIGH); // LED4 på
        digitalWrite(LED5, HIGH); // LED5 på
        
      break;   
  }
 }
}
