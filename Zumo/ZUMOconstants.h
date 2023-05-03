// konstanter for utregning av fart
const int count_per_rev = 909.7;
const int cm_per_rev = 11;

// konstaner for å definere lokasjoner
const int chargingStation = 7;
const int pizzaPlace = 6;

// Definerer forskjellige innebygde Zumo-funksjoner 
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4Buzzer buzzer;
Zumo32U4Encoders encoders;

// definerer Servo til pizzaServo
Servo pizzaServo;

//////////////////////////////////////////////////////
//       forkskjellige sensor-grenseverdier         //
// må endres for hver gang Zumo er på nytt underlag //
//////////////////////////////////////////////////////
int16_t onLineTreshold = 800;
int16_t offLineTreshold = 400;
int16_t isOnHouseSensorTreshold = 220;
 
// konstant for å iterer gjennom en switch case
int8_t i = 0;

// States for å definere kjøringen
enum DrivingState{
  start,
  drivingFast,
  drivingSlow,
  notDriving,
  turningLeft,
  noRoad
};

enum DrivingState drivingState;

// States for å definere snu-retning
enum Direction{
  right,
  left
};

enum Direction direction;

// batteri startprosent, og minimumsprosent
float batteryPercentage = 12;
int8_t batteryMin = 10;

// array som sender, og array som mottar data til/fra esp
float sendingData[4];
float receivedData[3];

// tidsvariabler
unsigned long previousMillis = 0;
unsigned long lastTime = 0;
unsigned long houseMillis = 0;
unsigned long sendTime = 0;
unsigned long recieveTime = 0;
unsigned long batteryTime = 0;
unsigned long turnTime = 0;
unsigned long turnTime1 = 0;
unsigned long stateTime = 0;
unsigned long elapsedTime = 0;
unsigned long noHouseMillis = 0;

// variabel for å lagre farten
float speedAvg = 0;

// variabeler som brukes til å regulere farten til motoren
int16_t leftSpeed = 0;
int16_t rightSpeed = 0;
int maxSpeed = 200;
int maxSpeedSlow = 150;
uint16_t lastError = 0;
uint16_t speedDifference;

// variabler hvor nåhverende hus, og destinasjonen lagres
int8_t houseNum = 0;
int8_t destination = pizzaPlace;
int8_t previousDestination;
// arrays med linje-sensorverdier
int lineSensorValues[5];
int houseSensor[5];

// boolske variabler for å registrere forskjellige handlinger som Zumo gjør
bool onChargingStation = false;
bool onDestination = false;
bool pizzaDelivered = false;
bool isFinishedCharging = false;
bool isOnPizzaPlace = false;
bool allowCount = true;
