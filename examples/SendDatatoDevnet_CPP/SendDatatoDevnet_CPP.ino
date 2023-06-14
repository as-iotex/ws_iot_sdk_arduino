#include <stdlib.h>

#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#error Platform not supported
#endif

#include <WiFiClient.h>
#include <PubSubClient.h>           // https://github.com/knolleary/pubsubclient/releases/tag/v2.8
#include <wsiotsdk.h>

#include <time.h>
#define emptyString String()

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMillis = 0;
time_t now;
time_t nowish = 1510592825;

int8_t TIME_ZONE = -5;          //NYC(USA): -5 UTC
static const uint8_t private_key[] = {0xa1, 0x73, 0x6f, 0xbf, 0x37, 0xa2, 0xfc, 0xb8, 0xfe, 0xe2, 0x02, 0xdb, 0x0c, 0x63, 0x91, 0xdf, 0xa4, 0x61, 0x86, 0x29, 0xb1, 0x86, 0xa6, 0x90, 0x65, 0x85, 0x2d, 0xfc, 0xd8, 0x8f, 0x58, 0x19};
static const char ssid[] = "StayHungry";
static const char pass[] = "zjn.19821225";

psa_key_id_t key_id = 0;

#define KEY_BITS    256
#define THINGNAME   "IoTeX_Demo"

#define USER_TOKEN  "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJQYXlsb2FkIjoiOTAyODE3NDM1MDA2OTc2MSIsImlzcyI6InczYnN0cmVhbSJ9._KxP2gGC33CFWq0H31M3MNstuM1ygAj5Yk10sYnWSEc"
#define USER_TOPIC  "eth_0x31c3785bebe03cc5ba691c486d6d1cdf8bb438c4_arduino_test"

void iotex_import_key(void)
{
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_status_t status;
    unsigned char prikey[32] = {0};
    unsigned int  prikey_len = 0;

    uint8_t exported[PSA_KEY_EXPORT_ECC_PUBLIC_KEY_MAX_SIZE(KEY_BITS)];	
	  size_t exported_length = 0;
    char dev_address[100] = {0};

    memcpy(prikey, private_key, sizeof(prikey));

    /* Set key attributes */
    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_SIGN_HASH | PSA_KEY_USAGE_VERIFY_HASH);
    psa_set_key_algorithm(&attributes, PSA_ALG_ECDSA(PSA_ALG_SHA_256));
    psa_set_key_type(&attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_K1));
    psa_set_key_bits(&attributes, 256);

    /* Import the key */
    status = psa_import_key(&attributes, prikey, 32, &key_id);
    if (status != PSA_SUCCESS) {
        key_id = 0;
        return;
    }

    status = psa_export_public_key(key_id, exported, sizeof(exported), &exported_length);
	  if (status != PSA_SUCCESS) {
        return;
	  }
}

int iotex_mqtt_pubscription(unsigned char *topic, unsigned char *buf, unsigned int buflen, int qos) {
    return client.publish((const char *)topic, (const uint8_t *)buf, buflen, false);
}

int iotex_mqtt_subscription(unsigned char *topic) {
    return client.subscribe((const char *)topic);
}

time_t iotex_time_set_func(void) {
    return time(nullptr);
}

void NTPConnect(void)
{
    Serial.print("Setting time using SNTP");

    configTime(TIME_ZONE * 3600, 0, "pool.ntp.org", "time.nist.gov");
    
    now = time(nullptr);
    while (now < nowish) {
      delay(500);
      Serial.print(".");
      now = time(nullptr);
    }
    Serial.println("done!");

    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);
    
    Serial.print("Current time: ");
    Serial.print(asctime(&timeinfo));
}

void messageReceived(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Received [");
    Serial.print(topic);
    Serial.print("]: ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void pubSubErr(int8_t MQTTErr)
{
  if (MQTTErr == MQTT_CONNECTION_TIMEOUT)
    Serial.print("Connection tiemout");
  else if (MQTTErr == MQTT_CONNECTION_LOST)
    Serial.print("Connection lost");
  else if (MQTTErr == MQTT_CONNECT_FAILED)
    Serial.print("Connect failed");
  else if (MQTTErr == MQTT_DISCONNECTED)
    Serial.print("Disconnected");
  else if (MQTTErr == MQTT_CONNECTED)
    Serial.print("Connected");
  else if (MQTTErr == MQTT_CONNECT_BAD_PROTOCOL)
    Serial.print("Connect bad protocol");
  else if (MQTTErr == MQTT_CONNECT_BAD_CLIENT_ID)
    Serial.print("Connect bad Client-ID");
  else if (MQTTErr == MQTT_CONNECT_UNAVAILABLE)
    Serial.print("Connect unavailable");
  else if (MQTTErr == MQTT_CONNECT_BAD_CREDENTIALS)
    Serial.print("Connect bad credentials");
  else if (MQTTErr == MQTT_CONNECT_UNAUTHORIZED)
    Serial.print("Connect unauthorized");
}

void connectToMqtt(bool nonBlocking = false) {
  Serial.print("MQTT connecting ");

  while (!client.connected()) {
    if (client.connect(THINGNAME)) {
      Serial.println("connected!");
    } else {
      Serial.print("failed, reason -> ");
      pubSubErr(client.state());
      if (!nonBlocking) {
        Serial.println(" < try again in 5 seconds");
        delay(5000);
      } else {
        Serial.println(" <");
      }
    }
    
    if (nonBlocking)
      break;
  }
}

void connectToWiFi(String init_str) {
    
    if (init_str != emptyString)
      Serial.print(init_str);
    
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(1000);
    }

    if (init_str != emptyString)
      Serial.println("ok!");
}

void checkWiFiThenMQTT(void) {
    connectToWiFi("Checking WiFi");
    connectToMqtt();
}

typedef struct __packed user_data {
    int i;
    float f;
    bool b;
}user_data_t;

void iotex_devnet_upload_data_example_raw(void) {

	user_data_t user_data;
	unsigned int len = sizeof(user_data);

	user_data.i = 64;
	user_data.f = 128.128;
	user_data.b = true;

  devnet_client.send((void *)&user_data, len, IOTEX_USER_DATA_TYPE_RAW);
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

#ifdef ESP32
    WiFi.setHostname(THINGNAME);
#else
    WiFi.hostname(THINGNAME);
#endif
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    connectToWiFi(String("Attempting to connect to SSID: ") + String(ssid));

    NTPConnect();

    client.setServer(devnet_client.getMQTTConnectAddr(), devnet_client.getMQTTConnectPort());
    client.setCallback(messageReceived);
    client.setBufferSize(384);

    connectToMqtt();

    devnet_client.begin(iotex_time_set_func, iotex_mqtt_pubscription, iotex_mqtt_subscription);
    devnet_client.setDevnetToken(USER_TOKEN, strlen(USER_TOKEN));
    devnet_client.setDevnetMQTTTopic(USER_TOPIC, strlen(USER_TOPIC));

    iotex_import_key();  
}

void loop()
{
    now = time(nullptr);
  
    if (!client.connected()) {
        checkWiFiThenMQTT();

    } else {
        client.loop();
        if (millis() - lastMillis > 5000) {
            lastMillis = millis();
            Serial.println("Raw Data uploading");
            iotex_devnet_upload_data_example_raw();
        }
    }
}








