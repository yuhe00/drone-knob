#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = SSID_NAME;
const char* password = SSID_PASS;

const char* mqtt_host = MQTT_HOST;
const char* mqtt_username = MQTT_USERNAME;
const char* mqtt_password = MQTT_PASSWORD;

WiFiClient espClient;
PubSubClient client(mqtt_host, 1883, espClient);

char msg_buf[255];

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    // Create a random client ID

    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    // Attempt to connect

    Serial.print("Attempting to connect to: ");
    Serial.print(mqtt_host);
    Serial.println("");

    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
}

void loop() {
  int rValue = analogRead(34);
  int gValue = analogRead(35);
  int bValue = analogRead(36);
  Serial.print("Values: ");
  Serial.print(rValue);
  Serial.print(" ");
  Serial.print(gValue);
  Serial.print(" ");
  Serial.print(bValue);
  Serial.print(" ");
  Serial.println("");

  if (!client.connected()) {
    reconnect();
  } else {
    sprintf(msg_buf, "%f", 1.0 - (float)rValue / 4096.0);
    client.publish("drone/knob/r", msg_buf);
    sprintf(msg_buf, "%f", 1.0 - (float)gValue / 4096.0);
    client.publish("drone/knob/g", msg_buf);
    sprintf(msg_buf, "%f", 1.0 - (float)bValue / 4096.0);
    client.publish("drone/knob/b", msg_buf);
  }

  delay(50);
}
