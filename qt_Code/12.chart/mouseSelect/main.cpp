#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("鼠标选择缩放与数值显示");
    w.setWindowIcon(QIcon(":/images/mouse.png"));

    w.show();
    return a.exec();
}
