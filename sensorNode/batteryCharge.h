void chargeZumo(){
   
if (isCharging) {
  digitalWrite(rLED, HIGH); //setter rLED high for å symbilsere at lading av ZumoBil pågår

  //
  if (abortCharge == true && (newBatteryPer >= abortLevel)){ //checks if abortCharging is active, and if new battery% is above the abortlevel.
     
        Serial.println("CHARGING ABORTED");
        doneCharging(); // funksjonen resetter alle verdier, og avslutter ladingen, og publiserer data til mqtt serveren    
    }

   if (newBatteryPer >= chargeStop){
    doneCharging(); // funksjonen resetter alle verdier, og avslutter ladingen, og publiserer data til mqtt serveren        
        }
    if(powerBankBattery <= pb_threshold){ // sjekker om nivået på powerBank er under minste nivå
      if(sunValue >= sunThreshold){ // sjekker om  
          batteryCharge = false; // tillater lading med solcelle om det er nok sol
      }
        
      else{ // stopper lading om powerBank batteriet kommer under minste nivå, og solnivået er for svakt
        Serial.println("PowerBankBattery is LOW.. Charging stopped at: ");
        Serial.print(newBatteryPer);
        doneCharging(); // funksjonen resetter alle verdier, og avslutter ladingen, og publiserer data til mqtt serveren 
      }      
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


   
lightBarZumo();
}
}
