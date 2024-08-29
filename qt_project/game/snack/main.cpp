#include "snackwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SnackWidget w;
    w.show();
    return a.exec();
}
