// ###### A function to calculate cost and reset charging states. ######
void doneCharging(){
      Serial.print("Charged Battery To: ");
      Serial.print(newBatteryPer);
      Serial.println("%");
      client.publish("batteryNewIn", String(newBatteryPer).c_str(), true);
      chargeCost = (batterySize * (float(chargePer) / 100)  * elCostDollar * heatLoss);
      Serial.print("Cost is: ");
      Serial.println(chargeCost);
      client.publish("chargeCost", String(chargeCost).c_str());
      isCharging = false;
      lastChargeState = false;  
      chargePer = 0; 
      client.publish("batteryFinishedIn", String('1').c_str()); //sending a signal to the zumo that charging is done.
      lastBatteryPer = batteryPer;
      chargeBlockerTimer = millis(); 
}
