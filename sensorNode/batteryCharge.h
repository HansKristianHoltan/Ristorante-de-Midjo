void chargeZumo(){
   
if (isCharging) {
  digitalWrite(rLED, HIGH); //setter rLED high for å symbilsere at lading av ZumoBil pågår
  if (abortCharge == true && (newBatteryPer >= abortLevel)){ //checks if abortCharging is active, and if new battery% is above the abortlevel.
     
        Serial.println("CHARGING ABORTED");
        doneCharging(); //running the function isDoneCharging that resets charging values and sends the new data to the server.    
        }

   if (newBatteryPer >= chargeStop){
    doneCharging(); // running the function isDoneCharging that resets charging values and sends the new data to the server.      
        }
    
  if((millis() - zumoChargeMillis >= (chargeSpeed)) && batteryCharge == false &&  (sunValue >= sunThreshold)){
      switch (chargePer){
        case 0 ... 40:
          //Serial.println("Solar charging of Zumo"); 
          newBatteryPer += 1;
          zumoChargeMillis = millis();
          chargePer += 1;
          chargeSpeed = solarChargeSpeed * 1.2; // Setter ladehastighet lik solverdi * 1.2
        break;

         case 41 ... 100: //Sakte lading om batteriet er ladet mer enn 40% om gangen (varme)
         // i case statement over er muligheten for lading til 100% der, men i if setningen reff før vil lading bare skje om nivået er under chargeStop
          //Serial.println("Solar charging of Zumo");
          newBatteryPer += 1;
          zumoChargeMillis = millis();
          chargePer += 1;
          chargeSpeed = solarChargeSpeed * 1.4;   // Setter ladehastighet lik solverdi * 1.4
         break;
      }
  }

  
 //kjører bare om den forrige if funksjonen returnerer false. Og det må være nok % på powerbank batteriet
 else if(millis() - zumoChargeMillis >= chargeSpeed && powerBankBattery > pb_threshold) {  
  
      batteryCharge = true; //Om lading fra batteri er startet, vil zumo bare lade fra batteri helt til neste gang bilen må lades.

      switch (chargePer){
        case 0 ... 40:
          //Serial.println("Battery charging of Zumo");
          newBatteryPer += 1;
          zumoChargeMillis = millis();
          chargePer += 1;
          chargeSpeed = random(160, 260); // setter ladehastighet til et random tall mellom 160 og 260
          powerBankBattery -= 1;
        break;

         case 41 ... 100: //Sakte lading om batteriet er ladet mer enn 40% om gangen (varme)
         //Serial.println("Battery charging of Zumo");
          newBatteryPer += 1; 
          zumoChargeMillis = millis();  
          chargePer += 1;
          chargeSpeed = random(200, 280); // setter ladehastighet til et random tall mellom 200 og 280 
          powerBankBattery -= 1; 
         break;
      }
   }  

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
}
