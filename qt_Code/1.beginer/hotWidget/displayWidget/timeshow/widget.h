#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void RecvTimer(); //接收定时器信号的槽函数

private slots:
    void on_pushButton_clicked();//回到今天

private:
    Ui::Widget *ui;
    QTimer *m_timer;//定时器
};

#endif // WIDGET_H
