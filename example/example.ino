#include <DHT.h>
#include <DHT_U.h>

extern volatile unsigned long timer0_millis;
unsigned long cero_value = 0;

#define DHT_PIN 4

DHT dht(DHT_PIN, DHT11);

float temp, hume;

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  if (millis() >= 5000) {
    hume = dht.readHumidity();
    temp = dht.readTemperature();
    Serial.println(String(temp) + " " + String(millis()));
    
    setMillis(cero_value);
  }
}

void setMillis(unsigned long new_millis) {
  uint8_t oldSREG = SREG;
  cli();
  timer0_millis = new_millis;
  SREG = oldSREG;
}
