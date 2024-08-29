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
    QTcpSocket *tcpClient; //socket
    QLabel *LabSocketState; //状态栏显示标签

    QString getLocalIP();//获取本机IP地址

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //自定义槽函数
    void onConnected();//连接到服务器后
    void onDisconnected();//socket断开后
    void onSocketStateChange(QAbstractSocket::SocketState socketState);//状态变化
    void onSocketReadyRead();//读取socket传入的数据

    void on_actConnect_triggered();//连接到服务器
    void on_actDisconnect_triggered();//断开连接
    void on_actClear_triggered();//清空文本框
    void on_btnSend_clicked();//发送消息

private:
    Ui::MainWindow *ui;

    // QWidget interface
protected:
    virtual void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
