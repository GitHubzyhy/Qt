#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = nullptr);

public slots:
    void ageChange(int age);//槽函数必须具有函数体

};

#endif // RECEIVER_H
