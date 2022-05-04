#include <Arduino.h>
#include <stdint.h>
#include "MspTar.h"

void setup()
{
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  new MspTar(&Serial);
}

void loop()
{
  float temp = 20;
  pTar->sendData(2, (uint8_t *)&temp, sizeof(temp));
  pTar->loop();
  delay(1000);
  digitalWrite(RED_LED, !digitalRead(RED_LED));
}