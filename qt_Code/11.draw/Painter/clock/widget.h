#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};
#endif // WIDGET_H
