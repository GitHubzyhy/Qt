#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//用QPainterPath绘制一个五角星
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};
#endif // WIDGET_H
