#include <QCoreApplication>
#include <QDebug>
#include <QVariant>
#include <QMetaClassInfo>
#include "myclass.h"
#include<QThread>
#include"thread.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSharedPointer<MyClass> myinstance =QSharedPointer<MyClass>( new MyClass);
    QObject *object = myinstance.get();

    myinstance->setPriority(MyClass::VeryLow);
    object->setProperty("priority", "VeryHigh"); object->setProperty("isGood",false);

    qInfo()<<myinstance->priority();
    qInfo()<<object->property("isGood");//用属性系统调用

    qInfo()<<myinstance->metaObject()->classInfo(0).name();
    qInfo()<<myinstance->metaObject()->classInfo(0).value();
    qInfo()<<myinstance->metaObject()->classInfo(1).name();
    qInfo()<<myinstance->metaObject()->classInfo(1).value();

    Thread mythread;
    mythread.start();
    QObject::connect(&mythread,&Thread::finished,&a,&QCoreApplication::quit);

    return a.exec();
}
