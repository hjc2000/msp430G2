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
    case 2: //给定值
    {
        if (data.pop())
        {
            //设置给定值
        }
        else
        {
            //读取给定值
        }
        break;
    }
    case 3: // PID参数
    {
        if (data.pop())
        {
            //写PID参数
            /*PID参数为3个double类型的值，从队列中取出3个double*/
        }
        else
        {
            //读PID参数
        }
        break;
    }
    }
}
