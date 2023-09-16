#include "mainwindow.h"

#include <QtGui>
#include<QWindow>
int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);//未GUI应用程序提供主时间循环

    QWindow w;
    w.show();
    a.dumpObjectTree();
    qGuiApp->dumpObjectInfo();//qGuiApp应用程序对象的全局指针，只有当应用程序对象是QGuiApplication的时候才有效
    return a.exec();
}
