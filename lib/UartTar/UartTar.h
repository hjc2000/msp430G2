#ifndef UartTar_h
#define UartTar_h

#include <stdint.h>
#include "Queue.h"
using namespace std;

class UartTar
{
public:
    UartTar(HardwareSerial *pSerial);
    //向串口发送数据
    void sendData(uint16_t funCode, const uint8_t *data, uint16_t size);
    void loop(void);

protected:
    /**
     * @brief 接收到一帧的数据后被调用
     *
     * @param data
     */
    virtual void OnReceive(Queue<uint8_t> &data) = 0;

private:
    void AnalysisReadList(uint8_t data);

    //读缓冲区，分析完的数据放到这里
    Queue<uint8_t> m_readBuff;

    uint8_t m_flag; //用来标志工作阶段
    uint8_t m_oldData;
    uint8_t m_newData;
    uint8_t m_receiveCount; //对接收到的数据域字节数计数（减计数，在收到长度时赋值）

    /// <summary>
    /// 检测帧头，通过控制m_flag来控制解包程序的走向
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    void DetectFrameHeader(void);

    /// <summary>
    /// 获取帧的长度
    /// </summary>
    /// <param name=""></param>
    void GetFrameLength(void);

    /// <summary>
    /// 当前收到的数据是不是用来转义的被插入的0
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsInsertedZero(void);

    /// <summary>
    /// 正式接收数据
    /// </summary>
    /// <param name=""></param>
    void GetData(void);

private:
    void PushFrameHeader(uint16_t count); //将发送数据的长度放入发送缓冲区
    void PushData(uint8_t data);          //将数据放入发送缓冲区
    HardwareSerial *m_pSerial;
};

#endif // UartTar_h
