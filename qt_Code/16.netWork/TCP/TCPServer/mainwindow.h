#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>

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
    QLabel *LabListen;//状态栏标签
    QLabel *LabSocketState;//状态栏标签

    QTcpServer *tcpServer;//TCP服务器
    QTcpSocket *tcpSocket;//TCP通讯的Socket

    QString getLocalIP();//获取本机IP地址
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //自定义槽函数
    void onNewConnection();//有新连接时(客户端接入时候)
    void onSocketStateChange(QAbstractSocket::SocketState socketState);//socket状态变化时
    void onClientConnected(); //客户端接入时
    void onClientDisconnected();//客户端断开连接时
    void onSocketReadyRead();//读取socket传入的数据

    void on_actStart_triggered();//开始监听
    void on_actStop_triggered();//停止监听
    void on_actClear_triggered();//清空文本框
    void on_actHostInfo_triggered();//本机地址

    void on_btnSend_clicked();//发送消息

private:
    Ui::MainWindow *ui;

    // QWidget interface
protected://关闭窗口时停止监听
    virtual void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
