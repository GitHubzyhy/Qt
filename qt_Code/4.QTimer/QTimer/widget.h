#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class QTimer;
class QElapsedTimer;
class Widget : public QWidget
{
    Q_OBJECT
private:
    QTimer *m_timer;//定时器
    QElapsedTimer *m_counter;//计时器

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void do_timer_timerout();//当定时器到时间了就执行这个函数
    void on_btnStart_clicked();//开始
    void on_btnStop_clicked();//停止
    void on_btnOneShot_clicked();//动态创建单次定时器

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
