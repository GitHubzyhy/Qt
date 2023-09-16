#include "mainwindow.h"
#include<QtWidgets>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget=new QWidget(this);
    setCentralWidget(widget);//将widget添加到主窗口中间
    clickBtn=new QPushButton("点击",widget);

    QCheckBox *cb=new QCheckBox("Connect",widget);
    cb->setCheckState(Qt::Checked);//设置单选按钮已经选中
    label=new QLabel(QTime::currentTime().toString(),widget);//添加一个标签，显示当前时间

    QHBoxLayout *hbox=new QHBoxLayout(widget);//将Widget按照水平方向依次排列
    hbox->addWidget(clickBtn);
    hbox->addWidget(cb);
    hbox->addWidget(label);
    startTimer(1000);//每隔一秒调用timerEvent方法

    connect(clickBtn,&QPushButton::clicked,this,&MainWindow::onClick);//建立连接
    connect(cb,&QCheckBox::stateChanged,this,&MainWindow::onCheck);

}

MainWindow::~MainWindow()
{
}

void MainWindow::onClick()
{
    statusBar()->showMessage("按钮被点击");//输出状态栏的信息
}

void MainWindow::onCheck(int state)
{
    statusBar()->showMessage("");//清空状态栏
    if(state==Qt::Checked)
        connect(clickBtn,&QPushButton::clicked,this,&MainWindow::onClick);//建立连接
    else
        disconnect(clickBtn,&QPushButton::clicked,this,&MainWindow::onClick);//断开连接
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    label->setText(QTime::currentTime().toString());
}

