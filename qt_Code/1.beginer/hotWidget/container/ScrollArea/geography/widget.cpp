#include "widget.h"
#include "./ui_widget.h"
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>//信号高级映射
#include <QFile>
#include <QMessageBox>
#include <QLabel>
#include <QRadioButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    LoadData();//加载地图和文本数据，包含省份和像素点位置
    InitControls();//初始化控件
}

Widget::~Widget()
{
    delete ui;
}
//初始化控件
void Widget::InitControls()
{
    //使用QLabel绘图
    m_labelMap = new QLabel;
    m_labelMap->setPixmap(m_map);

    //构建左边滚动区域包裹标签
    m_saLeftMap = new QScrollArea;
    m_saLeftMap->setWidget(m_labelMap);

    //右边容器和布局器
    QWidget *pWidRight = new QWidget;
    QVBoxLayout *pLayoutRight = new QVBoxLayout;

    //用于循环新建单选按钮
    QRadioButton *curButton = nullptr;
    m_pSigMapper = new QSignalMapper(this);

    int nCount = m_listProvinces.count();
    for (int i = 0; i < nCount; ++i)
    {
        curButton = new QRadioButton(m_listProvinces[i]);
        //关联信号到信号映射对象
        connect(curButton, &QRadioButton::clicked,
                m_pSigMapper, qOverload<>(&QSignalMapper::map));//返回重载函数的指针

        //设置映射参数，将当前按钮的编号设置为 i
        m_pSigMapper->setMapping(curButton, i);
        pLayoutRight->addWidget(curButton);
        curButton->setStyleSheet("QRadioButton {color: black;}");//版本原因
    }
    //将信号映射对象的 mapped() 信号关联到统一的槽函数
    connect(m_pSigMapper, &QSignalMapper::mappedInt,
            this, &Widget::showProvince);

    pWidRight->setLayout(pLayoutRight);//布局器设置给右边容器
    //新建右边滚动区域，将容器设置给右边滚动区域
    m_saRightButtons = new QScrollArea;
    m_saRightButtons->setWidget(pWidRight);

    //主界面布局器
    QHBoxLayout *pMainLayout = new QHBoxLayout;
    pMainLayout->addWidget( m_saLeftMap );
    pMainLayout->addWidget( m_saRightButtons );
    pMainLayout->setStretch(0, 4); //左边拉伸因子 4
    pMainLayout->setStretch(1, 1); //右边拉伸因子 1

    setLayout(pMainLayout);

    resize(800, 600);//窗口大小
    curButton->setChecked( true );//最后一个单选按钮选中

    m_saRightButtons->ensureWidgetVisible( curButton ); //显示最后一个单选按钮
    //移动视口位置
    m_saRightButtons->ensureVisible(
        m_listPoints[nCount - 1].x(),
        m_listPoints[nCount - 1].y(),
        200, 200); //显示最后一个单选按钮
}
//将大量有规律的信号映射到一个槽函数，批量处理。
void Widget::showProvince(int index)
{
    //移动的是视口位置
    m_saLeftMap->ensureVisible( m_listPoints[index].x(), m_listPoints[index].y(), 200, 200 );
}
//加载地图和文本数据，包含省份和像素点位置
void Widget::LoadData()
{
    //省份和像素点清空
    m_listProvinces.clear();
    m_listPoints.clear();

    m_map.load(":/geography/china.png");//加载地图
    QFile fileIn(":/geography/china.txt");//准备读取文本文件
    if (!fileIn.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "文件打开失败", fileIn.errorString());
        return;
    }

    //开始读取文件，用QIODevice类的读写函数
    while (!fileIn.atEnd())
    {
        QByteArray baLine = fileIn.readLine();
        QString strLine = QString::fromUtf8(baLine); //返回utf8的QString
        QStringList liParts = strLine.split('\t');

        m_listProvinces << liParts[0];
        QPoint pt;
        pt.setX(liParts[1].toInt());
        pt.setY(liParts[2].toInt());
        m_listPoints << pt;
    }
    //加载完毕
    qDebug() << m_listProvinces.size() << m_listProvinces;
    qDebug() << m_listPoints.size() << m_listPoints;
}
