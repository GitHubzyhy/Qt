#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImageReader>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    //接收出错的信号
    void RecvPlayError(QImageReader::ImageReaderError error);
    //接收播放时帧号变化
    void RecvFrameNumber(int frameNumber);

private slots:
    void on_btnOpenPic_clicked();//打开图片
    void on_btnOpenMov_clicked();//打开gif
    void on_btnStart_clicked();//开始播放
    void on_btnStop_clicked();//停止播放

private:
    Ui::Widget *ui;

    QPixmap *m_pPixMap;//像素图指针
    QMovie *m_pMovie;//动态图指针
    bool m_bIsMovie;//是否为动态图
    bool m_bIsPlaying;//动态图是否在播放中，如果在播放中，那么循环播放

    //清除函数，在打开新图之前，清空旧的
    void clearOldShow();
};
#endif // WIDGET_H
