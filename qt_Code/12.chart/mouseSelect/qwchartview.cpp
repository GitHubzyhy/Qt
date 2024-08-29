#include "qwchartview.h"
#include<QMouseEvent>

QWChartView::QWChartView(QWidget *parent)
{
    this->setDragMode(QGraphicsView:: RubberBandDrag);//视图组件拖拽框为橡皮框形式
    this->setMouseTracking(true);//只要鼠标移动就会发射mouseMoveEvent事件
}

void QWChartView::mousePressEvent(QMouseEvent *event)
{
    //鼠标左键按下，记录beginPoint
    if (event->button() == Qt::LeftButton)
        beginPoint = event->pos();
    QChartView::mouseMoveEvent(event);
}

void QWChartView::mouseMoveEvent(QMouseEvent *event)
{
    //鼠标移动事件
    QPoint point = event->pos();
    emit mouseMovePoint(point);//发射信号
    QChartView::mouseMoveEvent(event);
}

void QWChartView::mouseReleaseEvent(QMouseEvent *event)
{
    //鼠标左键释放事件
    if (event->button() == Qt::LeftButton)
    {
        endPoint = event->pos();

        QRectF rectF(this->beginPoint, this->endPoint);
        this->chart()->zoomIn(rectF);//将视图放大
    }
    else if (event->button() == Qt::RightButton)
        this->chart()->zoomReset();//鼠标右键释放
    QChartView::mouseReleaseEvent(event);
}

void QWChartView::keyPressEvent(QKeyEvent *event)
{
    //按键控制
    switch (event->key())
    {
        case Qt::Key_Plus:
            chart()->zoom(1.2);
            break;
        case Qt::Key_Minus:
            chart()->zoom(0.8);
            break;
        case Qt::Key_Left:
            chart()->scroll(10, 0); //以dx和dy指定的距离滚动图表的可见区域
            break;
        case Qt::Key_Right:
            chart()->scroll(-10, 0);
            break;
        case Qt::Key_Up:
            chart()->scroll(0, -10);
            break;
        case Qt::Key_Down:
            chart()->scroll(0, 10);
            break;
        case Qt::Key_PageUp:
            chart()->scroll(0, 50);
            break;
        case Qt::Key_PageDown:
            chart()->scroll(0, -50);
            break;
        case Qt::Key_Home:
            chart()->zoomReset();
            break;
        default:
            QGraphicsView::keyPressEvent(event);
    }
}
