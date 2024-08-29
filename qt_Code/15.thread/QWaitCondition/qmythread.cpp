#include "qmythread.h"
#include <QMutex>//互斥量
#include <QWaitCondition>
#include <QTime>
#include <QMutexLocker>

QMutex mutex;
QWaitCondition newdataAvailable;
int seq = 0; //序号
int diceValue;//点数

//生产者的线程任务
void QThreadProducer::run()
{
    m_stop = false; //启动线程时令m_stop=false
    seq = 0;
    srand(QTime::currentTime().msec());//通过当前时间的毫秒生成随机数

    while (!m_stop)
    {
        //用互斥量将其保护起来这部分代码的执行就不会被其他线程中断
        mutex.lock();//锁定

        diceValue = rand(); //获取随机数
        diceValue = (diceValue % 6) + 1;
        seq++;

        mutex.unlock();//解锁

        newdataAvailable.wakeAll();//唤醒所有线程，有新数据了
        msleep(500);//线程休眠500ms
    }
}

QThreadProducer::QThreadProducer()
{

}

void QThreadProducer::stopThread()
{
    QMutexLocker locker(&mutex);
    m_stop = true;
}
//消费者的线程任务
void QThreadConsumer::run()
{
    m_stop = false; //启动线程时令m_stop=false
    while (!m_stop) //循环主体
    {
        mutex.lock();
        //会先解锁mutex，使其他线程可以使用mutex.进入等待状态
        newdataAvailable.wait(&mutex);
        emit newValue(seq, diceValue);//发射信号给主线程
        mutex.unlock();
    }
}

QThreadConsumer::QThreadConsumer()
{

}

void QThreadConsumer::stopThread()
{
    QMutexLocker locker(&mutex);
    m_stop = true;
}
