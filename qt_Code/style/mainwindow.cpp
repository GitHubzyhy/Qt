#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStyleFactory>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //匹配以任意字符开头，后面紧跟着一个可选的加号，然后是"Style"的字符串。
    //捕获组(.*)将捕获加号之前的所有字符。
    QRegularExpression regExp(".(.*)\\+?Style");
    QString defaultStyle = QApplication::style()->metaObject()->className();
    ui->statusbar->showMessage(defaultStyle);

    QRegularExpressionMatch match = regExp.match(defaultStyle);
    if (match.hasMatch())//是否匹配
        defaultStyle = match.captured(1);//捕获第1组

    //将当前平台上所有的
    ui->comboSysStyle->addItems(QStyleFactory::keys());
    ui->comboSysStyle->setCurrentIndex(
        ui->comboSysStyle->findText(defaultStyle, Qt::MatchContains));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//下拉列表改变时候
void MainWindow::on_comboSysStyle_currentIndexChanged(int index)
{
    QString strStyle = ui->comboSysStyle->currentText();
    //使用选择的样式名称创建样式style
    QStyle *style = QStyleFactory::create(strStyle);
    //使用选择的样式名称创建样式style
    qApp->setStyle(style);
    ui->statusbar->showMessage(style->metaObject()->className());
}

void MainWindow::on_btnStyleSheet_clicked()
{
    this->setStyleSheet("QPlainTextEdit{color:blue;font:13pt '宋体';}"
                        "QPushButton:hover{background-color:lime;}"
                        "QLineEdit{border:2px groove red;"
                        "background-color:rgb(170,255,127);"
                        "border-radius:6px;}"
                        "QCheckBox:checked{color:red;}"
                        "QRadioButton:checked{color:red;}");
}

void MainWindow::on_btnNormal_clicked()
{
    this->setStyleSheet("");
}
