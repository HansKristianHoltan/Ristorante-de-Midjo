
/********* VARIABLES *********/

unsigned long previousmillis = 0;
int intervalTime = 2000;
uint8_t I2Caddress = 0x77;
uint8_t houseNum = 0;

/* kalibrer lufttrykk ved havnivå med data fra: https://www.yr.no/nb/detaljer/tabell/1-211102/Norway/Tr%C3%B8ndelag/Trondheim/Trondheim */
#define SEALEVELPRESSURE_HPA (1041) // brukes for å regne ut høyde over havet.


// Definere variabler for å lagre BME680 sensor data på:
float temperature;  // float pga desimaltall
float humidity;     // float pga desimaltall
float pressure;     // float pga desimaltall
float gasSens;      // float pga desimaltall

        
   /* MQTT, WIFI AND PUBSUBCLIENT VARIABLES */
const char* ssid = "OnePlus Nord2 5G";  //4G HOT SPOT SSID
const char* password = "z93mqy27";      // WIFI PASSORD
const char* mqttUser = "gruppe10";      //MQTT USER LOGIN: BRUKER
const char* mqttPassword = "gruppe10";  //MQTT USER LOGIN: PASSORD

const char* mqtt_server = "192.168.60.95"; // LEGGER TIL MQTT SERVER ADDRESSE      
WiFiClient espClient; //Oppretter en tilkobling til et WiFi-nettverk.
PubSubClient client(espClient); //Oppretter en tilkobling til en MQTT-broker som bruker WiFi-tilkoblingen.
//long lastMsg = 0;
//char msg[50];  
//int value = 0;

        /* CHARGING VARIABLES */
bool isCharging = false;                  // lagrer lade status
uint8_t batteryPer;                       // variabel for å lagre innkommende batteri prosent
uint8_t newBatteryPer;                    // variabel for å lagre ny batteriprosent  
uint8_t abortLevel = 60;                  // Variabel for å definere hvilken batteri prosent som tillater avslutting va lading om en pizza bestilling kommer.
uint8_t lastBatteryPer = 0;               // Variabel for å lagre forrige batteriprosen
bool lastChargeState = false;             // Variabel for å lagre forrige ladestatus
bool abortCharge = false;                 // Variabel for å avslutte lading om en pizza bestilles
uint8_t chargeStop = 80;                  // Definerer Zumo maks lade prosent 
uint8_t chargePer = 0;                    // En variabel for å huske hvor mange % batteriet har ladet
unsigned long chargeBlockerTimer = 0;     // En variabel for å lagre tiden i ms fo å blokkere lading rett etter lading er ferdig.
int chargeBlockerInterval = 4000;         // definerer et blokkeringintervall
unsigned long fadeTimer = 0;              // definerer en timer variabel for dimming va rLED
unsigned long powerBankTimer = 0;         // defionerer en timer variabel for å lade opp powerBankBattery
uint8_t sunThreshold = 60;                // definerer et minstenivå av sollys for solcelle lading
const int sunSensor = 34;                 // definerer en konstant pinne for photresistoren
int powerBankBattery = 500;               // setter batterikapasiteten til 500 kWh / 625 kwH (500 = 0.8 * 625)
unsigned long zumoChargeMillis = 0;       // definerer en timer for lading av Zumobilen
int solarChargeSpeed;                     // definerer en variabel for å lagre ladehastigheten til powerBanken
uint8_t chargeSpeed;                      // definerer en variabel for å lagre ladehastigheten til Zumobilen
bool batteryCharge = false;               // definerer en boolsk variabel for å ikke tillate sol lading, om nivået først har bikket under minste nivå
uint8_t pb_threshold = 100;               // definerer en minsteverdi for powerbanken
int sunValue;                             // variabel som brukes til å lagre lysnivået
int rLEDBrightness = 0;                   // variabel for å lagre lysstyrken til rLED
int fadeInt = 3;                          // en variabel som setter 
unsigned long lowBatError = 0;            // en variabel for å time blinking av rLED om powerbank er under alarm nivå


    
     /*         Cost Calculation Variables        */
   

float batterySize = 40;                                   // definerer at Zumo har et batteri på 40(kWH), som er vanlig elbil størrelse (små el-biler)
float electricalCostNok = 0.60;                           // 0,6 NOK / kWH (https://www.hvakosterstrommen.no/i/trondheim)
float dollarValue = 10.638;                               // 1 usd er 10,638NOK
float elCostDollar = (electricalCostNok / dollarValue);   // Dollar/kWH
float chargeCost;                                         // variabel for å regne ut kostnaden
float heatLoss = 1/0.9; //(90% efficient)                 // Variabel som brukes i utregning av strømforbruk, opplading er ikke 100% effektivt, her settes effektiviteten til 90%


/* Charging visulization variables */


enum ledState {  // creating a variable to store info if the LEDs are ON or OFF  // Denne var brukt i en tidligere versjon, blir stående i tilfelle den skal brukes igjen
  on, off
};

ledState rLEDstate = off; // lager en variabel av typen "ledState" for å lagre verdien til led

const int LED1 = 15; // definerer at pinne 15 er koblet til LED1  
const int LED2 = 2;  // definerer at pinne 2 er koblet til LED2 
const int LED3 = 4;  // definerer at pinne 4 er koblet til LED3 
const int LED4 = 5;  // definerer at pinne 5 er koblet til LED4 
const int LED5 = 18; // definerer at pinne 18 er koblet til LED5
const int rLED = 32; // definerer at rLED er koblet til pinne 13 

int errLEDTime = 250;                     // blinker av og på i 250ms intervaller ved lavt batteri
unsigned long blinkTimer = 0;  // definerer en teller for å telle blinkingen ved lading av Zumobilen
int blinkInterval = 250; // Setter av og på intervallet til 250ms
