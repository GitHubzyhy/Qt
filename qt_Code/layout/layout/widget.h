#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void Vertical();//垂直布局
    void Horizontal();//水平布局
    void Hybird();//混合布局
};
#endif // WIDGET_H
