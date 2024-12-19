#include "renderarea.h"
#include <QPainter>
#include <QPaintEvent>

RenderArea::RenderArea(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(232, 232);

    QFont newfont = font(); //获取当前控件的默认字体
    newfont.setPixelSize(12);//字体大小设置为12像素
    setFont(newfont);//应用于当前控件

    QFontMetrics fontMetrics(newfont);//个用于处理字体度量的工具类，它提供了用于计算字体的各种度量信息的函数
    xBoundingRect = fontMetrics.boundingRect("x"); //计算x的外边矩形
    yBoundingRect = fontMetrics.boundingRect("y"); //计算y的外边矩形
}

RenderArea::~RenderArea() {}
//设置操作
void RenderArea::setOperations(const QList<Operation> &operations)
{
    this->operations = operations;
    update();//重新绘制 paintEvent
}
//设置操作的形状
void RenderArea::setShape(const QPainterPath &shape)
{
    this->shape = shape;
    update();//重新绘制 paintEvent
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);//设置抗锯齿
    painter.fillRect(event->rect(), QBrush(Qt::white)); //把整个小窗口都画成白色

    painter.translate((232 - 100) / 2, (232 - 100) / 2); //正方形为100*100 将绘画点平移到中间

    painter.save();

    transformPainter(painter);//改变
    drawShape(painter);//画形状
    drawCoordinates(painter);//画x轴，y轴

    painter.restore();

    drawOutLine(painter);//画方格子
}
//画坐标
void RenderArea::drawCoordinates(QPainter &painter)
{
    painter.setPen(QPen(Qt::red, 3)); //第二个参数是笔的粗细
    //画一条横线
    painter.drawLine(0, 0, 50, 0);
    //画箭头
    painter.drawLine(48, -2, 50, 0);
    painter.drawLine(48, 2, 50, 0);
    //画x
    painter.drawText(60 - xBoundingRect.width() / 2,
                     0 + xBoundingRect.height() / 2, "x");
    //画y轴
    painter.drawLine(0, 0, 0, 50);

    painter.drawLine(-2, 48, 0, 50);
    painter.drawLine(2, 48, 0, 50);

    painter.drawText(0 - yBoundingRect.width() / 2,
                     60 + yBoundingRect.height() / 2, "y");
}
//画方格子
void RenderArea::drawOutLine(QPainter &painter)
{
    painter.setPen(Qt::darkGreen);//将画笔设置为深绿色
    painter.setPen(Qt::DashLine);//将画笔设置为虚线样式
    painter.setBrush(Qt::NoBrush);//不需要填充
    painter.drawRect(0, 0, 100, 100); //以0，0点画宽高的矩形
}
//画形状
void RenderArea::drawShape(QPainter &painter)
{
    painter.fillPath(shape, Qt::blue); //使用给定的画笔填充给定的路径
}
//坐标改变
void RenderArea::transformPainter(QPainter &painter)
{
    for (int i = 0; i < operations.size(); ++i)
    {
        //是叠加的效果
        switch (operations[i])
        {
            case Translate://平移
                painter.translate(50, 50);
                break;
            case Scale://缩放
                painter.scale(0.75, 0.75);
                break;
            case Rotate://旋转
                painter.rotate(60);
                break;
            case NoTransformation://无变化
                break;
        }
    }
}
