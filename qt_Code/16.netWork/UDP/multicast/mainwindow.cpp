#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui_mainwindow.h"
#include <QUdpSocket>

//获取本机ipv4
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
    LabSocketState = new QLabel(QString("Socket状态：")); //
    LabSocketState->setMinimumWidth(200);
    ui->statusbar->addWidget(LabSocketState);

    QString localIP = getLocalIP(); //本机IP
    this->setWindowTitle(this->windowTitle() + QString("----本机IP：") + localIP);

    udpSocket = new QUdpSocket(this); //用于与连接的客户端通讯的QTcpSocket
    /*  Multicast路由层次，1表示只在同一局域网内
        组播TTL: 生存时间，每跨1个路由会减1，多播无法跨过大多数路由所以为1
        默认值是1，表示数据包只能在本地的子网中传送。*/
    udpSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 1);

    connect(udpSocket, &QUdpSocket::stateChanged,
            this, &MainWindow::onSocketStateChange);
    onSocketStateChange(udpSocket->state());

    connect(udpSocket, &QUdpSocket::readyRead,
            this, &MainWindow::onSocketReadyRead);
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
//读取socket传入的数据
void MainWindow::onSocketReadyRead()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress peerAddr;
        quint16 peerPort;
        udpSocket->readDatagram(datagram.data(), datagram.size(), &peerAddr, &peerPort);

        QString str = datagram.data();

        QString peer = "[From " + peerAddr.toString() + ":" + QString::number(peerPort) + "] ";

        ui->plainTextEdit->appendPlainText(peer + str);
    }
}
//加入组播
void MainWindow::on_actStart_triggered()
{
    QString IP = ui->comboIP->currentText();
    groupAddress = QHostAddress(IP);
    quint16 groupPort = ui->spinPort->value();

    //绑定组播的端口（参数1指定地址为AnyIPv4表示端口为多播组统一的一个端口）
    if (udpSocket->bind(QHostAddress::AnyIPv4, groupPort, QUdpSocket::ShareAddress))
    {
        udpSocket->joinMulticastGroup(groupAddress);//加入组播组
        ui->plainTextEdit->appendPlainText("**加入组播成功");
        ui->plainTextEdit->appendPlainText("**组播地址IP：" + IP);
        ui->plainTextEdit->appendPlainText("**绑定端口：" + QString::number(groupPort));

        ui->actStart->setEnabled(false);
        ui->actStop->setEnabled(true);
        ui->comboIP->setEnabled(false);
    }
    else
        ui->plainTextEdit->appendPlainText("**绑定端口失败");
}
//退出组播
void MainWindow::on_actStop_triggered()
{
    udpSocket->leaveMulticastGroup(groupAddress);//退出组播
    udpSocket->abort();//解除绑定

    ui->actStart->setEnabled(true);
    ui->actStop->setEnabled(false);
    ui->comboIP->setEnabled(true);
    ui->plainTextEdit->appendPlainText("**已退出组播,解除端口绑定");
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
    ui->plainTextEdit->appendPlainText("本机主机名：" + hostName + "\n");
    QHostInfo hostInfo = QHostInfo::fromName(hostName);

    QList<QHostAddress> addList = hostInfo.addresses(); //
    if (!addList.isEmpty())
        for (int i = 0; i < addList.count(); i++)
        {
            QHostAddress aHost = addList.at(i);
            if (QAbstractSocket::IPv4Protocol == aHost.protocol())
            {
                QString IP = aHost.toString();
                ui->plainTextEdit->appendPlainText("本机IP地址：" + aHost.toString());
                if (ui->comboIP->findText(IP) < 0)
                    ui->comboIP->addItem(IP);
            }
        }
}
//发送组播消息
void MainWindow::on_btnMulticast_clicked()
{
    quint16 groupPort = ui->spinPort->value();
    QString msg = ui->editMsg->text();
    QByteArray datagram = msg.toUtf8();

    udpSocket->writeDatagram(datagram, groupAddress, groupPort);
    ui->plainTextEdit->appendPlainText("[multicst] " + msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();
}
