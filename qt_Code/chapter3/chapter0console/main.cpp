#include <QCoreApplication>//非GUI程序
#include<iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout<<"QT Version:"<<qVersion()<<std::endl;
    qDebug()<<"QT Version:"<<qVersion()<<'\n';

    return a.exec();// 这相当于是一个循环
}
