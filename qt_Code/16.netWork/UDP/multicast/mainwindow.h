#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostInfo>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class QLabel;
class QUdpSocket;
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *LabSocketState;
    QUdpSocket *udpSocket;//用于与连接的客户端通讯的QTcpSocket
    QHostAddress groupAddress;//组播地址
    QString getLocalIP();//获取本机IP地址
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //自定义槽函数
    void onSocketStateChange(QAbstractSocket::SocketState socketState);
    void onSocketReadyRead();//读取socket传入的数据

    //工具栏
    void on_actStart_triggered();//加入组播
    void on_actStop_triggered();//退出组播
    void on_actClear_triggered();//清空文本框
    void on_actHostInfo_triggered();//本机地址

    //按钮
    void on_btnMulticast_clicked();//发送组播消息

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
