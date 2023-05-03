// funksjon for å sende til esp
void sendToEsp(){
  // hvis zumo er på ladestasjon, send 1, hvis ikke send 0
  if (onChargingStation == true){
    sendingData[0] = 1;
  }
  else{
    sendingData[0] = 0;
  }

  // debugging
  //Serial.print("onChargingStation: ");
  //Serial.println(sendingData[0]);

  // hvis pizza er levert, send 1, hvis ikke send 0
  if (pizzaDelivered == true){
    sendingData[1] = 1;
  }
  else{
    sendingData[1] = 0;
  }

  // sender nåhverende batteryprosent og fart
  sendingData[2] = batteryPercentage;
  sendingData[3] = speedAvg;

  // regner ut størrelse på arrayen, og sender arrayen over til esp ved hjelp av seriell kommunikasjon
  int sendingArraySize = sizeof(sendingData) / sizeof(float);
  Serial1.write((uint8_t*)sendingData, sendingArraySize * sizeof(float));
}

// funksjon for å motta fra esp
void recieveFromEsp(){
  // hvis det registreres en sending med riktig størrelse
  if(Serial1.available() >= 3){
    // henter inn det som ble mottat ved hjelp av seriell kommunikasjon, og lagrer det i en array
    int numBytes = Serial1.readBytes((uint8_t*)receivedData, sizeof(receivedData));

    // så lenge batteriet ikke må lades, hent in ny pizza-leveranse
    if (batteryPercentage > batteryMin){
      destination = receivedData[0];
    }
    // lagrer 1 eller 0 til isFinishedCharging, 1 hvis ferdig å lade, 0 hvis ikke
    isFinishedCharging = receivedData[1];

    // hvis ferdig å lade, registrer ny batteryprosent
    if (isFinishedCharging == 1){
      batteryPercentage = receivedData[2];
    } 
  }
  return destination;
}