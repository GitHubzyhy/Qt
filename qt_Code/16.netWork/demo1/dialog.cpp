#include "dialog.h"
#include "./ui_dialog.h"
#include <QHostInfo>
#include <QNetworkInterface>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

//QHostInfo 获取本机主机名和IP地址
void Dialog::on_btnGetHostInfo_clicked()
{
    QString hostName = QHostInfo::localHostName(); //本地主机名
    ui->plainTextEdit->appendPlainText("本机主机名：" + hostName + "\n");

    QHostInfo hostInfo = QHostInfo::fromName(hostName); //通过主机名查Ip地址
    QList<QHostAddress> addList = hostInfo.addresses(); //ip地址列表
    if (!addList.isEmpty())
        for (int i = 0; i < addList.count(); ++i)
        {
            QHostAddress aHost = addList.at(i); //每一项是一个QHostAddress
            bool show = ui->chkOnlyIPv4->isChecked(); //只显示IPv4
            if (show)
                show = (QAbstractSocket::IPv4Protocol == aHost.protocol());
            else
                show = true;//为了执行下面的代码
            if (show)
            {
                ui->plainTextEdit->appendPlainText("协 议：" + protocolName(aHost.protocol())); //协议类型
                ui->plainTextEdit->appendPlainText("本机IP地址：" + aHost.toString()); //IP地址
                ui->plainTextEdit->appendPlainText("");
            }
        }
}
//通过协议类型返回协议名称
QString Dialog::protocolName(QAbstractSocket::NetworkLayerProtocol protocol)
{
    switch (protocol)
    {
        case QAbstractSocket::IPv4Protocol:
            return "IPv4 Protocol";
        case QAbstractSocket::IPv6Protocol:
            return "IPv6 Protocol";
        case QAbstractSocket::AnyIPProtocol:
            return "Any IP Protocol";
        default:
            return "Unknown Network Layer Protocol";
    }
}
//查找主机地址信息
void Dialog::on_btnLookup_clicked()
{
    QString hostname = ui->editHost->text(); //主机名
    ui->plainTextEdit->appendPlainText("正在查找查找主机信息：" + hostname);
    QHostInfo::lookupHost(hostname, this, &Dialog::lookedUpHostInfo);
}

//查找主机信息的槽函数
void Dialog::lookedUpHostInfo(const QHostInfo &host)
{
    QList<QHostAddress> addList = host.addresses(); //Ip地址列表
    if (!addList.isEmpty())
        for (int i = 0; i < addList.count(); ++i)
        {
            QHostAddress aHost = addList.at(i); //每一项是一个QHostAddress
            bool show = ui->chkOnlyIPv4->isChecked(); //只显示IPv4
            if (show)
                show = QAbstractSocket::IPv4Protocol == aHost.protocol();
            else
                show = true;

            if (show)
            {
                ui->plainTextEdit->appendPlainText("协 议：" + protocolName(aHost.protocol()));
                ui->plainTextEdit->appendPlainText(aHost.toString());
            }
        }
}

void Dialog::on_btnDetail_clicked()
{
    QList<QHostAddress> addList = QNetworkInterface::allAddresses(); //返回主机上所有IP地址的列表
    if (!addList.isEmpty())
        for (int i = 0; i < addList.count(); ++i)
        {
            QHostAddress aHost = addList.at(i);
            bool show = ui->chkOnlyIPv4->isChecked(); //只显示IPv4
            if (show)
                show = (QAbstractSocket::IPv4Protocol == aHost.protocol());
            else
                show = true;

            if (show)
            {
                ui->plainTextEdit->appendPlainText(QString("协  议：") + protocolName(aHost.protocol()));
                ui->plainTextEdit->appendPlainText(QString("IP地址：") + aHost.toString());
                ui->plainTextEdit->appendPlainText(QString(""));
            }
        }
}

void Dialog::on_btnALLInterface_clicked()
{
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces(); //返回主机上所有接口的网络列表
    for (int i = 0; i < list.count(); ++i)
    {
        QNetworkInterface aInterface = list.at(i);
        //判断接口信息是否有效
        if (!aInterface.isValid()) continue;

        ui->plainTextEdit->appendPlainText(QString("设备名称：") + aInterface.humanReadableName());
        ui->plainTextEdit->appendPlainText(QString("硬件地址：") + aInterface.hardwareAddress());

        QList<QNetworkAddressEntry> entryList = aInterface.addressEntries(); //返回该网络接口
        for (int j = 0; j < entryList.count(); ++j)
        {
            QNetworkAddressEntry aEntry = entryList.at(j);
            ui->plainTextEdit->appendPlainText(QString("   IP 地址：") + aEntry.ip().toString());
            ui->plainTextEdit->appendPlainText(QString("   子网掩码：") + aEntry.netmask().toString());
            ui->plainTextEdit->appendPlainText(QString("   广播地址：") + aEntry.broadcast().toString() + "\n");
        }
        ui->plainTextEdit->appendPlainText("\n");
    }
}
//清空文本
void Dialog::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}
