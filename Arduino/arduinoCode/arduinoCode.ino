#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT.h>

// Cambiar por personales
#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "CABLEVISION-eec1"
#define WIFI_PASSWORD "1805BMISBQHA"

#define DHTPIN 12
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

FirebaseData firebaseData;

float temp, valorAnterior;

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("_");
  Serial.println("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (millis() - valorAnterior >= 5000) {
    valorAnterior = millis();
    
    temp = dht.readTemperature();
    if (isnan(temp)) { // Para ver si esta funcionando (ta bueno)
      Serial.println(("Failed to read from DHT sensor!"));
      return;
    }
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println("°C ");
    //String fireTemp = String(temp) + String("°C");

    Firebase.setFloat(firebaseData, "Temperatura", temp);
  }
}
