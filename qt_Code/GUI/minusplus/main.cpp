#include "minusplus.h"

#include <QApplication>
#include<QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MinusPlus w;

    w.resize(300,190);//设置窗口的大小
    w.setWindowTitle("Plus minus");
//    w.setWindowIcon(QIcon(""));
    w.show();
    return a.exec();
}
