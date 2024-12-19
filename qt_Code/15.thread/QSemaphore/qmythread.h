#ifndef QMYTHREAD_H
#define QMYTHREAD_H

#include <QThread>

//采集数据
class QThreadDAQ : public QThread
{
    Q_OBJECT
private:
    bool m_stop = false; //停止线程
protected:
    void run() Q_DECL_OVERRIDE;
public:
    QThreadDAQ() {};
    void stopThread();
};
//读取数据
class QThreadShow : public QThread
{
    Q_OBJECT
private:
    bool m_stop = false; //停止线程
protected:
    void run() Q_DECL_OVERRIDE;
public:
    QThreadShow() {};
    void stopThread();
signals:
    //用于一次传递一个缓存区的数据
    void newValue(int *data, int count, int seq);
};

#endif // QMYTHREAD_H
