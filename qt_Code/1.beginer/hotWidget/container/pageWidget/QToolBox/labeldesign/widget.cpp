#include "widget.h"
#include "./ui_widget.h"
#include <QFont>
#include <QColor>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initControls();//初始化控件
}

Widget::~Widget()
{
    delete ui;
}
//初始化控件
void Widget::initControls()
{
    //字号旋钮框
    ui->spinBoxSize->setRange(4, 100);
    ui->spinBoxSize->setValue(9);

    //颜色组合框的设置
    QStringList colorNames = QColor::colorNames(); //获取常见颜色
    ui->comboBoxFGColor->addItems(colorNames);//设置前景色组合框
    ui->comboBoxFGColor->setCurrentText( "black" );//默认前景色 黑色

    //设置背景色组合框
    ui->comboBoxBGColor->addItems( colorNames );
    ui->comboBoxBGColor->setCurrentText( "lightgray" );//默认背景色，浅灰

    //修改工具箱本身的样式表
    QString strCss = "::tab{ background-color: magenta; }"
                     "QWidget#pageText{ background-color: green; }"
                     "QWidget#pageFont{ background-color: cyan; }"
                     "QWidget#pageColor{ background-color: yellow; }";
    ui->toolBox->setStyleSheet(strCss);//设置qss
}
//修改左边标签控件的文本
void Widget::on_pushButtonEditText_clicked()
{
    QString strText = ui->lineEditText->text().trimmed(); //去除空格
    ui->labelShow->setText(strText);
}
//编辑字体
void Widget::on_fontComboBox_currentTextChanged(const QString &arg1)
{
    QFont txtFont(arg1, ui->spinBoxSize->value());
    ui->labelShow->setFont(txtFont);
}
//编辑字号
void Widget::on_spinBoxSize_valueChanged(int arg1)
{
    QFont txtFont( ui->fontComboBox->currentText(), arg1 );
    ui->labelShow->setFont(txtFont);
}
//前景背景色修改
void Widget::on_comboBoxFGColor_currentTextChanged(const QString &arg1)
{
    QString strFGColor = arg1; //前景色
    QString strBGColor = ui->comboBoxBGColor->currentText(); //背景色

    //样式表
    QString strCss = QString("color: %1; background-color: %2;")
                     .arg(strFGColor)
                     .arg(strBGColor);
    ui->labelShow->setStyleSheet(strCss);
}

void Widget::on_comboBoxBGColor_currentTextChanged(const QString &arg1)
{
    QString strFGColor = ui->comboBoxFGColor->currentText(); //前景色
    QString strBGColor = arg1; //背景色

    //样式表
    QString strCss = QString("color: %1; background-color: %2;")
                     .arg( strFGColor )
                     .arg( strBGColor );
    ui->labelShow->setStyleSheet(strCss);
}
