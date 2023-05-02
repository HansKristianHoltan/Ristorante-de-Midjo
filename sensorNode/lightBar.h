/*
 * 
 * *** NOT IN USE, FUNCTYION IS NOW IN batteryCharge.h *** *
void lightBar() {
  if(isCharging){
    
    if(millis() - fadeTimer >= 5){  // Dimme inn og ut en Rød LED om Zumobilen lader. Ny verdi hvert 5. ms 
      
      analogWrite(rLED, rLEDBrightness); //Skriver en PWM verdi til digitalporten (pass på at det ikke er en ADC2 port, da disse ikke fungerer ved bruk av WiFi)
      rLEDBrightness += (fadeInt);       //Regner ut en ny verdi for lysstyrken     
      fadeTimer = millis();
      
      if(rLEDBrightness >= 255){ // Om verdien for lysstyrke er over, eller lik 255, settes verdien til 255. 
        rLEDBrightness = 255;
        fadeInt = -3;   // fadeInt variabelen settes negativ, for å senke verdien i de neste iterasjonene     
      }
      
      else if(rLEDBrightness <= 0){ // Om verdien for lysstyrke er under, eller lik 0, settes verdien til 0
        fadeInt = 3; // fadeInt variabelen settes positiv, for å øke verdien i de neste iterasjonene
        rLEDBrightness = 0;
      }             
}

      switch (newBatteryPer) {
       case 0 ... 20:
        if ((millis() - blinkTimer >= blinkInterval) && LED == off){
          
            LED = on;
            blinkTimer = millis();

            digitalWrite(LED1, HIGH);   
            digitalWrite(LED2, LOW);
            digitalWrite(LED3, LOW);
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);
            
          }
          if ((millis() - blinkTimer >= blinkInterval) && LED == on){
            LED = off;
            blinkTimer = millis();
            digitalWrite(LED1, LOW);
            digitalWrite(LED2, LOW);
            digitalWrite(LED3, LOW);
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);
          }
        

       break;

       case 21 ... 40:
       if ((millis() - blinkTimer >= blinkInterval) && LED == off){
            LED = on;
            blinkTimer = millis();
            Serial.println("ON");
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, LOW);
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);
            
          }
          if ((millis() - blinkTimer >= blinkInterval) && LED ==on){
            LED = off;
            blinkTimer = millis();
            Serial.println("OFF");
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, LOW);
            digitalWrite(LED3, LOW);
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);
          }
        

       break;

       case 41 ... 60:

       if ((millis() - blinkTimer >= blinkInterval) && LED == off){
            LED = on;
            blinkTimer = millis();

            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, HIGH);
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);
            
          }
          if ((millis() - blinkTimer >= blinkInterval) && LED == on){
            LED = off;
            blinkTimer = millis();
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, LOW);
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);
          
        }

       break;

       case 61 ... 80:

       if ((millis() - blinkTimer >= blinkInterval) && LED == off){
            LED = on;
            blinkTimer = millis();

            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, HIGH);
            digitalWrite(LED4, HIGH);
            digitalWrite(LED5, LOW);
            
          }
          if ((millis() - blinkTimer >= blinkInterval) && LED == on){
            LED = off;
            blinkTimer = millis();
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, HIGH);
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);
          
        }

       break;

       case 81 ... 100:

        if ((millis() - blinkTimer >= blinkInterval) && LED == off){
            LED = on;
            blinkTimer = millis();

            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, HIGH);
            digitalWrite(LED4, HIGH);
            digitalWrite(LED5, HIGH);
            
          }
          if ((millis() - blinkTimer >= blinkInterval) && LED == on){
            LED = off;
            blinkTimer = millis();
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, HIGH);
            digitalWrite(LED4, HIGH);
            digitalWrite(LED5, LOW); 
        }

       break;
      
    
 }
}   
}
 */
