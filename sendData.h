// ###### PRINTING SENSOR VALUES TO SERIAL MONITOR ######
// ###### USED FOR TROUBLESHOOTING PURPOSES ######
void sendData() {


  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  temperature = bme.temperature;
  humidity = bme.humidity;
  pressure = (bme.pressure /100);
  gasSens = bme.gas_resistance / 1000.0;
  

  
   if (millis() - previousmillis >= intervalTime) {

  //  getReadings();
  
    previousmillis = millis();
    Serial.print("NEW BATTERY PRINT: ");
    Serial.println(newBatteryPer);
    Serial.print(" Abort State: ");
    Serial.println(abortCharge);
  /*
  Serial.print("Temperature = ");
  Serial.print(bme.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bme.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(bme.humidity);
  Serial.println(" %");

  Serial.print("Gas = ");
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(" KOhms");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
  Serial.println();
  */
  
  char tempString[8];

  
    dtostrf(temperature, 1, 2, tempString);
    /*
    Serial.print("Temperature [C]: ");
    Serial.println(tempString);
    */
    client.publish("tempSens", tempString);
    

    char humString[8];
    dtostrf(humidity, 1, 2, humString);
    /*
    Serial.print("Humidity [%]: ");
    Serial.println(humString);
    */
    client.publish("humSens", humString);
    

    char presString[8];
    dtostrf(pressure, 1, 2, presString);
    /*
    Serial.print("Pressure [hPa]: ");
    Serial.println(presString);
    */
    client.publish("presSens", presString);
    

    char gasString[8];
    dtostrf(humidity, 1, 2, gasString);
    /*
    Serial.print("Gas Value [kOhm]: ");
    Serial.println(gasString);
    */
    client.publish("gasSens", gasString); 
}
}
