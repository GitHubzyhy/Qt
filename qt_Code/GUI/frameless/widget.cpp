#include "widget.h"
#include "./ui_widget.h"
#include<QMouseEvent>

QPoint winPos;//鼠标相对于窗口左上角坐标
Widget::Widget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint); // 设置窗口无边框，设置后窗口无法移动
    setAttribute(Qt::WA_TranslucentBackground, true);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btn_exit_clicked()
{
    qApp->quit();//退出整个程序
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    QPoint mousePos=event->globalPosition().toPoint();//鼠标相对于屏幕的坐标，全局坐标的点对象-》转换为 QPoint 类型的对象
    QPoint topleft=this->geometry().topLeft();//窗口左上角相对于屏幕的坐标，获取对象的几何信息-》返回一个表示左上角位置的点对象。
    winPos=mousePos-topleft;//按下的时候就算出来
}


void Widget::mouseMoveEvent(QMouseEvent *event)
{
    //event 是一个指针，指向事件对象。在这种情况下，它可能指的是鼠标事件对象。
    QPoint mousePos=event->globalPosition().toPoint();//鼠标相对于屏幕的坐标，全局坐标的点对象-》转换为 QPoint 类型的对象
    QPoint endPos=mousePos-winPos;//窗口相对于桌面的坐标
    this->move(endPos);//设置窗口相对于桌面的坐标（x），实现窗口移动
}

