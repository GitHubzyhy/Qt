#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QHostAddress>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Dialog;
}
QT_END_NAMESPACE

class QHostInfo;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void lookedUpHostInfo(const QHostInfo &host);//查找主机信息的槽函数

    //QHostInfo 获取本机主机名和IP地址
    void on_btnGetHostInfo_clicked();
    void on_btnLookup_clicked();//查找主机地址信息

    //QNetworkInterface的使用
    void on_btnDetail_clicked();
    void on_btnALLInterface_clicked();

    void on_btnClear_clicked();//清空文本

private:
    Ui::Dialog *ui;

    //通过协议类型返回协议名称
    QString protocolName(QAbstractSocket::NetworkLayerProtocol protocol);
};
#endif // DIALOG_H
