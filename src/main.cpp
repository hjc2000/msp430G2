#include <Arduino.h>
#include <stdint.h>
#include "MspTar.h"
#include "DallasTemperature.h"
OneWire oneWire(P1_4);
DallasTemperature sensors(&oneWire);

void setup()
{
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  new MspTar(&Serial);
  sensors.begin();
}

void loop()
{
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  pTar->sendData(2, (uint8_t *)&temp, sizeof(temp));
  pTar->loop();
  delay(1000);
  digitalWrite(RED_LED, !digitalRead(RED_LED));
}