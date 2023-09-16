#include <QCoreApplication>
#include"sender.h"
//#include"receiver.h"

int main(int argc, char *argv[])
{

    Sender sendObj;//创建信号发出者对象
    sendObj.incAge();//年龄++并且发出信号

//    Receiver receiverObj;//创建接受者对象
//    QObject::connect(&sendObj,&Sender::agechanged,&receiverObj,&Receiver::ageChange);
//    sendObj.incAge();//12
//    sendObj.incAge();//13

}
