#include "dialog.h"
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(&threadProducer, SIGNAL(started()), this, SLOT(onthreadA_started()));
    connect(&threadProducer, SIGNAL(finished()), this, SLOT(onthreadA_finished()));

    connect(&threadConsumer, SIGNAL(started()), this, SLOT(onthreadB_started()));
    connect(&threadConsumer, SIGNAL(finished()), this, SLOT(onthreadB_finished()));

    connect(&threadConsumer, SIGNAL(newValue(int *, int, int)),
            this, SLOT(onthreadB_newValue(int *, int, int)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onthreadA_started()
{
    ui->labA->setText("Thread Producer状态: started");
}

void Dialog::onthreadA_finished()
{
    ui->labA->setText("Thread Producer状态: finished");
}

void Dialog::onthreadB_started()
{
    ui->labB->setText("Thread Consumer状态: started");
}

void Dialog::onthreadB_finished()
{
    ui->labB->setText("Thread Consumer状态: finished");
}
//将信息显示出来
void Dialog::onthreadB_newValue(int *data, int count, int bufNo)
{
    QString str = QString::asprintf("第 %d 个缓冲区：", bufNo);
    for (int i = 0; i < count; i++)
    {
        str = str + QString::asprintf("%d, ", *data);
        data++;
    }
    str = str + '\n';

    ui->plainTextEdit->appendPlainText(str);
}
//启动线程
void Dialog::on_btnStartThread_clicked()
{
    threadConsumer.start();
    threadProducer.start();

    ui->btnStartThread->setEnabled(false);
    ui->btnStopThread->setEnabled(true);
}
//停止线程
void Dialog::on_btnStopThread_clicked()
{
    threadConsumer.terminate(); //因为threadB可能处于等待状态，所以用terminate强制结束
    threadConsumer.wait();//

    threadProducer.terminate();//结束线程的run()函数执行
    threadProducer.wait();//

    ui->btnStartThread->setEnabled(true);
    ui->btnStopThread->setEnabled(false);
}

void Dialog::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

void Dialog::closeEvent(QCloseEvent *event)
{
    if (threadProducer.isRunning())
    {
        threadProducer.terminate();//结束线程的run()函数执行
        threadProducer.wait();//
    }

    if (threadConsumer.isRunning())
    {
        threadConsumer.terminate(); //因为threadB可能处于等待状态，所以用terminate强制结束
        threadConsumer.wait();//
    }

    event->accept();
}
