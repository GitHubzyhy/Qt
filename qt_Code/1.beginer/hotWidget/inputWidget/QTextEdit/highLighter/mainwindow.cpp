#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "highlighter.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);
    ui->textEdit->setFont(font);

    highlighter = new Highlighter(ui->textEdit->document());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
                           this,
                           "打开代码",
                           "/home",
                           tr("代码文件(*.h *.cpp *.c)"));
    QFile fileIn(fileName);
    if (!fileIn.open(QIODevice::ReadOnly | QFile::Text))
    {
        //打开错误
        QMessageBox::warning(this, tr("打开错误")
                             , tr("打开文件错误：") + fileIn.errorString());
        return; //不处理文件
    }
    ui->textEdit->setPlainText(fileIn.readAll());
}
