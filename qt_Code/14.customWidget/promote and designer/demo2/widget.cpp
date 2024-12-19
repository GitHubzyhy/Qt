#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_horizontalSlider_valueChanged(int value)
{
    ui->battery->setPowerLevel(value);
}

void Widget::on_battery_powerLevelChanged(int arg1)
{
    QString str = QStringLiteral("当前电量：") + QString::asprintf("%d %%", arg1);
    ui->LabInfo->setText(str);
}
