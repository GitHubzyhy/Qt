#include "sender.h"

Sender::Sender(QObject *parent)
    : QObject{parent}
{

}

void Sender::incAge()
{
    m_age++;
    emit agechanged(m_age);//发出信号
}
