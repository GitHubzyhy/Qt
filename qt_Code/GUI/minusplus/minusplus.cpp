#include "minusplus.h"
#include<QPushButton>
#include<QGridLayout>
#include<QLabel>

MinusPlus::MinusPlus(QWidget *parent)
    : QWidget(parent)
{
    auto *plsBtn=new QPushButton("+",this);
    auto *minBtn=new QPushButton("-",this);
    lbl=new QLabel("0",this);

    auto *grid=new QGridLayout(this);
    grid->addWidget(plsBtn, 0, 0, 1, 1);//第3，4个参数表示占据1行1列的空间
    grid->addWidget(minBtn, 0, 1, 1, 1);
    grid->addWidget(lbl, 1, 1, 1, 1);
    setLayout(grid);

    connect(plsBtn,&QPushButton::clicked,this,&MinusPlus::OnPlus);
    connect(minBtn,&QPushButton::clicked,this,&MinusPlus::OnMinus);

}

MinusPlus::~MinusPlus()
{
    delete lbl;
}

void MinusPlus::OnPlus()
{
    int val=lbl->text().toInt();//抓换成整形数字
    lbl->setText(QString::number(++val));
}

void MinusPlus::OnMinus()
{
    int val=lbl->text().toInt();//抓换成整形数字
    lbl->setText(QString::number(--val));
}

