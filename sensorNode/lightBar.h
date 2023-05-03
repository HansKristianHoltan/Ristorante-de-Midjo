
void lightBarZumo () { //funksjon for å illustrere lading  av bil
  // switch case for å blinke det intervallet (1/5, 2/5, 3/5, 4/5 ,5/5) som lades opp 
  if(millis() - blinkTimer >= blinkInterval){
      switch (newBatteryPer) {  
       case 0 ... 20:
    
            blinkTimer = millis();

            digitalWrite(LED1, !digitalRead(LED1)); // blinker LED1 ved å sette motsatt verdi hver gang case statement kjører
            digitalWrite(LED2, LOW);
            digitalWrite(LED3, LOW);
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);
            
       break;

       case 21 ... 40:
                
            blinkTimer = millis();
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, (!digitalRead(LED2))); // blinker LED2 ved å sette motsatt verdi hver gang case statement kjører
            digitalWrite(LED3, LOW);
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);

       break;

       case 41 ... 60:

            blinkTimer = millis();
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, (!digitalRead(LED3)));  // blinker LED3 ved å sette motsatt verdi hver gang case statement kjører
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);
            
       break;

       case 61 ... 80:

            blinkTimer = millis();
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, HIGH);
            digitalWrite(LED4, (!digitalRead(LED4)));  // blinker LED4 ved å sette motsatt verdi hver gang case statement kjører
            digitalWrite(LED5, LOW);           


       break;

       case 81 ... 100:

            blinkTimer = millis();
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, HIGH);
            digitalWrite(LED4, HIGH);
            digitalWrite(LED5, (!digitalRead(LED5)));  // blinker LED5 ved å sette motsatt verdi hver gang case statement kjører

       break;    
 }            
}
}


void lightbarpBB () {
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
