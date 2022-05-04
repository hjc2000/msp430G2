#include "MspTar.h"

MspTar *pTar = 0;

MspTar::MspTar(HardwareSerial *pSerial) : UartTar(pSerial)
{
    pTar = this;
}

void MspTar::OnReceive(Queue<uint8_t> &data)
{
    switch (data.pop())
    {
    case 0:
    {
        break;
    }
    case 1: // LED开关
    {
        if (data.pop())
        {
            //红色LED
            if (data.pop())
            {
                //开
            }
            else
            {
                //关
            }
        }
        else
        {
            //绿色LED
            if (data.pop())
            {
                //开
            }
            else
            {
                //关
            }
        }
        break;
    }
    }
}
