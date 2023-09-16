#include <QApplication>//为QT widget模块的应用程序提供事件循环
#include<QWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;
    w.show();

    qApp->dumpObjectInfo();
    qApp->dumpObjectTree();

    return a.exec();
}
