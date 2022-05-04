#include <Arduino.h>
#include <stdint.h>
#include "MspTar.h"
#include "DallasTemperature.h"

OneWire oneWire(P2_0);
DallasTemperature sensors(&oneWire);

void setup()
{
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  new MspTar(&Serial);
  sensors.begin();
}
uint8_t buff[] = {1, 255, 255};

void loop()
{
  sensors.requestTemperatures();
  double temp = sensors.getTempCByIndex(0);
  pTar->loop();
  pTar->sendData(buff, 3);
  delay(1000);
  digitalWrite(RED_LED, !digitalRead(RED_LED));
}