
void doneCharging(){
      Serial.print("Charged Battery To: ");
      Serial.print(newBatteryPer);
      Serial.println("%");
      client.publish("batteryNewIn4", String(newBatteryPer).c_str());
      chargeCost = (batterySize * (float(chargePer) / 100)  * elCostDollar * heatLoss); //regner ut lade kostnad
      Serial.print("Cost is: ");
      Serial.println(chargeCost);
      client.publish("chargeCost", String(chargeCost).c_str()); // publiserer kostnaden til serveren
      isCharging = false;     
      lastChargeState = false;  
      chargePer = 0; 
      client.publish("batteryFinishedIn", String('1').c_str()); //sending a signal to the zumo that charging is done.
      lastBatteryPer = batteryPer;
      chargeBlockerTimer = millis(); // setter chargeBlockTimer lik millis for å legge inn en liten pause mellom gangene det er mulig å lade
      batteryCharge = true;
      digitalWrite(rLED, LOW);
}


void sendSensorData() {
  if (! bme.performReading()) { // Om det ikke kan foretas en sensor avlesning:
    Serial.println("Failed to perform reading :("); //printer error melding
    return;
  }
  
  temperature = bme.temperature;           // Leser av sensor verdiene for temperatur og lagrer de i variabelen
  humidity = bme.humidity;                 // Leser av sensor verdier for fuktighet og lagrer de i variabelen
  pressure = (bme.pressure /100);          // Leser av sensor verdier for trykk, gjør om verdien fra Pa til hPa og lagrer de i variabelen
  gasSens = (bme.gas_resistance / 1000.0); // Leser av sensor verdier for luftkvalitet, gjør om verdien fra Ohm til kOhm og lagrer de i variabelen
 
   if (millis() - previousmillis >= intervalTime) {
    
    char tempString[8]; // lager en character array for å holde på verdien  
    dtostrf(temperature, 1, 2, tempString); // konverterer fra float til characterarray
    /*
    Serial.print("Temperature [C]: "); //brukt til feilsøking
    Serial.println(tempString); //brukt til feilsøking
    */
    client.publish("tempSens", tempString); // "publiserer" temperatur sensor verdi til topic "tempSens"
    

    char humString[8]; // lager en character array for å holde på verdien
    dtostrf(humidity, 1, 2, humString); // konverterer fra float til characterarray
    /*
    Serial.print("Humidity [%]: "); //brukt til feilsøking
    Serial.println(humString); //brukt til feilsøking
    */
    client.publish("humSens", humString); // "publiserer" luftfuktighet sensor verdi til topic "humSens"
    

    char presString[8]; // lager en character array for å holde på verdien
    dtostrf(pressure, 1, 2, presString); // konverterer fra float til characterarray
    /*
    Serial.print("Pressure [hPa]: "); //brukt til feilsøking
    Serial.println(presString); //brukt til feilsøking
    */
    client.publish("presSens", presString); // "publiserer" trykk sensor verdi til topic "presSens"
    

    char gasString[8]; // lager en character array for å holde på verdien
    dtostrf(humidity, 1, 2, gasString); // konverterer fra float til characterarray
    /*
    Serial.print("Gas Value [kOhm]: "); //brukt til feilsøking
    Serial.println(gasString); //brukt til feilsøking
    */
    client.publish("gasSens", gasString); // "publiserer" gass sensor verdi til topic "gasSens"  

    previousmillis = millis(); //resetter telleren
}
}
