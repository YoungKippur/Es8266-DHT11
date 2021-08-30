#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>

// Cambiar por personales
#define FIREBASE_HOST "https://pythondht11-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "NYGDlmwb8s0Ut8orOqTt9nkVyYxjQOTUyPXDmJFQ"
#define WIFI_SSID "CABLEVISION-eec1"
#define WIFI_PASSWORD "1805BMISBQHA"

#define DHTPIN 12
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float temp;

void setup(){
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("_");
  Serial.print("Connected");
  Serial.println("IP Address: ");
  Serial.print(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  temp = dht.readTemperature();

  if (isnan(temp)) { // Para ver si esta funcionando (ta bueno)
    Serial.println(("Failed to read from DHT sensor!"));
    return;
  }

  Serial.println("Temperature: ");
  Serial.print(temp);
  Serial.println("°C ");
  String fireTemp = String(temp) + String("°C");
  delay(5000); // Cambiar a millis!!

  Firebase.pushString("/DHT11/Temperature", fireTemp);//setup path to send Temperature readings
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
}
