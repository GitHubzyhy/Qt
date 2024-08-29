#include "renderarea.h"
#include "ui_renderarea.h"
#include <QPainterPath>
#include <QPainter>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderArea)
{
    ui->setupUi(this);

    //初始化
    shap = Polygon;
    antialiased = false;
    transformed = false;
    pixmap.load(":/images/man.jpg");

    setBackgroundRole(QPalette::Base);//使用调色板的基本颜色作为其背景颜色，
    setAutoFillBackground(true);//部件将自动用由背景角色指定的颜色填充其背景，这将在部件需要重新绘制或更新时自动发生。
}

RenderArea::~RenderArea()
{
    delete ui;
}
//形状
void RenderArea::setShap(Shape newShap)
{
    shap = newShap;
    update();
    /*  用于请求重新绘制部件Qt 会在下一个事件循环中处理这个请求，
        执行部件的绘制函数（通常是重写的 paintEvent() 函数）。
        这样，部件将使用更新后的数据或外观进行重新绘制，以反映最新的更改*/
}
//笔
void RenderArea::setPen(const QPen &newPen)
{
    pen = newPen;
    update();
}
//画刷
void RenderArea::setBrush(const QBrush &newBrush)
{
    brush = newBrush;
    update();
}
//抗锯齿
void RenderArea::setAntialiased(bool newAntialiased)
{
    antialiased = newAntialiased;
    update();
}
//坐标轴一系列转换
void RenderArea::setTransformed(bool newTransformed)
{
    transformed = newTransformed;
    update();
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    static const QPoint points[4] =
    {
        QPoint(10, 80),
        QPoint(20, 10),
        QPoint(80, 30),
        QPoint(90, 70)
    };
    QRect rect(10, 20, 80, 60);

    QPainterPath path;//一系列绘图操作的顺序集合
    path.moveTo(20, 80); //把画笔移动到指定位置
    path.lineTo(20, 30); //这个函数用于从当前点（上一步的终点）绘制一条直线到指定的坐标(20, 30)。它将画笔落下，从当前点绘制直线到目标点。
    path.cubicTo(80, 0, 50, 50, 80, 80); //绘制贝塞尔曲线80,80是终点位置3

    int startAngle = 20 * 16; //扇形的角度
    int arcLength = 120 * 16; //扇形的长度

    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    if (antialiased) //判断是否抗锯齿
        painter.setRenderHint(QPainter::Antialiasing, true); //设置绘图的渲染提示:抗锯齿，true代表启动了

    for (int x = 0; x < width(); x += 100)
        for (int y = 0; y < height(); y += 100)
        {
            painter.save();//保存当前画家的状态

            painter.translate(x, y); //位移

            if (transformed) //判断是否旋转
            {
                painter.translate(50, 50);

                painter.rotate(60.0);//将当前坐标系统绕原点旋转 60 度
                painter.scale(0.6, 0.9); //对坐标系统进行缩放,。之后的绘制操作将按照新的坐标系统进行绘制，图形将被缩放为更矮更胖的形状。

                painter.translate(-50, -50); //将坐标系统还原
            }
            //根据形状开始绘画
            switch (shap)
            {
                case Line:
                    painter.drawLine(rect.bottomLeft(), rect.topRight());
                    break;
                case Point:
                    painter.drawPoints(points, 4);
                    break;
                case PolyLine:
                    painter.drawPolyline(points, 4);
                    break;
                case Polygon:
                    painter.drawPolygon(points, 4);
                    break;
                case Rect:
                    painter.drawRect(rect);
                    break;
                case RoundedRect:
                    painter.drawRoundedRect(rect, 25, 25, Qt::RelativeSize);
                    break;
                case Chord:
                    painter.drawChord(rect, startAngle, arcLength);
                    break;
                case Pie:
                    painter.drawPie(rect, startAngle, arcLength);
                    break;
                case Path:
                    painter.drawPath(path);
                    break;
                case Text:
                    painter.drawText(rect,
                                     Qt::AlignCenter,
                                     tr("Qt by\nThe Qt Company"));
                    break;
                case Pixmap:
                    painter.drawPixmap(10, 10, pixmap.scaled(80, 80));
            }

            painter.restore();//返回画家的状态
        }
}
