#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    RasterWidget w;
    w.show();
    return a.exec();
}
