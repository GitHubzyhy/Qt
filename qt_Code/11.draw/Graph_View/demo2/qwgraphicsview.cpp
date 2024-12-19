#include "qwgraphicsview.h"
#include <QMouseEvent>
//鼠标按下
QWGraphicsView::QWGraphicsView(QWidget *parent) {}

void QWGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)//判断是否是鼠标左键
    {
        QPoint point = event->pos();
        emit mouseClicked(point);
    }
    QGraphicsView::mousePressEvent(event);
}
//鼠标双击事件
void QWGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)//判断是否是鼠标左键
    {
        QPoint point = event->pos();
        emit mouseDoubleClick(point);
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}
//鼠标移动事件
void QWGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    emit mouseMovePoint(point);

    QGraphicsView::mouseMoveEvent(event);
}
//键盘按下事件
void QWGraphicsView::keyPressEvent(QKeyEvent *event)
{
    emit keyPress(event);
    QGraphicsView::keyPressEvent(event);
}
