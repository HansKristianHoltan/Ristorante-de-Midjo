Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4Buzzer buzzer;

TaskHandle_t ZUMO;
TaskHandle_t battery;

uint16_t batteryPrecentage = 100;
bool isDrivingBackwards = false;

uint16_t currentMillis;
uint16_t previousMillis = 0;

int16_t maxSpeed = 200;
int8_t decreasedSpeed = 100;

int16_t maxSpeedRev = 100;

uint16_t lastError = 0;
uint16_t speedDifference;

uint8_t houseNum = 0;
uint8_t deliveryHouse;

uint16_t lineSensorValues[5];
uint16_t pizzaDeliverySensor[5];