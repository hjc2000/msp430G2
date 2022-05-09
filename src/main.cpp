#include <Arduino.h>
#include <stdint.h>
#include "MspTar.h"
#include "DallasTemperature.h"
// #include "driverlib.h"  //F5529可以通过包含这个头文件使用TI官方库

OneWire oneWire(P1_4);
DallasTemperature sensors(&oneWire);

void setup()
{
  Serial.begin(115200);
  new MspTar(&Serial);
  sensors.begin();
}

void loop()
{
  static uint32_t t0 = millis();
  if (millis() - t0 > 5000)
  {
    t0 = millis();
    sensors.requestTemperatures();
    float temp = sensors.getTempCByIndex(0);
    pTar->sendData(2, (uint8_t *)&temp, sizeof(temp));
  }
  pTar->loop();
}
