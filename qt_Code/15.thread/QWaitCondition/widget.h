#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qmythread.h"

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

private:
    Ui::Widget *ui;

    QThreadProducer threadProducer;//生产者
    QThreadConsumer threadConsumer;//消费者
    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    //线程
    void onthreadA_started();
    void onthreadA_finished();

    void onthreadB_started();
    void onthreadB_finished();
    //将消费者发送的数值显示出来
    void onthreadB_newValue(int seq, int diceValue);
    //界面的功能函数
    void on_btnStartThread_clicked();//启动线程
    void on_btnStopThread_clicked();//结束线程
    void on_btnClear_clicked();//清空文本
};
#endif // WIDGET_H
