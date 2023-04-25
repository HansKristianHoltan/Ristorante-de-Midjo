/********* VARIABLES *********/

unsigned long previousmillis = 0;
int intervalTime = 2000;
uint8_t I2Caddress = 0x77;
uint8_t houseNum = 0;

/* Calibrate sealever preassure from Yr.no: https://www.yr.no/nb/detaljer/tabell/1-211102/Norway/Tr%C3%B8ndelag/Trondheim/Trondheim */
#define SEALEVELPRESSURE_HPA (1041)


// Define variables to store BME680 readings to be sent
float temperature;
float humidity;
float pressure;
float gasSens;

        
   /* MQTT, WIFI AND PUBSUBCLIENT VARIABLES */
const char* ssid = "OnePlus Nord2 5G"; // Mobile WiFi HotSpot
const char* password = "z93mqy27";  // Password
const char* mqttUser = "gruppe10";  //mqtt user login
const char* mqttPassword = "gruppe10";  //mqtt user login 

const char* mqtt_server = "192.168.60.95"; // Add MQTT Broker IP address:      
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

        /* CHARGING VARIABLES */
bool isCharging = false;   // SETS CHARGING STATE
uint8_t batteryPer;
uint8_t newBatteryPer;
bool chargeState = false;
unsigned long previous_chargemillis = 0;  // A variable to to store time, and compare to millis ()
uint8_t abortLevel = 60;                  // Abort chargin, only if its = to or above the abortLevel
uint8_t lastBatteryPer = 0;               // Variable to store the last battery %,
bool lastChargeState = false;             // storing the last charging state
int chargeInt = 200;                      // every 200 ms, 1 % is added when fast charging.
uint8_t slowChargePer = 40;               // the first 40% will be fast charging.
bool abortCharge = false;                 // defining a boolean variable to abort charging if a pizza order is recieved while charging.
uint8_t chargeStop = 80;                  // defining max% the battery will charge too. 
uint8_t chargePer = 0;                    // defining a variable for a counter that counts battery % while charging
unsigned long chargeBlockerTimer = 0;     // a millis timer to block charging, if charging just finished.
int chargeBlockerInterval = 4000;         // blocks the charging for 4000 ms after charging finished.


// Structuring a message, this was done in case esp-now was going to be used.
typedef struct struct_message {
    float temp;
    float hum;
    float pres;
    float gas;
} struct_message;

    
     /*         Cost Calculation Variables        */
   

float batterySize = 40; //(kWH)
float electricalCostNok = 0.60; // 0,6 NOK / kWH (https://www.hvakosterstrommen.no/i/trondheim)
float dollarValue = 10.638; // NOK
float elCostDollar = (electricalCostNok / dollarValue); //Dollar/kWH
float chargeCost;
float heatLoss = 1/0.9; //(90% efficient)


/* Charging visulization variables */

enum ledState {  // creating a variable to store info if the LEDs are ON or OFF
  on, off
};

ledState LED = off;  //assigning the new variable to the variable LED and setting it to off.

const int LED1 = 15;
const int LED2 = 2;
const int LED3 = 4;
const int LED4 = 5;
const int LED5 = 18;

unsigned long blinkTimer = 0;
int blinkInterval = 250; //setting blink ON and OFF time to 500 ms
