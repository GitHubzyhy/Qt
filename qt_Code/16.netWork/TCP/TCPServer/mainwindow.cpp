#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QHostInfo>
#include <QTcpSocket>

//获取本机IP地址
QString MainWindow::getLocalIP()
{
    QString hostName = QHostInfo::localHostName();
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QString localIP = "";

    QList<QHostAddress> addList = hostInfo.addresses(); //ip地址列表
    if (!addList.isEmpty())
        for (int i = 0; i < addList.count(); ++i)
        {
            QHostAddress aHost = addList.at(i);
            if (QAbstractSocket::IPv4Protocol == aHost.protocol())
            {
                localIP = aHost.toString();
                break;
            }
        }
    return localIP;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LabListen = new QLabel("监听状态:");
    LabListen->setMinimumWidth(150);
    ui->statusbar->addWidget(LabListen);

    LabSocketState = new QLabel("Socket状态：");
    LabSocketState->setMinimumWidth(200);
    ui->statusbar->addWidget(LabSocketState);

    QString localIP = getLocalIP(); //本机IP
    this->setWindowTitle(this->windowTitle() + QString("----本机IP：") + localIP);
    ui->comboIP->addItem(localIP);

    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection,
            this, &MainWindow::onNewConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//有新连接时(客户端接入时候)
void MainWindow::onNewConnection()
{
    tcpSocket = tcpServer->nextPendingConnection();//创建socket
    connect(tcpSocket, &QTcpSocket::connected,//socket 连接建立时
            this, &MainWindow::onClientConnected);
    onClientConnected();

    connect(tcpSocket, &QTcpSocket::disconnected,//socket 连接断开时
            this, &MainWindow::onClientDisconnected);

    connect(tcpSocket, &QTcpSocket::stateChanged,//socket 状态变化时
            this, &MainWindow::onSocketStateChange);
    onSocketStateChange(tcpSocket->state());

    connect(tcpSocket, &QTcpSocket::readyRead,//socket的读取缓冲区有新数据时
            this, &MainWindow::onSocketReadyRead);
}
//socket状态变化时
void MainWindow::onSocketStateChange(QAbstractSocket::SocketState socketState)
{
    switch (socketState)
    {
        case QAbstractSocket::UnconnectedState:
            LabSocketState->setText(QString("scoket状态：套接字处于未连接状态"));
            break;
        case QAbstractSocket::HostLookupState:
            LabSocketState->setText(QString("scoket状态：套接字正在进行主机名查找。"));
            break;
        case QAbstractSocket::ConnectingState:
            LabSocketState->setText(QString("scoket状态：套接字正在尝试建立连接"));
            break;

        case QAbstractSocket::ConnectedState:
            LabSocketState->setText(QString("scoket状态：套接字已成功连接"));
            break;

        case QAbstractSocket::BoundState:
            LabSocketState->setText(QString("scoket状态：套接字已绑定到地址和端口。"));
            break;

        case QAbstractSocket::ClosingState:
            LabSocketState->setText(QString("scoket状态：套接字正在关闭连接"));
            break;

        case QAbstractSocket::ListeningState:
            LabSocketState->setText(QString("scoket状态：套接字处于监听状态"));
    }
}
//客户端接入时
void MainWindow::onClientConnected()
{
    ui->plainTextEdit->appendPlainText(QString("**client socket connected"));
    ui->plainTextEdit->appendPlainText(QString("**peer address:") +
                                       tcpSocket->peerAddress().toString());
    ui->plainTextEdit->appendPlainText(QString("**peer port:") +
                                       QString::number(tcpSocket->peerPort()));

}
//客户端断开连接时
void MainWindow::onClientDisconnected()
{
    ui->plainTextEdit->appendPlainText(QString("**client socket disconnected"));
    tcpSocket->deleteLater();//删除本次会话的socket
}
//读取socket传入的数据
void MainWindow::onSocketReadyRead()
{
    while (tcpSocket->canReadLine())
        ui->plainTextEdit->appendPlainText("[in] " + tcpSocket->readLine());
}
//开始监听
void MainWindow::on_actStart_triggered()
{
    QString IP = ui->comboIP->currentText(); //在网络中定位设备
    int port = ui->spinPort->value(); //区分不同应用或程序

    QHostAddress addr(IP);
    tcpServer->listen(addr, port);//开始监听
    ui->plainTextEdit->appendPlainText(QString("**开始监听..."));
    ui->plainTextEdit->appendPlainText(QString("**服务器地址：")
                                       + tcpServer->serverAddress().toString());
    ui->plainTextEdit->appendPlainText(QString("**服务器端口：")
                                       + QString::number(tcpServer->serverPort()));

    ui->actStart->setEnabled(false);
    ui->actStop->setEnabled(true);

    LabListen->setText(QString("监听状态：正在监听"));
}
//停止监听
void MainWindow::on_actStop_triggered()
{
    if (tcpServer->isListening()) //正在监听
    {
        tcpServer->close();//关闭服务器,停止网络监听
        ui->actStart->setEnabled(true);
        ui->actStop->setEnabled(false);
        LabListen->setText(QString("监听状态：已停止监听"));
    }
}
//清空文本框
void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}
//本机地址
void MainWindow::on_actHostInfo_triggered()
{
    QString hostName = QHostInfo::localHostName(); //本地主机名
    ui->plainTextEdit->appendPlainText(QString("本机主机名：") + hostName + "\n");
    QHostInfo hostInfo = QHostInfo::fromName(hostName);

    QList<QHostAddress> addList = hostInfo.addresses(); //
    if (!addList.isEmpty())
        for (int i = 0; i < addList.count(); i++)
        {
            QHostAddress aHost = addList.at(i);
            if (QAbstractSocket::IPv4Protocol == aHost.protocol())
            {
                QString IP = aHost.toString();
                ui->plainTextEdit->appendPlainText(QString ("本机IP地址：") + aHost.toString());
                if (ui->comboIP->findText(IP) < 0)
                    ui->comboIP->addItem(IP);
            }
        }
}
//发送消息
void MainWindow::on_btnSend_clicked()
{
    QString msg = ui->editMsg->text();
    ui->plainTextEdit->appendPlainText(QString("[out] ") + msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();//焦点

    QByteArray str = msg.toUtf8(); //转换成字节数组
    str.append('\n');//添加一个换行符
    tcpSocket->write(str);//QIODevice的接口
}
//关闭窗口时停止监听
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (tcpServer->isListening())
        tcpServer->close();;//停止网络监听
    event->accept();
}
