#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QHostInfo>

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
    ui->comboTargetIP->addItem(localIP);

    udpSocket = new QUdpSocket(this); //用于与连接的客户端通讯的QTcpSocket
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
//读取socket传入的数据
void MainWindow::onSocketReadyRead()
{
    while (udpSocket->hasPendingDatagrams()) //判断是否有数据包可以读取
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());//设置字节数组的大小

        QHostAddress peerAddr;//ip
        quint16 peerPort;//端口
        udpSocket->readDatagram(datagram.data(), datagram.size(), &peerAddr, &peerPort);

        QString str = datagram.data();
        QString peer = "[From " + peerAddr.toString() + ":" + QString::number(peerPort) + "] ";
        ui->plainTextEdit->appendPlainText(peer + str);
    }
}
//绑定端口
void MainWindow::on_actStart_triggered()
{
    quint16 port = ui->spinBindPort->value(); //本机UDP端口
    if (udpSocket->bind(port)) //绑定端口成功
    {
        ui->plainTextEdit->appendPlainText(QString("**已成功绑定"));
        ui->plainTextEdit->appendPlainText(QString("**绑定端口：")
                                           + QString::number(udpSocket->localPort()));

        ui->actStart->setEnabled(false);
        ui->actStop->setEnabled(true);
    }
    else
        ui->plainTextEdit->appendPlainText(QString("**绑定失败"));
}
//解除绑定
void MainWindow::on_actStop_triggered()
{
    udpSocket->abort();
    ui->actStart->setEnabled(true);
    ui->actStop->setEnabled(false);
    ui->plainTextEdit->appendPlainText(QString("**已解除绑定"));
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

    QList<QHostAddress> addList = hostInfo.addresses(); //ip地址列表
    if (!addList.isEmpty())
        for (int i = 0; i < addList.count(); i++)
        {
            QHostAddress aHost = addList.at(i);
            if (QAbstractSocket::IPv4Protocol == aHost.protocol())
            {
                QString IP = aHost.toString();
                ui->plainTextEdit->appendPlainText(QString("本机IP地址：") + aHost.toString());
                if (ui->comboTargetIP->findText(IP) < 0)//没找到
                    ui->comboTargetIP->addItem(IP);
            }
        }
}
//发送消息
void MainWindow::on_btnSend_clicked()
{
    QString targetIp = ui->comboTargetIP->currentText();
    QHostAddress targetAddr(targetIp);//目标IP
    quint16 targetPort = ui->spinTargetPort->value(); //目标port
    QString msg = ui->editMsg->text(); //发送的消息内容

    QByteArray str = ui->editMsg->text().toUtf8();
    udpSocket->writeDatagram(str, targetAddr, targetPort);//发出数据报

    ui->plainTextEdit->appendPlainText(QString("[out] ") + msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();
}
//广播消息
void MainWindow::on_btnBroadcast_clicked()
{
    quint16 targetPort = ui->spinTargetPort->value(); //目标端口
    QString msg = ui->editMsg->text();
    QByteArray str = msg.toUtf8();
    udpSocket->writeDatagram(str, QHostAddress::Broadcast, targetPort);

    ui->plainTextEdit->appendPlainText(QString("[broadcast] ") + msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();
}
