#include "receiver.h"
#include<QDebug>
Receiver::Receiver(QObject *parent)
    : QObject{parent}
{

}

void Receiver::ageChange(int age)
{
    qDebug()<<"age: "<<age;

}
