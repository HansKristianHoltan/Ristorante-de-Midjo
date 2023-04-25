#include "isDoneCharging.h"
void batteryCharge(){
   
if (isCharging == true) { 
  if (abortCharge == true && (newBatteryPer >= abortLevel)){ //checks if abortCharging is active, and if new battery% is above the abortlevel.
     
        Serial.println("CHARGING ABORTED");
        doneCharging(); //running the function isDoneCharging that resets charging values and sends the new data to the server.    
    }
    
  if((millis() - previous_chargemillis >= chargeInt) && (slowChargePer >= chargePer) && (newBatteryPer <= chargeStop - 1)) {
    previous_chargemillis = millis();
    newBatteryPer = newBatteryPer + 1;
    Serial.println("New Battery FAST:  ");
    Serial.println(newBatteryPer);
    chargePer = chargePer + 1;
    //lastChargeState = false; // can this be removed???
  }
 
 if ((millis() - previous_chargemillis >= 2*chargeInt) && (slowChargePer <= chargePer) && (newBatteryPer <= chargeStop - 1)) {
    previous_chargemillis = millis();
    newBatteryPer = newBatteryPer + 1;
    Serial.println("New Battery SLOW:  ");
    Serial.println(newBatteryPer);
    chargePer = chargePer + 1;    
  }
  
  if (newBatteryPer >= chargeStop){
    doneCharging(); // running the function isDoneCharging that resets charging values and sends the new data to the server.      
  }
}
}
