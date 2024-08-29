#include "widget.h"
#include<QtWidgets>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int W = width();
    int H = height();
    int sid = qMin(W, H);
    QRect rect((W - sid) / 2, (H - sid) / 2, sid, sid); //viewport矩形区
    painter.drawRect(rect);
    painter.setViewport(rect);//设置viewport 只在rect这个区域进行绘图操作
    //窗口与视图是同一个矩形，窗口定义逻辑坐标的范围
    painter.setWindow(-100, -100, 200, 200); //设置窗口大小，逻辑坐标 窗口坐标轴在中心(0,0)
    painter.setRenderHint(QPainter::Antialiasing);//设置渲染效果为抗锯齿

    //设置画笔
    QPen pen;
    pen.setWidth(1);//设置线宽度
    pen.setColor(Qt::red);//线的颜色
    pen.setStyle(Qt::SolidLine);//线的类型

    //线性渐变
    QLinearGradient linearGrad(0, 0, 100, 0); //从左到右
    linearGrad.setColorAt(0, Qt::yellow); //起点颜色
    linearGrad.setColorAt(1, Qt::green); //终点颜色
    linearGrad.setSpread(QGradient::PadSpread);
    painter.setBrush(linearGrad);

    //复合模式 用于控制图形绘制操作如何与现有图像进行组合的一种方式
    //painter.setCompositionMode(QPainter::RasterOp_NotSourceXorDestination);
    painter.setCompositionMode(QPainter::CompositionMode_Difference);
    for (int i = 0; i < 36; ++i)
    {
        painter.drawEllipse(QPoint(50, 0), 50, 50); //在(50,0)的中心位置定义水平半径50，垂直半径50
        painter.rotate(10);//旋转10°
    }
}
