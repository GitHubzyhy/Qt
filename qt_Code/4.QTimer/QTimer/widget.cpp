#include "widget.h"
#include "./ui_widget.h"
#include <QTimer>
#include <QElapsedTimer>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_timer = new QTimer(this); //挂在对象树上面，不用手动delete
    m_counter = new QElapsedTimer;
    m_timer->stop();//停止定时器
    m_timer->setTimerType(Qt::CoarseTimer);//设置精度
    ui->radioCoarse->setChecked(true);//将界面上的radioButton设置选中状态

    connect(m_timer, &QTimer::timeout, this, &Widget::do_timer_timerout);
}

Widget::~Widget()
{
    delete m_counter;
    delete ui;
}
//中断时调用的槽函数
void Widget::do_timer_timerout()
{
    QApplication::beep();//发出声音

    QTime curTime = QTime::currentTime();
    ui->lcdHour->display(curTime.hour());//设置显示的时分秒
    ui->lcdMin->display(curTime.minute());
    ui->lcdSec->display(curTime.second());

    if (m_timer->isSingleShot()) //判断是否是单次计时器
    {
        int tmMsec = m_counter->elapsed(); //返回从启动或重启计时器以来经过的毫秒数。
        QString str = QString("流逝的时间：%1毫秒").arg(tmMsec);
        ui->labelMessage->setText(str);

        ui->btnStart->setEnabled(true);
        ui->btnOneShot->setEnabled(true);
        ui->btnStop->setEnabled(false);
    }
}
//开始
void Widget::on_btnStart_clicked()
{
    m_timer->setInterval(ui->spinBoxIntv->value());//设置定时器的时间间隔

    if (ui->radioContiue->isChecked()) //界面的radioButton判断是否是单次计时器
        m_timer->setSingleShot(false);//默认为false
    else
        m_timer->setSingleShot(true);

    if (ui->radioPrecise->isChecked()) //设置精确度
        m_timer->setTimerType(Qt::PreciseTimer);
    else if (ui->radioCoarse->isChecked())
        m_timer->setTimerType(Qt::CoarseTimer);
    else
        m_timer->setTimerType(Qt::VeryCoarseTimer);

    m_timer->start();//启动定时器
    m_counter->start();//启动计时器

    ui->btnStart->setEnabled(false);
    ui->btnOneShot->setEnabled(false);
    ui->btnStop->setEnabled(true);
}
//停止
void Widget::on_btnStop_clicked()
{
    m_timer->stop();//让定时器停下来
    int tmMsec = m_counter->elapsed(); //返回从启动或重启计时器以来经过的毫秒数。
    int ms = tmMsec % 1000;
    int s = tmMsec / 1000;
    QString str = QString("流逝的时间：%1秒,%2毫秒").arg(s).arg(ms);
    ui->labelMessage->setText(str);

    ui->btnStart->setEnabled(true);
    ui->btnOneShot->setEnabled(true);
    ui->btnStop->setEnabled(false);
}
//动态创建单次定时器
void Widget::on_btnOneShot_clicked()
{
    int intv = ui->spinBoxIntv->value(); //从界面上拿到周期是多少秒

    m_timer->setSingleShot(true);//只触发一次
    QTimer::singleShot(intv, Qt::PreciseTimer, this, &Widget::do_timer_timerout);//第二种用法
    m_counter->start();//计时器开始启动

    ui->btnOneShot->setEnabled(false);//让这个按钮失效
}
