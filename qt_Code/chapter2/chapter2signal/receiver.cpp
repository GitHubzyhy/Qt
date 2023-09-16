#include "receiver.h"
#include<QDebug>
Receiver::Receiver(QObject *parent)
    : QObject{parent}
{

}

void Receiver::ageChanged(int age)
{
    qDebug()<<"age: "<<age;
}
