#include "widget.h"
#include<QFile>
#include <QApplication>

void demo1(widget &w)
{
    w.resize(250,150);
    w.setWindowTitle("一个简单的例子");
    w.setToolTip("这是一个QWidget");
    w.setWindowIcon(QIcon("C://Users//ZYH//Desktop//图片//图标//bilibili.ico"));//设置桌面图标
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    widget w;

    demo1(w);

    QFile stylefile("myStyle.css");
    stylefile.open(QIODevice::ReadOnly);//已只读方式打开
    QString stylesheet=QString::fromLatin1(stylefile.readAll());//readAll是从文件读取数据返回一个字节数组
    a.setStyleSheet(stylesheet);//设置样式表

    w.show();
    return a.exec();
}
