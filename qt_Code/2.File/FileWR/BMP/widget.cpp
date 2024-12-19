#include "widget.h"
#include "./ui_widget.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QPixmap>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    resize(480, 360); //设置主窗口的大小

    //打印结构体大小
    qDebug() << tr("BFH: %1 B").arg( sizeof(BMPFileHeader) );//14字节
    qDebug() << tr("BIH: %1 B").arg( sizeof(BMPInfoHeader) );
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonBrowse_clicked()
{
    //获取要打开的图片文件名
    QString strName = QFileDialog::getOpenFileName(
                          this,
                          tr("打开BMP"),
                          tr("."),//当前目录
                          tr("BMP Files(*.bmp);;All Files(*)"));
    ui->lineEditName->setText(strName);
}

void Widget::on_pushButtonShowPic_clicked()
{
    //从界面获取图片文件名
    QString strName = ui->lineEditName->text();
    if ( !strName.isEmpty() )//在 labelShowPic 标签控件显示图片
        ui->labelShowPic->setPixmap( QPixmap(strName) );
}

void Widget::on_pushButtonReadHeader_clicked()
{
    //读取头部
    //获取图片文件名
    QString strName = ui->lineEditName->text();
    if ( strName.isEmpty() )//没文件名
        return;

    QFile fileIn(strName);//构造一个文件对象
    if ( ! fileIn.open(QIODevice::ReadOnly) )//只读模式打开
    {
        QMessageBox::warning(this, tr("打开文件"),
                             tr("打开文件失败：") + fileIn.errorString());
        return;
    }

    //开始读取数据
    BMPFileHeader bfh;//定义 BMP 文件头
    BMPInfoHeader bih;//定义 BMP 信息头

    //读取 BMP 文件头和信息头
    qint64 nReadBFH = fileIn.read( (char *)&bfh, sizeof(bfh) );
    qint64 nReadBIH = fileIn.read( (char *)&bih, sizeof(bih) );
    //判断读取字节数对不对
    if ( (nReadBFH < sizeof(bfh))
         || (nReadBIH < sizeof(bih)) )
    {
        QMessageBox::warning(this, tr("读取 BMP"),
                             tr("读取 BMP 头部失败，头部字节数不够！"));
        return;
    }

    QString strInfo = tr("文件名：%1\r\n\r\n").arg(strName);
    QString strTemp;
    //开始判断
    if ( bfh.bfType != 0x4D42 )//判断是否是BM
    {
        strTemp = tr("类型：不是 BMP 图片\r\n");
        strInfo += strTemp;
    }
    else
    {
        //是正常的 BMP 图片
        strTemp = tr("类型：是 BMP 图片\r\n");
        strInfo += strTemp;
        //读取 bih 里面的信息
        strTemp = tr("宽度：%1\r\n").arg( bih.biWidth );
        strInfo += strTemp;
        strTemp = tr("高度：%1\r\n").arg( bih.biHeight );
        strInfo += strTemp;
        strTemp = tr("水平分辨率：%1 DPI\r\n").arg( (int)(bih.biXPelsPerMeter / 39.3701) );
        strInfo += strTemp;
        strTemp = tr("垂直分辨率：%1 DPI\r\n").arg( (int)(bih.biYPelsPerMeter / 39.3701) );
        strInfo += strTemp;
        strTemp = tr("颜色深度：%1 位\r\n").arg( bih.biBitCount );
        strInfo += strTemp;
        strTemp = tr("帧数：%1\r\n").arg(bih.biPlanes);
        strInfo += strTemp;
    }
    //显示信息串到 textBrowser
    ui->textBrowser->setText( strInfo );

}
