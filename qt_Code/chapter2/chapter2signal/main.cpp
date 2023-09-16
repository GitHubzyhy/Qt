#include <QCoreApplication>
#include"sender.h"
#include"receiver.h"
int main(int argc, char *argv[])
{
    Sender senderObj;//发出信号的对象
    Receiver receiverObj;//接受信号的对象

    senderObj.incAge();//11 并且发出了信号
    QObject::connect(&senderObj,&Sender::agechanged,&receiverObj,&Receiver::ageChanged);//建立连接

    senderObj.incAge();//12 并且发出了信号
    senderObj.incAge();//13 并且发出了信号
    QObject::disconnect(&senderObj,&Sender::agechanged,&receiverObj,&Receiver::ageChanged);//断开连接
    senderObj.incAge();//不会显示，因为已经断开了连接

}
