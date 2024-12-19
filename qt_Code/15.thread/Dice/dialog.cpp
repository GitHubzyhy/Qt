#include "dialog.h"
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(&threadA, &QDiceThread::started, this, &Dialog::onthreadA_started);
    connect(&threadA, &QDiceThread::finished, this, &Dialog::onthreadA_finished);
    connect(&threadA, &QDiceThread::newValue, this, &Dialog::onthreadA_newValue);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::closeEvent(QCloseEvent *event)
{
    if (threadA.isRunning())
    {
        threadA.stopThread();
        threadA.wait();
    }
    event->accept();
}
//线程的started()信号的响应槽函数
void Dialog::onthreadA_started()
{
    ui->labA->setText("Thread状态：thread started");
}
//线程的 finished()信号的响应槽函数
void Dialog::onthreadA_finished()
{
    ui->labA->setText("Thread状态：thread finished");
}
//QDiceThread的newValue()信号的响应槽函数，显示骰子次数和点数
void Dialog::onthreadA_newValue(int seq, int diceValue)
{
    QString str = QString::asprintf("第 %d 次掷骰子，点数为：%d", seq, diceValue);
    ui->plainTextEdit->appendPlainText(str);

    QPixmap pic;//控制图片的显示
    QString fileName = QString::asprintf(":/images/%d.png", diceValue); //显示骰子点数
    ui->labPic->setScaledContents(true);
    pic.load(fileName);//加载图像
    ui->labPic->setPixmap(pic);
}
//启动线程
void Dialog::on_btnStartThread_clicked()
{
    threadA.start();//开启线程

    //线程控制
    ui->btnStartThread->setEnabled(false);
    ui->btnStopThread->setEnabled(true);
    //筛子
    ui->btnDiceBegin->setEnabled(true);
    ui->btnDiceEnd->setEnabled(false);
}
//开始
void Dialog::on_btnDiceBegin_clicked()
{
    threadA.diceBegin();
    ui->btnDiceBegin->setEnabled(false);
    ui->btnDiceEnd->setEnabled(true);
}
//暂停
void Dialog::on_btnDiceEnd_clicked()
{
    threadA.dicePause();
    ui->btnDiceBegin->setEnabled(true);
    ui->btnDiceEnd->setEnabled(false);
}
//暂停线程
void Dialog::on_btnStopThread_clicked()
{
    threadA.stopThread();
    threadA.wait();//阻止线程执行,直到线程结束(从run()函数返回)

    //线程
    ui->btnStartThread->setEnabled(true);
    ui->btnStopThread->setEnabled(false);
    //骰子
    ui->btnDiceBegin->setEnabled(false);
    ui->btnDiceEnd->setEnabled(false);
}
//清空文本
void Dialog::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}
