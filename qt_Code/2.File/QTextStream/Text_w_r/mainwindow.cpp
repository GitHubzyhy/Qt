#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QSaveFile>
#include <QException>
#include <QMessageBox>
#include <QTextBlock>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getFile(bool save)
{
    QString curPath = QDir::currentPath(); //应用程序可执行目录
    QString aFileName;//存储点击的文件的绝对路径

    if (save)
        aFileName = QFileDialog::getSaveFileName(this, "打开一个文件", curPath,
                    tr("程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)"));
    else
        aFileName = QFileDialog::getOpenFileName(this, "打开一个文件", curPath,
                    tr("程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)"));

    if (aFileName.isEmpty())
        return aFileName;

    QFileInfo fileInfo(aFileName);//为另存的时候打开目录做准备
    QDir::setCurrent(fileInfo.absolutePath()); //设置应用程序的当前工作目录为fileInfo的绝对路径不包括文件名

    return aFileName;
}

void MainWindow::on_actionQpen_IODevice_triggered()
{
    //QFIle打开
    QFile aFile(getFile());//参数是路径

    if (!aFile.exists()) //文件不存在
        return;

    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text)) //以只读和文本方式打开
        return;

    ui->textEditDevice->appendPlainText(aFile.readAll());//参数里面返回的是字节数组
    aFile.close();
}

void MainWindow::on_actSave_IODevice_triggered()
{
    //另存为
    QFile aFile(getFile(true));

    if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text)) //文件不存在就创建一个新的文件
        return;

    QString str = ui->textEditDevice->toPlainText();
    aFile.write(str.toUtf8(), str.toUtf8().length()); //开始写入文件

    aFile.close();
}

void MainWindow::on_actSave_TextSafe_triggered()
{
    //安全的存储
    QSaveFile aFile(getFile(true));

    if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    aFile.setDirectWriteFallback(false);//使用临时文件来保存数据，然后在成功写入后再将临时文件重命名为目标文件。这样做的好处是可以避免原始文件的损坏或部分写入。

    try//不用文件关闭
    {
        QString str = ui->textEditDevice->toPlainText();
        aFile.write(str.toUtf8(), str.toUtf8().length()); //写到临时文件里
        aFile.commit();//成功以后再整体提交
    }
    catch (QException &e)
    {
        QMessageBox::warning(this, "异常", "保存文件过程发生错误！");
        aFile.cancelWriting();//取消文件写入操作
    }
}

void MainWindow::on_actOpen_TextStream_triggered()
{
    //用textstream打开文件
    //用只读的方式
    QFile aFile(getFile());

    if (!aFile.exists()) //文件不存在
        return;

    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream aStream(&aFile);
    aStream.setAutoDetectUnicode(true);//防止中文乱码

    while (!aStream.atEnd())
    {
        QString str = aStream.readLine(); //一行一行的读取
        ui->textEditStream->appendPlainText(str);
    }

    aFile.close();
}

void MainWindow::on_actSave_TextStream_triggered()
{
    //QTextStream另存
    QSaveFile aFile(getFile(true));

    if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    aFile.setDirectWriteFallback(false);

    try
    {
        //写到临时文件里
        QTextStream aStream(&aFile);
        aStream.setAutoDetectUnicode(true);//防止中文乱码

        QTextDocument *doc = ui->textEditStream->document();//获取文本对象

        for (int i = 0; i < doc->blockCount(); ++i) //循环每个文本块
        {
            aStream << doc->findBlockByNumber(i).text(); //将当前文本块写入
            aStream << "\n";
        }

        aFile.commit();//成功后整体提交
    }
    catch (QException &e)//发生异常的时候不会覆盖以前的文件
    {
        QMessageBox::warning(this, "异常", "保存文件过程发生错误！");
        aFile.cancelWriting();
    }
}
