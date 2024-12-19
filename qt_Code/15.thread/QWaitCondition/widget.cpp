#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //线程
    connect(&threadProducer, SIGNAL(started()), this, SLOT(onthreadA_started()));
    connect(&threadProducer, SIGNAL(finished()), this, SLOT(onthreadA_finished()));

    connect(&threadConsumer, SIGNAL(started()), this, SLOT(onthreadB_started()));
    connect(&threadConsumer, SIGNAL(finished()), this, SLOT(onthreadB_finished()));
    //接受传递过来的值
    connect(&threadConsumer, SIGNAL(newValue(int, int)), this, SLOT(onthreadB_newValue(int, int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event)
{
    if (threadProducer.isRunning()) //正在运行
    {
        threadProducer.stopThread();
        threadProducer.wait();//阻止线程执行
    }

    if (threadConsumer.isRunning())
    {
        threadConsumer.terminate();//因为threadB可能处于等待状态，所以用terminate强制结束
        threadConsumer.wait();//阻止线程执行
    }
    event->accept();
}

void Widget::onthreadA_started()
{
    ui->labA->setText("Thread Producer状态: started");
}

void Widget::onthreadA_finished()
{
    ui->labA->setText("Thread Producer状态: finished");
}

void Widget::onthreadB_started()
{
    ui->labB->setText("Thread Consumer状态: started");
}

void Widget::onthreadB_finished()
{
    ui->labB->setText("Thread Consumer状态: finished");
}
//将消费者发送的数值显示出来
void Widget::onthreadB_newValue(int seq, int diceValue)
{
    QString str = QString::asprintf("第 %d 次掷骰子，点数为：%d",
                                    seq, diceValue);
    ui->plainTextEdit->appendPlainText(str);

    QPixmap pic;
    QString filename = QString::asprintf(":/images/%d.png", diceValue);
    pic.load(filename);
    ui->labPic->setPixmap(pic);
}
//启动线程
void Widget::on_btnStartThread_clicked()
{
    threadConsumer.start();//必须消费者先
    threadProducer.start();

    ui->btnStartThread->setEnabled(false);
    ui->btnStopThread->setEnabled(true);
}
//结束线程
void Widget::on_btnStopThread_clicked()
{
    threadProducer.stopThread();//结束线程的run()函数执行
    threadProducer.wait();//

    threadConsumer.terminate(); //因为threadB可能处于等待状态，所以用terminate强制结束
    threadConsumer.wait();

    ui->btnStartThread->setEnabled(true);
    ui->btnStopThread->setEnabled(false);
}
//清空文本
void Widget::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}
