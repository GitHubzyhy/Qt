#include "widget.h"

#include <QApplication>
#include <QSystemTrayIcon>//系统菜单托盘
#include <QIcon>
#include <QMenu>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    QSystemTrayIcon sysTray(QIcon(":/img/icon.png"), &w);

    QMenu menu;
    auto showAct = new QAction("show", &sysTray);
    auto exitAct = new QAction("exit", &sysTray);

    QObject::connect(showAct, &QAction::triggered, [&]()
    {
        w.setVisible(true);
    });
    QObject::connect(exitAct, &QAction::triggered, [&]()
    {
        QApplication::quit();
    });

    menu.addAction(showAct);
    menu.addAction(exitAct);

    sysTray.setContextMenu(&menu);//设置上下文菜单

    sysTray.show();

    w.show();
    return a.exec();
}
