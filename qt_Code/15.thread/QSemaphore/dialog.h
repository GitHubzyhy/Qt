#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "qmythread.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    //线程
    void onthreadA_started();
    void onthreadA_finished();

    void onthreadB_started();
    void onthreadB_finished();
    //将信息显示出来
    void onthreadB_newValue(int *data, int count, int bufNo);

    void on_btnStartThread_clicked();//启动线程
    void on_btnStopThread_clicked();//停止线程
    void on_btnClear_clicked();//清空文本

private:
    Ui::Dialog *ui;

    QThreadDAQ threadProducer;//数据采集
    QThreadShow threadConsumer;//读取数据

protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif // DIALOG_H
