#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class QLabel;
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *LabSocketState;//socket状态显示标签
    QUdpSocket *udpSocket;//用于UDP 通信
    QString getLocalIP();//获取本机IP地址

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //自定义槽函数
    void onSocketStateChange(QAbstractSocket::SocketState socketState);//状态变化
    void onSocketReadyRead();//读取socket传入的数据

    //工具栏
    void on_actStart_triggered();//绑定端口
    void on_actStop_triggered();//解除绑定
    void on_actClear_triggered();//清空文本框
    void on_actHostInfo_triggered();//本机地址

    //按钮
    void on_btnSend_clicked();//发送消息
    void on_btnBroadcast_clicked();//广播消息

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
