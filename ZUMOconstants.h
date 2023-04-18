#define count_per_rev 909.7
#define cm_per_rev 11

// Definerer forskjellige innebygde Zumo-funksjoner 
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4Buzzer buzzer;
Zumo32U4Encoders encoders;

Servo pizzaServo;

// Lager en struct som skal lagre daten som både sendes og mottas til/fra esp
typedef struct package{
  bool isOnChargingStation;
  float batteryPrecentage;
  bool pizzaDelivered;
  int avarageSpeed;
  bool isFinishedCharging;
  int deliveryHouseNum; 
} package;

package toEsp;
package fromEsp;

// ??
StaticJsonDocument<250> doc;

// string som lagrer stringen sendt fra esp
String recievedData;


enum TurnState{
  turn,
  wait,
  turnBack,
  continueDriving
};

enum TurnState turnState;
 
int8_t i = 1;

enum DrivingState{
  drivingForwards,
  drivingBackwards,
  turning,
  notDriving  
};

enum DrivingState drivingState;

bool isDrivingBackwards = false;

float batteryPrecentage = 100;
int8_t batteryMin = 10;

// tidsvariabler
int previousMillis = 0;
int lastTime = 0;
int houseMillis = 0;
int sendTime = 0;
int recieveTime = 0;
int turnAroundTime = 0;
int batteryTime = 1000;
int servoTime = 0;
int turnTime = 0;
int turnTime1 = 0;
int turnTime2 = 0;
int turnTime3 = 0;
int turnTimer = 0;


double Kp = 2.5;  // Proportional gain
double Kd = 5.0;  // Derivative gain
double Ki = 0.0;  // Integral gain

double setpoint = 2000.0;
double integral = 0.0;


int speedAvg;

int8_t maxSpeed = 200;
uint8_t maxSpeedRev = -100;

int lastError = 0;
int lastErrorRev = 0;
int speedDifference;
int speedDifferenceRev;

int8_t houseNum = 0;
int8_t destination;

int lineSensorValues[5];
int houseSensor[5];


bool isOnChargingStation;
bool pizzaDelivered;
bool isFinishedCharging;