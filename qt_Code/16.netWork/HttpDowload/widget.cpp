#include "widget.h"
#include "./ui_widget.h"
#include <QDir>
#include <QMessageBox>
#include <QUrl>
#include <QNetworkReply>
#include <QDesktopServices>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->editURL->setClearButtonEnabled(true);
}

Widget::~Widget()
{
    delete ui;
}
//网络响应结束
void Widget::on_finished()
{
    QFileInfo fileInfo;
    fileInfo.setFile(downloadedFile->fileName());

    downloadedFile->close();
    delete downloadedFile;
    downloadedFile = Q_NULLPTR;

    reply->close();
    reply = Q_NULLPTR;

    if (ui->checkOpen->isChecked())//打开下载的文件
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));

    ui->btnDownload->setEnabled(true);

}
//读取下载的数据
void Widget::on_readyRead()
{
    downloadedFile->write(reply->readAll());
}
//下载进程
void Widget::on_downloadProgress(qint64 bytesRead, qint64 totalBytes)
{
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesRead);
    ui->lbProgr->setText(QString::number(double(bytesRead) / totalBytes * 100) + "%");
}
//下载
void Widget::on_btnDownload_clicked()
{
    QString urlSpec = ui->editURL->text().trimmed();
    if (urlSpec.isEmpty())
    {
        QMessageBox::information(this, "错误",
                                 "请指定需要下载的URL");
        return;
    }

    QUrl newUrl = QUrl::fromUserInput(urlSpec);//URL地址
    if (!newUrl.isValid())
    {
        QMessageBox::information(this, "错误",
                                 QString("无效URL: %1 \n 错误信息: %2").arg(urlSpec, newUrl.errorString()));
        return;
    }

    QString tempDir = ui->editPath->text().trimmed(); //临时目录
    if (tempDir.isEmpty())
    {
        QMessageBox::information(this, tr("错误"), "请指定保存下载文件的目录");
        return;
    }
    QString fullFileName = tempDir + newUrl.fileName(); //文件路径
    if (QFile::exists(fullFileName))//如果存在该文件就删除
        QFile::remove(fullFileName);

    downloadedFile = new QFile(fullFileName); //创建临时文件
    if (!downloadedFile->open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("打开错误")
                             , tr("打开文件错误：") + downloadedFile->errorString());
        return;
    }
    ui->btnDownload->setEnabled(false);

    //发送网络请求，创建网络响应
    reply = networkManager.get(QNetworkRequest(newUrl));
    connect(reply, &QNetworkReply::finished,//下载结束后
            this, &Widget::on_finished);
    connect(reply, &QNetworkReply::readyRead,//缓冲区有可读取数据
            this, &Widget::on_readyRead);
    connect(reply, &QNetworkReply::downloadProgress,//网络操作进度
            this, &Widget::on_downloadProgress);
}
//缺省路径
void Widget::on_btnDefaultPath_clicked()
{
    QString curPath = QDir::currentPath();

    QDir dir(curPath);
    QString sub = "temp";
    dir.mkdir(sub);

    ui->editPath->setText(curPath + "/" + sub + "/");
}
//实时跟踪文本变化
void Widget::on_editURL_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);
}
