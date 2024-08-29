#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTcpSocket>
#include <QHostInfo>

//获取本机IP地址
QString MainWindow::getLocalIP()
{
    QString hostName = QHostInfo::localHostName();
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QString localIP = "";

    QList<QHostAddress> addList = hostInfo.addresses(); //IP地址列表
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

    tcpClient = new QTcpSocket(this);
    LabSocketState = new QLabel(QString("Socket状态：")); //状态栏标签
    LabSocketState->setMinimumWidth(250);
    ui->statusbar->addWidget(LabSocketState);

    QString localIP = getLocalIP(); //本机IP
    this->setWindowTitle(this->windowTitle() + QString("----本机IP：") + localIP);
    ui->comboServer->addItem(localIP);

    connect(tcpClient, &QTcpSocket::connected,//socket 连接建立时
            this, &MainWindow::onConnected);
    connect(tcpClient, &QTcpSocket::disconnected,//socket 连接断开时
            this, &MainWindow::onDisconnected);
    connect(tcpClient, &QTcpSocket::stateChanged,//socket 状态变化时
            this, &MainWindow::onSocketStateChange);
    connect(tcpClient, &QTcpSocket::readyRead,//socket的读取缓冲区有新数据时
            this, &MainWindow::onSocketReadyRead);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//连接到服务器后
void MainWindow::onConnected()
{
    ui->plainTextEdit->appendPlainText(QString("**已连接到服务器"));
    ui->plainTextEdit->appendPlainText(QString("**peer address:") +
                                       tcpClient->peerAddress().toString());
    ui->plainTextEdit->appendPlainText(QString("**peer port:") +
                                       QString::number(tcpClient->peerPort()));
    ui->actConnect->setEnabled(false);
    ui->actDisconnect->setEnabled(true);
}
//socket断开后
void MainWindow::onDisconnected()
{
    ui->plainTextEdit->appendPlainText(QString("**已断开与服务器的连接"));
    ui->actConnect->setEnabled(true);
    ui->actDisconnect->setEnabled(false);
}
//状态变化
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

//连接到服务器
void MainWindow::on_actConnect_triggered()
{
    QString address = ui->comboServer->currentText();
    quint16 port = ui->spinPort->value();

    tcpClient->connectToHost(address, port);
    //tcpClient->connectToHost(QHostAddress::LocalHost,port);
}
//断开连接
void MainWindow::on_actDisconnect_triggered()
{
    if (tcpClient->state() == QAbstractSocket::ConnectedState)
        tcpClient->disconnectFromHost();
}
//清空文本框
void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}
//发送消息
void MainWindow::on_btnSend_clicked()
{
    QString msg = ui->editMsg->text();
    ui->plainTextEdit->appendPlainText(QString("[out] ") + msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();

    QByteArray str = msg.toUtf8();
    str.append('\n');
    tcpClient->write(str);
}
//读取socket传入的数据
void MainWindow::onSocketReadyRead()
{
    while (tcpClient->canReadLine())
        ui->plainTextEdit->appendPlainText("[in] " + tcpClient->readLine());
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (tcpClient->state() == QAbstractSocket::ConnectedState)
        tcpClient->disconnectFromHost();//断开socket,关闭成功后发射disconnected()信号
    event->accept();
}
