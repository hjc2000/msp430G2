#include <UartTar.h>

UartTar::UartTar(HardwareSerial *pSerial) : m_pSerial(pSerial)
{
    m_flag = 0;
    m_oldData = 0;
    m_newData = 0;
    m_receiveCount = 0;
}

void UartTar::DetectFrameHeader(void)
{
    if ((m_newData == 85) && (m_oldData == 85))
    {
        m_flag = 1;
    }
}

void UartTar::GetFrameLength(void)
{
    m_receiveCount = m_newData;
    //如果数据长度是85，会导致帧重启，所以使用0代替85，数据长度不可能
    //真的是0，因为至少会有1字节的功能码，即使后面不跟数据
    if (m_receiveCount == 0)
    {
        m_receiveCount = 85;
    }
}

bool UartTar::IsInsertedZero(void)
{
    if (m_newData == 0 && m_oldData == 85)
    {
        return true;
    }
    return false;
}

void UartTar::GetData(void)
{
    if (!IsInsertedZero())
    {
        //如果这个数据不是被插入的用来转义的0
        m_readBuff.push(m_newData);
        m_receiveCount--;
        if (m_receiveCount == 0)
        {
            /*已经收集到一个帧了*/
            OnReceive(m_readBuff);
            m_flag = 0; //回到等待帧头的状态
        }
    }
}

void UartTar::AnalysisReadList(uint8_t data)
{
    m_newData = data;
    DetectFrameHeader();
    switch (m_flag)
    {
    case 0: //等待帧头的到来
    {
        break;
    }
    case 1: //已经接收到帧头，此时应该重启帧
    {
        m_readBuff.clear();
        m_flag++;
        break;
    }
    case 2: //接收帧长度
    {
        GetFrameLength();
        m_flag++;
        break;
    }
    case 3: //接收数据
    {
        GetData();
        break;
    }
    }
    m_oldData = m_newData;
}

void UartTar::PushFrameHeader(uint16_t count)
{
    m_pSerial->write(85);
    m_pSerial->write(85);
    if (count == 85)
    {
        m_pSerial->write((uint8_t)0);
    }
    else
    {
        m_pSerial->write(count);
    }
}

void UartTar::PushData(uint8_t data)
{
    /*如果数据域中出现85*/
    if (data == 85)
    {
        m_pSerial->write(85);
        m_pSerial->write((uint8_t)0);
    }
    else
    {
        m_pSerial->write(data);
    }
}

void UartTar::sendData(const uint8_t *buff, uint16_t size)
{
    PushFrameHeader(size);
    for (size_t i = 0; i < size; i++)
    {
        PushData(buff[i]);
    }
}

void UartTar::loop(void)
{
    while (m_pSerial->available())
    {
        AnalysisReadList(m_pSerial->read());
    }
}
