#define count_per_rev 909.7
#define cm_per_rev 11
#define chargingStation 7
#define pizzaPlace 6

// Definerer forskjellige innebygde Zumo-funksjoner 
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4Buzzer buzzer;
Zumo32U4Encoders encoders;

// definerer Servo til pizzaServo
Servo pizzaServo;

//
enum IntersectionState{
  leftTurnFound,
  rightTurnFound,
  threeOrFourWayIntersectionFound,
  noRoad,
  noIntersection
};

enum IntersectionState intersectionState;

int16_t onLineTreshold = 800;
int16_t offLineTreshold = 400;
int16_t isOnHouseSensorTreshold = 280;
 
int8_t i = 1;

enum DrivingState{
  start,
  drivingFast,
  drivingSlow,
  notDriving,
  turningAround,
  turningLeft
};

enum DrivingState drivingState;

float batteryPercentage = 20;
int8_t batteryMin = 10;

float sendingData[4];
float receivedData[3];

// tidsvariabler
unsigned long previousMillis = 0;
unsigned long lastTime = 0;
unsigned long houseMillis = 0;
unsigned long sendTime = 0;
unsigned long recieveTime = 0;
unsigned long batteryTime = 0;
unsigned long onIntersectionTime = 0;
unsigned long onIntersectionTime1 = 0;
unsigned long onIntersectionTime2 = 0;
unsigned long onIntersectionTime3 = 0;

unsigned long turnTime = 0;
unsigned long turnTime1 = 0;
unsigned long turnTime2 = 0;
unsigned long turnTime3 = 0;

unsigned long stateTime = 0;
unsigned long elapsedTime = 0;

float speedAvg = 0;

int16_t leftSpeed = 0;
int16_t rightSpeed = 0;
int maxSpeed = 200;
int maxSpeedSlow = 150;

uint16_t lastError = 0;
uint16_t speedDifference;

int8_t houseNum = 0;
int8_t destination;

int lineSensorValues[5];
int houseSensor[5];


bool onChargingStation = false;
bool onDestination = false;
bool pizzaDelivered = false;
bool isFinishedCharging = false;