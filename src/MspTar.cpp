#include "MspTar.h"

MspTar *pTar = 0;

MspTar::MspTar(HardwareSerial *pSerial) : UartTar(pSerial)
{
    pTar = this;
}
