#include "widget.h"
#include<QtWidgets>

using std::cos;//避免后续使用要加上std::
using std::sin;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setPalette(QPalette(Qt::white));//设置窗口背景色 使用 QPalette 类来设置窗口的颜色方案
    setAutoFillBackground(true);//窗口的自动背景填充设置为启用
    resize(600, 300);
}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);//抗锯齿
    painter.setRenderHint(QPainter::TextAntialiasing);//将渲染效果设置为文本抗锯齿

    //生成五角星五个顶点的坐标
    qreal R = 100; //半径
    const qreal Pi = 3.1415926;
    qreal deg = Pi * 72 / 180;
    QPoint points[5] =
    {
        QPoint(R, 0),
        QPoint(R * cos(deg), -R * sin(deg)),
        QPoint(R * cos(2 * deg), -R * sin(2 * deg)),
        QPoint(R * cos(3 * deg), -R * sin(3 * deg)),
        QPoint(R * cos(4 * deg), -R * sin(4 * deg)),
    };

    //设置字体
    QFont font;
    font.setPointSize(12);//设置字号为12
    font.setBold(true);

    //设置画笔
    QPen penLine;
    penLine.setWidth(2);// 设置笔的宽度，像素为单位
    penLine.setColor(Qt::blue);//画线颜色
    penLine.setStyle(Qt::SolidLine);//线条的类型
    penLine.setCapStyle(Qt::FlatCap);//线条 端点 的样式
    penLine.setJoinStyle(Qt::BevelJoin);//线条 连接点 样式

    //设置画刷
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);//画刷填充样式

    //设置到画家中去
    painter.setFont(font), painter.setPen(penLine), painter.setBrush(brush);

    //设计绘制五角星的PainterPath，以便于重复使用
    QPainterPath starPath;
    starPath.moveTo(points[0]);//设置路径的当前点

    starPath.lineTo(points[2]);//这将在路径的当前点与 points[2] 之间绘制一条直线。
    starPath.lineTo(points[4]);//起点已经变成了points[2]
    starPath.lineTo(points[1]);
    starPath.lineTo(points[3]);

    starPath.closeSubpath();//闭合路径，最后一个点与第一个点相连
    //在 starPath 路径中的 points[0] 位置绘制字符 "0"，并将该字符添加到路径中。
    starPath.addText(points[0], font, "0");
    starPath.addText(points[1], font, "1");
    starPath.addText(points[2], font, "2");
    starPath.addText(points[3], font, "3");
    starPath.addText(points[4], font, "4");

    //绘图
    painter.save();//保存坐标状态

    painter.translate(100, 120); //平移
    painter.drawPath(starPath);//画星星
    painter.drawText(0, 0, "S1");//星星中心文字

    painter.restore();//恢复坐标状态

    painter.translate(300, 120);
    painter.scale(0.8, 0.8); //缩放
    painter.rotate(90);//顺时针旋转90度
    painter.drawPath(starPath);//画星星
    painter.drawText(0, 0, "S2");//星星中心文字

    painter.resetTransform();//复位所有坐标变换 又回到了原始坐标
    painter.translate(500, 120);
    painter.rotate(-145);//逆时针旋转145度
    painter.drawPath(starPath);//画星星
    painter.drawText(0, 0, "S3");//星星中心文字
}
