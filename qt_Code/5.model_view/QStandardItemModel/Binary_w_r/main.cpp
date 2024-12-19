#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowIcon(QIcon(":/images/icon.png"));
    w.setWindowTitle("标准数据项");
    w.show();

    return a.exec();
}
