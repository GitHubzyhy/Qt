#include "tabpreview.h"
#include "ui_tabpreview.h"
#include <QFile>

TabPreview::TabPreview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TabPreview)
{
    ui->setupUi(this);
    //初始化控件
    InitControls();

    ui->labelImagePreview->setMaximumSize(QSize(268, 209));
}

TabPreview::~TabPreview()
{
    delete ui;
}

void TabPreview::InitControls()
{
    //设置二态按钮，类似复选框的选中和未选中状态
    ui->pushButtonTextPreview->setCheckable( true );
    ui->pushButtonImagePreview->setCheckable( true );
    ui->pushButtonBytePreview->setCheckable( true );

    //设置按钮分组，分组里的按钮默认互斥，只有一个处于选中状态
    //为每个按钮分配一个整数序号，分组对象可以自动发送带序号的点击信号
    m_buttonGroup.addButton( ui->pushButtonTextPreview, 0 );
    m_buttonGroup.addButton( ui->pushButtonImagePreview, 1 );
    m_buttonGroup.addButton( ui->pushButtonBytePreview, 2 );

    //设置分组的触发信号到堆栈控件切换页面槽函数
    connect( &m_buttonGroup, SIGNAL(idClicked(int)),//QButtonGroup里的信号
             ui->stackedWidget, SLOT(setCurrentIndex(int)) );

    //开始设置样式表
    //设置所有按钮的选中状态外观
    this->setStyleSheet( "QPushButton:checked { background-color: yellow }" );

    //设置字节浏览框的背景色
    ui->textBrowserByte->setStyleSheet( "background-color: #AAEEFF" );

    //图片预览标签背景色
    ui->labelImagePreview->setStyleSheet( "background-color: #E0E0E0" );
}

void TabPreview::onFileNameChanged(const QString &fileName)
{
    //主页面更新文件名，并处理预览界面的更新。
    m_strFileName = fileName;
    //这里主要按图片和非图片区分处理
    //尝试按图片加载
    bool isImage = m_image.load(m_strFileName);
    m_image = m_image.scaled(ui->labelImagePreview->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    if (isImage)
    {
        //如果是图片
        ui->labelImagePreview->setText("");
        ui->labelImagePreview->setPixmap( m_image );
    }
    else
    {
        m_image = QPixmap(); //空图
        ui->labelImagePreview->setPixmap(m_image);
        ui->labelImagePreview->setText(tr("不是支持的图片，无法以图片预览。"));
    }

    //文本预览和字节预览统一使用前 200 字节内容来显示
    QFile fileIn(m_strFileName);
    if (!fileIn.open(QIODevice::ReadOnly))
        qDebug() << tr("文件无法打开：") << m_strFileName; //无法读取，无法预览
    else
    {
        QByteArray baData = fileIn.read(200); //读取200个字节
        QString strText = QString::fromLocal8Bit( baData );//转为文本
        //普通文本预览
        ui->textBrowserText->setText( strText );

        //转为HEX字节文本显示，大写的十六进制字母
        QString strHex = baData.toHex().toUpper();
        ui->textBrowserByte->setText( strHex );//十六进制字节浏览
    }

    //根据文件形式，设置默认的预览界面
    if ( isImage ) //判断图片
        //通过函数点击按钮一次，与鼠标点击一样，触发 clicked() 信号
        ui->pushButtonImagePreview->click();
    else //非图片
    {
        //判断是哪种文本
        if ( m_strFileName.endsWith( ".txt", Qt::CaseInsensitive )
             || m_strFileName.endsWith( ".h", Qt::CaseInsensitive )
             || m_strFileName.endsWith( ".cpp", Qt::CaseInsensitive )
             || m_strFileName.endsWith( ".c", Qt::CaseInsensitive ) )
            ui->pushButtonTextPreview->click();

        else //其他
            ui->pushButtonBytePreview->click();
    }
}
