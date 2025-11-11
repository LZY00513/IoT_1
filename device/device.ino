// device.ino
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";
const char* MQTT_SERVER = "broker.hivemq.com"; 
const int MQTT_PORT = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

const char* SET_TOPIC = "home/light/set";
const char* STATUS_TOPIC = "home/light/status";

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  String msg = String((char*)payload);
  Serial.print("MQTT message arrived: ");
  Serial.print(topic);
  Serial.print(" -> ");
  Serial.println(msg);

  if (String(topic) == SET_TOPIC) {
    if (msg == "on") {
      digitalWrite(LED_BUILTIN, LOW); // builtin LED is often inverted
      client.publish(STATUS_TOPIC, "on");
      Serial.println("LED turned ON");
    } else if (msg == "off") {
      digitalWrite(LED_BUILTIN, HIGH);
      client.publish(STATUS_TOPIC, "off");
      Serial.println("LED turned OFF");
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(ESP.getChipId());
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe(SET_TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // off initially

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
}

unsigned long lastStatus = 0;
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Report the status every 10 seconds
  if (millis() - lastStatus > 10000) {
    lastStatus = millis();
    if (digitalRead(LED_BUILTIN) == LOW) {
      client.publish(STATUS_TOPIC, "on");
    } else {
      client.publish(STATUS_TOPIC, "off");
    }
  }
}
