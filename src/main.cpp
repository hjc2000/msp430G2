#include <Arduino.h>
#include <stdint.h>
#include "MspTar.h"

void setup()
{
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  new MspTar(&Serial);
}
uint8_t buff[] = {1, 255, 255};

void loop()
{
  pTar->loop();
  pTar->sendData(buff, 3);
  delay(1000);
  digitalWrite(RED_LED, !digitalRead(RED_LED));
}