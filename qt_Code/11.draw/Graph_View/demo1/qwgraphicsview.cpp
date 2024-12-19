#include "qwgraphicsview.h"
#include <QMouseEvent>

QWGraphicsView::QWGraphicsView(QWidget *parent): QGraphicsView(parent) {}

void QWGraphicsView::mousePressEvent(QMouseEvent *event)
{
    //鼠标左键按下的事件
    if (event->button() == Qt::LeftButton)
    {
        QPoint point = event->pos();
        emit mouseClicked(point);
    }
    QGraphicsView::mousePressEvent(event);
}

void QWGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    //鼠标移动事件
    QPoint point = event->pos(); //QGraphics的坐标
    emit mouseMovePoint(point);

    QGraphicsView::mouseMoveEvent(event);
}
