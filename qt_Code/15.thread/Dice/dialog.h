#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "qdicethread.h"

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

private:
    Ui::Dialog *ui;

    QDiceThread threadA;
    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void onthreadA_started();//线程的started()信号的响应槽函数
    void onthreadA_finished();//线程的 finished()信号的响应槽函数
    //QDiceThread的newValue()信号的响应槽函数，显示骰子次数和点数
    void onthreadA_newValue(int seq, int diceValue);

    void on_btnStartThread_clicked();//启动线程
    void on_btnDiceBegin_clicked();//开始
    void on_btnDiceEnd_clicked();//暂停
    void on_btnStopThread_clicked();//暂停线程
    void on_btnClear_clicked();//清空文本
};
#endif // DIALOG_H
