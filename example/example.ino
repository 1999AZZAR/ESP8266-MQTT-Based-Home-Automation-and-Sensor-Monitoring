#include "config.h"

// Function prototypes
void MQTT_connect();
void setupWiFi();
void readAndPublishSensorData();

void setup() {
  Serial.begin(115200);

  // Initialize WiFi
  setupWiFi();

  // Subscribe to MQTT topics
  mqtt.subscribe(&Light1);
  mqtt.subscribe(&Light2);
}

void loop() {
  MQTT_connect();

  // Process MQTT subscriptions
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(500))) {
    if (subscription == &Light1 || subscription == &Light2) {
      int relayNumber = (subscription == &Light1) ? 1 : 2;
      Serial.print(F("Got r") + String(relayNumber) + F(" : "));
      Serial.println((char *)subscription->lastread);
      int relayState = atoi((char *)subscription->lastread);
      digitalWrite((relayNumber == 1) ? Relay1 : Relay2, relayState);
    }
  }

  // Read and publish sensor data
  readAndPublishSensorData();
  delay(3500);
}

void readAndPublishSensorData() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C "));

  // Publish sensor data
  if (!temp.publish(temperature)) {
    Serial.println(F("Failed to publish temperature"));
  } else {
    Serial.println(F("Temperature published successfully"));
  }

  if (!humi.publish(humidity)) {
    Serial.println(F("Failed to publish humidity"));
  } else {
    Serial.println(F("Humidity published successfully"));
  }
}

void setupWiFi() {
  // Adding the WiFi networks to the MultiWiFi instance
  wifi_multi.addAP(ssid1, password1);
  wifi_multi.addAP(ssid2, password2);
  wifi_multi.addAP(ssid3, password3);

  // Wait for ESP8266 to scan the local area and connect with the strongest of the networks defined above
  Serial.print("Connecting to Wi-Fi...");
  while (wifi_multi.run(connectTimeOutPerAP) != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void MQTT_connect() {
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;

  while (!mqtt.connect()) {
    Serial.println(mqtt.connectErrorString(mqtt.connect()));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);

    if (--retries == 0) {
      while (1);
    }
  }

  Serial.println("MQTT Connected!");
}
