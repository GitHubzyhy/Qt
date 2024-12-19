#ifndef QWCHARTVIEW_H
#define QWCHARTVIEW_H

#include <QChartView>

class QWChartView : public QChartView
{
    Q_OBJECT
public:
    explicit QWChartView(QWidget *parent = nullptr);

private:
    QPoint beginPoint;//选择矩形区域的起点
    QPoint endPoint;//选择矩形区域的终点
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;//鼠标左键按下
    void mouseMoveEvent(QMouseEvent *event) override;//鼠标
    void mouseReleaseEvent(QMouseEvent *event) override;//鼠标释放左键
    void keyPressEvent(QKeyEvent *event) override;//按键事件
signals:
    void mouseMovePoint(QPoint point);//鼠标移动信号
};

#endif // QWCHARTVIEW_H
