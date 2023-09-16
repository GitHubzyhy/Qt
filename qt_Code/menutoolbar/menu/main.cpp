#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(400,500);
    w.setWindowTitle("这是一个demov");
    w.show();
    return a.exec();
}
