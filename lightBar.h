void lightBar() {
  if(isCharging){
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
  
  else{
            digitalWrite(LED1, LOW);
            digitalWrite(LED2, LOW);
            digitalWrite(LED3, LOW);
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);
    
  }

}
