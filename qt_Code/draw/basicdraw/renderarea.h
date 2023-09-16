#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include<QBrush>
#include<QPen>
#include<QPixmap>

namespace Ui {
class RenderArea;
}

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    enum Shape{Line,Point,PolyLine,Polygon,Rect,RoundedRect,
                 Chord,Pie,Path,Text,Pixmap};

    explicit RenderArea(QWidget *parent = nullptr);
    ~RenderArea();
//对外接口
    void setShap(Shape newShap);
    void setPen(const QPen &newPen);
    void setBrush(const QBrush &newBrush);
    void setAntialiased(bool newAntialiased);
    void setTransformed(bool newTransformed);
    void setPixmap(const QPixmap &newPixmap);

private:
    Ui::RenderArea *ui;
    Shape shap;
    QPen pen;
    QBrush brush;
    bool antialiased;//抗锯齿
    bool transformed;
    QPixmap pixmap;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);//要绘画只能重定义
};

#endif // RENDERAREA_H
