#include "widget.h"
#include "./ui_widget.h"
#include <QFileDialog>  //打开文件对话框
#include <QScrollArea>  //为标签添加滚动区域
#include <QMessageBox>  //消息框
#include <QPixmap>  //像素图
#include <QMovie>   //动态图
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //初始化成员变量
    m_pPixMap = NULL;
    m_pMovie = NULL;
    m_bIsMovie = false;
    m_bIsPlaying = false;

    QVBoxLayout *layout = ui->verticalLayout;
    layout->removeWidget(layout->itemAt(0)->widget());//移除控件

    QScrollArea *pSA = new QScrollArea(this);
    pSA->setWidget(ui->labelShow);//把标签填充到滚动区域里
    layout->insertWidget(0, pSA);//index处插入控件

    //打印支持的图片格式
    qDebug() << QImageReader::supportedImageFormats();
    //打印支持的动态图格式
    qDebug() << QMovie::supportedFormats();
}

Widget::~Widget()
{
    clearOldShow();//手动清理
    delete ui;
}
//接收播放错误信号
void Widget::RecvPlayError(QImageReader::ImageReaderError error)
{
    //打印
    qDebug() << tr("读取动态图错误的代码：%1").arg(error);
    //提示播放出错
    QMessageBox::critical(this, tr("播放出错"),
                          tr("播放动态图出错，文件名为：\r\n%1").arg(m_pMovie->fileName()));
    //回到停止状态
    m_bIsPlaying = false;
}
//接收帧号变化信号
void Widget::RecvFrameNumber(int frameNumber)
{
    ui->horizontalSlider->setValue(frameNumber);
}
//打开图片
void Widget::on_btnOpenPic_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                           this,
                           tr("打开静态图片"),
                           "/home",
                           "Pictures (*.bmp *.jpg *.jpeg *.png *.xpm);;All files(*)");
    if (fileName.isEmpty()) return;
    clearOldShow();//清空旧的图片或短片
    qDebug() << "文件的绝对路径为" << fileName;

    m_pPixMap = new QPixmap;
    if (m_pPixMap->load(fileName))//加载图片
    {
        //加载成功,设置给标签
        ui->labelShow->setPixmap(*m_pPixMap);
        //设置标签的新大小，与像素图一样大
        ui->labelShow->setGeometry(m_pPixMap->rect());

        //设置 bool 状态
        m_bIsMovie = false; //不是动态图
        m_bIsPlaying = false; //不是动态图播放
    }
    else
    {
        //加载失败，删除图片对象，返回
        delete m_pPixMap;
        m_pPixMap = NULL;
        //提示失败
        QMessageBox::critical(this, tr("打开失败"),
                              tr("打开图片失败，文件名为：\r\n%1").arg(fileName));
    }

}
//打开gif图
void Widget::on_btnOpenMov_clicked()
{
    QString strFileName; //文件名
    strFileName = QFileDialog::getOpenFileName(
                      this,
                      tr("打开动态图片"),
                      "/home",
                      "Movies (*.gif *.mng);;All files(*)");
    if (strFileName.isEmpty())
        return;//文件名为空，返回
    clearOldShow();//清除旧的图片或短片
    qDebug() << "文件的绝对路径为" << strFileName;

    //新建动态图
    m_pMovie = new QMovie(strFileName);
    //缩放设置
    m_pMovie->setScaledSize(ui->verticalLayout->itemAt(0)->widget()->size());
    if ( ! m_pMovie->isValid() )//判断是否动态图文件可用
    {
        //不可用
        QMessageBox::critical(this, tr("动态图不可用"),
                              tr("动态图格式不支持或读取出错，文件名为：\r\n%1").arg(strFileName));
        //清除
        delete m_pMovie;
        m_pMovie = nullptr;
        return; //不可用就直接返回
    }

    //动态图的总帧数
    int nCount = m_pMovie->frameCount(); //动态图的帧数量
    if (nCount)//如果有统计帧数，那就设置滑动条上限
        ui->horizontalSlider->setMaximum(nCount);
    else
        ui->horizontalSlider->setMaximum(100);//默认为100

    //把动态图设置给标签
    ui->labelShow->setMovie(m_pMovie);
    //修改 bool 状态
    m_bIsMovie = true;
    m_bIsPlaying = false; //还没点击播放开始的按钮

    //关联播放时的信号,播放出错信号
    connect(m_pMovie, &QMovie::error, this, &Widget::RecvPlayError);
    //播放的帧号变化信号
    connect(m_pMovie, &QMovie::frameChanged, this, &Widget::RecvFrameNumber);
    //将动态图片跳转到起始帧
    if (m_pMovie->jumpToFrame(0))
    {
        //跳转成功,对于打头的帧，设置标签的矩形为帧的矩形
        ui->labelShow->setGeometry(m_pMovie->frameRect());
    }
    //如果跳转失败，槽函数 RecvPlayError() 会提示出错
}
//播放
void Widget::on_btnStart_clicked()
{
    if (!m_bIsMovie) return; //不是动态图
    if (m_bIsPlaying) return; //正在播放
    //播放动态图
    m_bIsPlaying = true; //开始播放状态
    m_pMovie->start();
    //打印动态图默认的播放循环轮数，0 代表不循环，-1 代表无限循环
    qDebug() << tr("循环计数：%1").arg( m_pMovie->loopCount() );
}
//停止播放
void Widget::on_btnStop_clicked()
{
    if ( ! m_bIsMovie) //不是动态图
        return;
    if ( ! m_bIsPlaying) //没有处于播放状态
        return;
    //停止播放
    m_bIsPlaying = false;
    m_pMovie->stop();
}
//清理
void Widget::clearOldShow()
{
    ui->labelShow->clear();//清空标签内容
    if (!m_pPixMap) //像素图不空就删除
    {
        delete m_pPixMap;
        m_pPixMap = nullptr;
    }

    if (!m_pMovie) //如果短片不为空，就删除
    {
        if (m_bIsPlaying) //如果正在播放则停止
            m_pMovie->stop();//停止播放

        delete m_pMovie;
        m_pMovie = nullptr;
    }
    //标志位重置
    m_bIsMovie = false;
    m_bIsPlaying = false;
}
