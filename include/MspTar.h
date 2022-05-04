#pragma once
#include "UartTar.h"

class MspTar : public UartTar
{
public:
    MspTar(HardwareSerial *pSerial);
    void OnReceive(Queue<uint8_t> &data)
    {
    }
};
extern MspTar *pTar;