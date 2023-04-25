void sendToEsp(){
  if (onChargingStation == true){
    sendingData[0] = 1;
  }
  else{
    sendingData[0] = 0;
  }
  Serial.print("onChargingStation: ");
  Serial.println(sendingData[0]);
  if (pizzaDelivered == true){
    sendingData[1] = 1;
  }
  else{
    sendingData[1] = 0;
  }
  sendingData[2] = batteryPercentage;
  sendingData[3] = speedAvg;
  int sendingArraySize = sizeof(sendingData) / sizeof(float);
  Serial1.write((uint8_t*)sendingData, sendingArraySize * sizeof(float));
}

void recieveFromEsp(){
  if(Serial1.available() >= 3){
    int numBytes = Serial1.readBytes((uint8_t*)receivedData, sizeof(receivedData));
    if (batteryPercentage > batteryMin){
      destination = receivedData[0];
    }
    isFinishedCharging = receivedData[1];
    Serial.print("isFinishedCharging: ");
    Serial.println(isFinishedCharging);
    if (isFinishedCharging == 1){
      batteryPercentage = receivedData[2];
    } 
  }
  return destination;
}