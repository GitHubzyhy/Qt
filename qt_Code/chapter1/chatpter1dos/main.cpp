#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug()<<"对象a的类名称："<<a.metaObject()->className();
    qDebug()<<"应用程序目录: "<<a.applicationFilePath();
    a.dumpObjectTree();
    a.dumpObjectInfo();

    return a.exec();//进入主循环
}
