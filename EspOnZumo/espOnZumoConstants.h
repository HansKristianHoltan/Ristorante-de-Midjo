
// definerer pins for seriellkommunikasjon med Zumo
const int RXD2 = 16;
const int TXD2 = 17;

// Wifi navn og passord
const char* ssid = "OnePlus Nord2 5G";
const char* password = "z93mqy27";

// mqtt server navn og passord
const char* mqtt_server = "192.168.60.95";
const char* mqttUser = "gruppe10";
const char* mqttPassword = "gruppe10";

// definerer funksjoner fra wifi og mqtt
WiFiClient espClient;
PubSubClient client(espClient);

// float for å lagre batteriprosent
float batteryPrecentage;

// array for henholdsvis mottagelse og sending til Zumo
float recievedData[4];
float sendingData[3];

// tidsvariabler
unsigned long recieveTime = 0;
unsigned long sendTime = 0;
unsigned long rpiTime = 0;


