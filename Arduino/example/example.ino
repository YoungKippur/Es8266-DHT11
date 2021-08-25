#include <ESP8266WiFi.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHT_PIN 12

DHT dht(DHT_PIN, DHT11);

float temp, hume;
float valorAnterior;

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  if (millis() - valorAnterior >= 5000) {
    valorAnterior = millis();
    hume = dht.readHumidity();
    temp = dht.readTemperature();
    Serial.println(String(temp) + " " + String(millis()));
  }
}
