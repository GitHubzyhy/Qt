#include "breakoutwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BreakOutWidget w;
    w.show();
    return a.exec();
}
