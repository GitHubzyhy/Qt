#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/images/icon.png"));
    w.setWindowTitle("kinds of charts");
    w.show();
    return a.exec();//进入主事件循环
}
