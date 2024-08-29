#ifndef QWGRAPHICSVIEW_H
#define QWGRAPHICSVIEW_H

#include <QGraphicsView>

class QWGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    QWGraphicsView(QWidget *parent = nullptr);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
signals:
    //QGraphicsView没有与mouseMoveEvent()相关的信号
    void mouseMovePoint(QPoint point);
    void mouseClicked(QPoint point);
};

#endif // QWGRAPHICSVIEW_H
