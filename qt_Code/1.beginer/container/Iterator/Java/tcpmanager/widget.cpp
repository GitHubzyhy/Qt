#include "widget.h"
#include "./ui_widget.h"
#include <QMessageBox>
#include <QMapIterator>//只读迭代器
#include <QMutableMapIterator>//读写迭代器
#include <QTreeWidgetItem>
#include <QRegularExpression>//正则表达式
#include <QRegularExpressionValidator>//正则表达式验证
#include <QMultiMap> //保存IP和端口映射

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置树形控件只有 1 列
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->header()->setHidden(true);//隐藏表头
    //设置 IP编辑框
    //定义 IPv4 正则表达式，注意 "\\" 就是一个反斜杠字符
    QRegularExpression re("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
                          "(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    //新建正则表达式验证器
    QRegularExpressionValidator *reVali = new QRegularExpressionValidator(re);
    ui->lineEditIP->setValidator(reVali); //设置给 lineEditIP
    ui->lineEditIP->setText( tr("192.168.1.1") ); //默认值
    //设置端口范围
    ui->spinBoxPort->setRange( 0, 65535 );
    ui->spinBoxPort->setValue( 1500 ); //默认值

    //初始化填充连接信息
    InitTCPLinks();
    //更新树形控件的显示
    UpdateTreeShow();
}

Widget::~Widget()
{
    delete ui;
}
//初始化填充
void Widget::InitTCPLinks()
{
    m_tcplinks.clear();
    m_tcplinks.insert( tr("192.168.1.1"), 80 );
    m_tcplinks.insert( tr("192.168.1.1"), 443 );
    m_tcplinks.insert( tr("192.168.1.2"), 20 );
    m_tcplinks.insert( tr("192.168.1.2"), 21 );
    m_tcplinks.insert( tr("192.168.1.3"), 80 );
    m_tcplinks.insert( tr("192.168.1.3"), 443 );
    m_tcplinks.insert( tr("192.168.1.3"), 3306 );
}
//更新树形控件的显示
void Widget::UpdateTreeShow()
{
    ui->treeWidget->clear();//清空旧的
    QMultiMapIterator<QString, int> it( m_tcplinks );

    QString strOldIP;//保存迭代中旧的IP
    QTreeWidgetItem *pOldTopItem = NULL;//保存旧的顶级IP节点
    QTreeWidgetItem *pPortItem = NULL;//端口号节点
    while (it.hasNext()) //判断是否尾元素后面的狭缝
    {
        it.next(); //向后移动一个狭缝位置
        //获取滑过元素的 IP 和端口
        QString strIp = it.key();
        int nPort = it.value();

        if (strIp != strOldIP)
        {
            //新的主机IP，建立顶级IP节点
            pOldTopItem = new QTreeWidgetItem;
            pOldTopItem->setText(0, strIp);
            ui->treeWidget->addTopLevelItem( pOldTopItem );
            //添加端口号为子节点
            pPortItem = new QTreeWidgetItem();
            pPortItem->setText( 0, tr("%1").arg(nPort) );
            pOldTopItem->addChild( pPortItem );

            strOldIP = strIp;//更新旧的IP
        }
        else
        {
            //现在元素IP 与 上一个元素IP一样
            //添加 pOldTopItem 子节点
            pPortItem = new QTreeWidgetItem;
            pPortItem->setText( 0, tr("%1").arg(nPort) );
            pOldTopItem->addChild(pPortItem);
        }
    }
    //遍历结束，树形控件条目添加完成
    ui->treeWidget->expandAll(); //全部展开
}
//添加TCP连接
void Widget::on_pushButtonAddTCP_clicked()
{
    //获取 IP 和端口
    QString strIp = ui->lineEditIP->text().trimmed(); //剔除前后空格
    if ( strIp.isEmpty() )
    {
        ui->textBrowser->setText( tr("IP为空。") );
        return; //IP为空
    }

    //端口
    int nPort = ui->spinBoxPort->value();
    //检查是否已存在相同的 IP和端口
    if (m_tcplinks.contains(strIp, nPort))
    {
        ui->textBrowser->setText( tr("该IP端口的连接已存在，IP和端口不能同时重复。") );
        return;
    }

    //不重复的连接，添加
    m_tcplinks.insert(strIp, nPort);
    ui->textBrowser->setText( tr("添加TCP连接完成。") );
    //更新树形控件
    UpdateTreeShow();
}
//删除匹配IP连接
void Widget::on_pushButtonDelIP_clicked()
{
    //获取 IP
    QString strIP = ui->lineEditIP->text().trimmed();
    if ( strIP.isEmpty() )
    {
        ui->textBrowser->setText( tr("IP为空。") );
        return; //IP为空
    }
    int nDelCount = 0; //删除计数
    QMutableMultiMapIterator<QString, int> it(m_tcplinks); //读写迭代器
    while (it.hasNext())
    {
        it.next();//向后移动一个狭缝位置
        if ( it.key() == strIP ) //检查滑过元素的 key
        {
            //删除刚找到的滑过元素
            it.remove();
            nDelCount += 1; //更新删除计数
        }
    }

    //判断
    if ( nDelCount < 1 )
        ui->textBrowser->setText( tr("没有匹配的IP。") );
    else
    {
        ui->textBrowser->setText( tr("已删除匹配IP的连接个数：%1 。").arg( nDelCount ) );
        //更新树形控件
        UpdateTreeShow();
    }
}
//删除匹配端口连接
void Widget::on_pushButtonDelPort_clicked()
{
    //获取端口号
    const int nFindPort = ui->spinBoxPort->value();
    int nDelCount = 0;
    //读写迭代器
    QMutableMultiMapIterator<QString, int> it(m_tcplinks);
    it.toFront();//从头开始
    /*  注意 Q*MapIterator 迭代器的 findNext() 和 findPrevious() 比较的是 value ;
        而 QMap/QMultiMap 容器类的 find() 比较的是 key 或者 key-value 对。*/
    while ( it.findNext( nFindPort ) ) //端口号是 value，可以用迭代器的查找函数
    {
        it.remove();
        nDelCount += 1;
    }
    //遍历结束
    if ( nDelCount < 1 )
        ui->textBrowser->setText( tr("没有匹配的端口。") );
    else
    {
        ui->textBrowser->setText( tr("已删除匹配端口的连接个数：%1 。").arg( nDelCount ) );
        //更新树形控件
        UpdateTreeShow();
    }
}
//查找1024以下小端口连接
void Widget::on_pushButtonFindBelow1024_clicked()
{
    //查找的话就用只读迭代器
    QMutableMultiMapIterator<QString, int> it(m_tcplinks);
    QString strInfo = tr("1024以下端口号的连接：\r\n");

    //迭代查找
    while (it.hasNext())
    {
        it.next();//向后移动一个狭缝位置
        if (it.value() <= 1024)
            strInfo += it.key() + tr(" 端口：%1 \r\n").arg(it.value() );
    }
    ui->textBrowser->setText( strInfo );
}
//给小端口增加1024
void Widget::on_pushButtonPlus1024_clicked()
{
    QMutableMultiMapIterator<QString, int> it(m_tcplinks);
    QString strInfo = tr("修改旧的1024以下端口号的连接：\r\n");
    //迭代查找
    while (it.hasNext())
    {
        it.next(); //滑过一个元素
        if ( it.value() <= 1024 )
        {
            strInfo += it.key() + tr(" 端口：%1 \r\n").arg(it.value() );
            //修改端口号，增加1024
            it.setValue( it.value() + 1024 );
            //等同于  it.value() += 1024;
        }
    }
    //显示
    ui->textBrowser->setText( strInfo );
    //更新树形控件
    UpdateTreeShow();
}
