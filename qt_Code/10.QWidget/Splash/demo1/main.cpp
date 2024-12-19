#include "mainwindow.h"

#include <QApplication>
#include "qdlglogin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDlgLogin *dlgLogin = new QDlgLogin;

    if(dlgLogin->exec() == QDialog::Accepted)//模态对话框显示
    {
        MainWindow w;
        w.show();
        return a.exec();
    }

    return 0;
}
