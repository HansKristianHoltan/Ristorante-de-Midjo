#define RXD2 16
#define TXD2 17

const char* ssid = "OnePlus Nord2 5G";
const char* password = "z93mqy27";

const char* mqtt_server = "192.168.43.128";
const char* mqttUser = "gruppe10";
const char* mqttPassword = "gruppe10";

WiFiClient espClient;
PubSubClient client(espClient);

StaticJsonDocument<250> doc;

typedef struct package{
  bool isOnChargingStation;
  float batteryPrecentage;
  bool pizzaDelivered;
  int avarageSpeed;
  bool isFinishedCharging;
  int deliveryHouseNum; 
} package;

float batteryPrecentage;

package toZumo;
package fromZumo;

String recievedData;

int recieveTime = 0;
int sendTime = 0;
int rpiTime = 0;


