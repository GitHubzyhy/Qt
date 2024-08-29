#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include<QPen>

namespace Ui
{
    class RenderArea;
}

class QBrush;
class QPen;
class RenderArea : public QWidget
{
    Q_OBJECT

public:
    enum Shape
    {
        Line, Point, PolyLine, Polygon, Rect, RoundedRect,
        Chord, Pie, Path, Text, Pixmap
    };

    explicit RenderArea(QWidget *parent = nullptr);
    ~RenderArea();

    //对外接口
    void setShap(Shape newShap);//形状
    void setPen(const QPen &newPen);//笔
    void setBrush(const QBrush &newBrush);//画刷
    void setAntialiased(bool newAntialiased);//抗锯齿
    void setTransformed(bool newTransformed);//坐标轴一系列转换

private:
    Ui::RenderArea *ui;

    Shape shap;
    QPen pen;
    QBrush brush;
    bool antialiased;//抗锯齿
    bool transformed;//坐标轴一系列转换
    QPixmap pixmap;//绘制pixmap图片

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);//要绘画只能重定义
};

#endif // RENDERAREA_H
