#include "widget.h"
#include<QUiLoader>
#include<QFile>
#include<QtWidgets>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QUiLoader loader;
    QFile file(":/forms/widget.ui");
    file.open(QFile::ReadOnly);
    QWidget *formWidget = loader.load(&file, this);
    file.close();

    this->dumpObjectTree();
    //在窗口小部件从层次结构中查找QSpinBox类型的子窗口部件
    ui_inputSpinBox1 = findChild<QSpinBox*>("inputSpinBox1");
    ui_inputSpinBox2 = findChild<QSpinBox*>("inputSpinBox2");
    ui_outputWidget = findChild<QLabel*>("outputWidget");

    //根据对象名称自动连接对象的槽
    QMetaObject::connectSlotsByName(this);

}

Widget::~Widget()
{
}
//当第一个spinbox数字变化的时候
void Widget::on_inputSpinBox1_valueChanged(int value)
{
    ui_outputWidget->setText(QString::number(value+ui_inputSpinBox2->value()));
}
//当第二个spinbox数字变化的时候
void Widget::on_inputSpinBox2_valueChanged(int value)
{
    ui_outputWidget->setText(QString::number(value+ui_inputSpinBox1->value()));
}
