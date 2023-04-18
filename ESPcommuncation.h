void sendToEsp(){
  Serial.print("batteri:");
  Serial.println(batteryPrecentage);
  doc["onChargingStation"] = toEsp.pizzaDelivered;
  doc["batteryPrecentage"] = batteryPrecentage;
  if (turnState == wait){
    doc["pizzaDelivered"] = true;
  }
  else{
    doc["pizzaDelivered"] = false;
  }
 
  doc["avarageSpeed"] = toEsp.avarageSpeed;
  String sendingData;
  serializeJson(doc, sendingData);
  Serial1.println(sendingData);
}

void recieveFromEsp(){
  if(Serial1.available()){
    recievedData = Serial1.readStringUntil('\n');    
  }
  deserializeJson(doc, recievedData);
  if (destination != 6){
      destination = doc["deliveryHouseNum"];
  }
  isFinishedCharging = doc["isFinishedCharging"];
  if (isFinishedCharging == true){
    batteryPrecentage = doc["batteryPrecentage"];
  }
}