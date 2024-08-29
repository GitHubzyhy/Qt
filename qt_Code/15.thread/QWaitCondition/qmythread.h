#ifndef QMYTHREAD_H
#define QMYTHREAD_H

#include <QThread>

//生产者 产生点数
class QThreadProducer: public QThread
{
    Q_OBJECT
private:
    bool m_stop = false; //停止线程
protected:
    void run() override;

public:
    QThreadProducer();
    void stopThread();//让线程停止
};

//消费者 读取数据并送给主线程进行显示
class QThreadConsumer: public QThread
{
    Q_OBJECT
private:
    bool m_stop = false; //停止线程
protected:
    void run() override;

public:
    QThreadConsumer();
    void stopThread();
signals:
    void newValue(int seq, int diceValue);
};

#endif // QMYTHREAD_H
