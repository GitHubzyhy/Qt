#include "qdicethread.h"
#include <QTime>

QDiceThread::QDiceThread() {}
//开始掷骰子
void QDiceThread::diceBegin()
{
    m_Paused = false;
}
//暂停掷骰子
void QDiceThread::dicePause()
{
    m_Paused = true;
}
//停止线程
void QDiceThread::stopThread()
{
    m_stop = true;
}
//线程任务
void QDiceThread::run()
{
    m_stop = false; //启动线程时令m_stop=false
    m_seq = 0; //掷骰子次数
    srand(QTime::currentTime().msec());//随机数初始化，srand是线程安全的

    while (!m_stop) //线程未终结
    {
        if (!m_Paused) //允许掷骰子
        {
            m_diceValue = rand(); //获取随机数
            m_diceValue = (m_diceValue % 6) + 1;
            m_seq++;

            emit newValue(m_seq, m_diceValue);
        }
        msleep(500); //线程休眠500ms
    }
    // 在  m_stop==true时结束线程任务
    quit();//相当于  exit(0),退出线程的事件循环
}
