#include "widget.h"
#include "./ui_widget.h"
#include <QTimer>
#include <QDateTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle(tr("电子钟"));

    m_timer = new QTimer(this);
    //设置定时器触发时间间隔，单位毫秒
    m_timer->setInterval(1000);//1s
    //关联定时器信号到槽函数
    connect(m_timer, &QTimer::timeout, this, &Widget::RecvTimer);

    m_timer->start();//启动定时器
    //调用一次 "回到今天" 槽函数，初始化日历
    on_pushButton_clicked();
}

Widget::~Widget()
{
    delete ui;
}
//接收定时器信号的槽函数
void Widget::RecvTimer()
{
    //获取当前时间
    QDateTime dt = QDateTime::currentDateTime();
    //构造时间字符串
    QString strTime = dt.time().toString("HH:mm:ss"); //设置指定的格式
    //设置 LCD 时钟
    ui->lcdNumber->display(strTime);
    //设置进度条的显示： 秒数%10
    ui->progressBar->setValue(dt.time().second() % 10);
}
//回到今天
void Widget::on_pushButton_clicked()
{
    //获取当前时间
    QDateTime dt = QDateTime::currentDateTime();
    ui->calendarWidget->setSelectedDate(dt.date()); //设置日历为今天
    //点击按钮时，输入焦点在按钮上，这时候日历选中的日子是灰色，容易看不清
    //将输入焦点回到日历控件，这样日历选中日子会重新变成高亮蓝色
    ui->calendarWidget->setFocus();
}
