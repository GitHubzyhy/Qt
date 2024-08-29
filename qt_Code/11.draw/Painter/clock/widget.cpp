#include "widget.h"
#include<QtWidgets>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QTimer *timer = new QTimer(this);
    //QOverload<>::of 指定的哪个重载函数的版本
    connect(timer, &QTimer::timeout, //该信号会在定时器超时时发出。
            this, QOverload<>::of(&Widget::update)); //这种方式用于在定时器超时时执行更新界面或执行其他需要定期操作的任务。
    timer->start(1000);//启动或重新启动定时器，超时时间间隔为1000毫秒。
    resize(300, 300);
}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent *event)
{
    //三个点绘制
    static const QPoint hourHand[3] = { QPoint(7, 8), QPoint(-7, 8), QPoint(0, -40) };
    static const QPoint minuteHand[3] = { QPoint(7, 8), QPoint(-7, 8), QPoint(0, -70) };
    static const QPoint secondes[3] = { QPoint(2, 8), QPoint(-2, 8), QPoint(0, -100) };
    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);
    QColor secondColor(127, 0, 255, 160);

    QTime time = QTime::currentTime();
    QPainter painter(this);//在此绘图设备上绘图

    painter.setRenderHint(QPainter::Antialiasing);//抗锯齿，让画的线更平缓
    painter.translate(width() / 2, height() / 2); //位移改变逻辑坐标

    int side = qMin(width(), height());//找到最小的值
    painter.scale(side / 300.0, side / 300.0);//按照一定的比例进行缩放
    painter.setPen(Qt::NoPen);

    //时针绘制
    painter.save();//保存下此时的旋转状态
    painter.setBrush(hourColor);//刷下颜色
    painter.rotate((360 / 12) * (time.hour() + time.minute() / 60.0)); //顺时针旋转坐标系
    painter.drawPolygon(hourHand, 3); //拿出三个点
    painter.restore();//撤回旋转之前的状态

    //分针绘制
    painter.save();//保存下此时的旋转状态
    painter.setBrush(minuteColor);//刷下颜色
    painter.rotate((360 / 60) * (time.minute() + time.second() / 60.0));
    painter.drawPolygon(minuteHand, 3); //拿出三个点
    painter.restore();//撤回旋转之前的状态

    //秒针绘制
    painter.save();//保存下此时的旋转状态
    painter.setBrush(secondColor);//刷下颜色
    painter.rotate((360 / 60)*time.second());
    painter.drawPolygon(secondes, 3); //拿出三个点
    painter.restore();//撤回旋转之前的状态

    //表盘的绘制
    for (int i = 0; i < 60; ++i)
    {
        if (i % 5 == 0) //画时针
        {
            painter.setPen(hourColor);
            painter.drawLine(90, 0, 98, 0);
        }
        else
        {
            painter.setPen(minuteColor);
            painter.drawLine(92, 0, 96, 0);
        }

        painter.rotate(360 / 60);
    }
}
