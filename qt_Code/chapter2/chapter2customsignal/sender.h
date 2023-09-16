#ifndef SENDER_H
#define SENDER_H

#include <QObject>

class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = nullptr);
    void incAge();//显示年龄
private:
    int m_age=10;

signals:
    void agechanged(int value);//发出信号，不用实现函数体，moc会帮助我们实现
};

#endif // SENDER_H
