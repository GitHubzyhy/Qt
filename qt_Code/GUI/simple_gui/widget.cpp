#include "widget.h"
#include<QFrame>//一个矩形框架
#include<QGridLayout>
#include<QPushButton>
#include<QApplication>
#include<QSpinBox>

widget::widget(QWidget *parent)
    : QWidget(parent)
{
    auto *frame1=new QFrame(this);//QFrame 提供一个矩形框架相当于容器
    frame1->setFrameStyle(QFrame::Box);//用一个简单矩形渲染框架
    frame1->setCursor(Qt::SizeAllCursor);//四向箭头光标

    auto *frame2=new QFrame(this);
    frame2->setFrameStyle(QFrame::Box);
    frame2->setCursor(Qt::WaitCursor);//鼠标会变成一个等待图标

    auto *frame3=new QFrame(this);
    frame3->setFrameStyle(QFrame::Box);
    frame3->setCursor(Qt::PointingHandCursor);//鼠标变成一个手的形状

    auto *grid=new QGridLayout(this);//网格布局
    grid->addWidget(frame1,0,0);//第0行第0列
    grid->addWidget(frame2,0,1);
    grid->addWidget(frame3,0,2);

    setLayout(grid);//grid如果没有让widget为父对象的时候就必须用这个
    QPushButton *btn=new QPushButton("quit",this);
    connect(btn,&QPushButton::clicked,qApp,&QApplication::quit);

    auto *gridframe=new QGridLayout(frame2);
    gridframe->addWidget(btn);

    QSpinBox *spinbox=new QSpinBox(this);//调整数字的
    gridframe->addWidget(spinbox);
    this->dumpObjectTree();//展示整个对象树
}

widget::~widget()
{
}

