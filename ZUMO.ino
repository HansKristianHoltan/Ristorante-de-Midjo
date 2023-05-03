#include <Zumo32U4.h>
#include <Wire.h>
#include "ZUMO_constants.h"
#include "lineFollower.h"
#include "isOnLocation.h"
#include "SWbattery.h"

void setup() {
  Serial.begin(9600);

  xTaskCreatePinnedToCore(
  ZUMO,
  "Normal_zumo_behavior",
  10000,
  NULL,
  1,
  &ZUMO,
  0
);

xTaskCreatePinnedToCore(
  SWbattery,
  "battery simulation",
  10000,
  NULL,
  1,
  &battery,
  0
);

  lineSensors.initFiveSensors();
  lineSensors.emittersOn();
  calibrateSensors();
}

void loop(){}

void ZUMO(){
  while(true){
  getPosition();
    if (batteryPrecentage > 10){
      setSpeeds();
    }
    else{
      turnAround();
      setSpeedsReverse();
    }
  isOnHouse();
  }   
}
