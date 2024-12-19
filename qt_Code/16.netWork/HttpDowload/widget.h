#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class QNetworkReply;
class QFile;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    //自定义槽函数
    void on_finished();//网络响应结束
    void on_readyRead();//读取下载的数据
    void on_downloadProgress(qint64 bytesRead, qint64 totalBytes);//下载进程

    void on_btnDownload_clicked();//下载
    void on_btnDefaultPath_clicked();//缺省路径

    //实时跟踪文本变化
    void on_editURL_textChanged(const QString &arg1);

private:
    Ui::Widget *ui;

    QNetworkAccessManager networkManager;//网络管理
    QNetworkReply *reply; //网络响应
    QFile *downloadedFile;//下载保存的临时文件
};
#endif // WIDGET_H
