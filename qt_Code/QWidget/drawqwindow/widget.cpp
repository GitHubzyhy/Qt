#include "widget.h"
#include<QBackingStore>
#include<QResizeEvent>
#include<QPainter>
RasterWidget::RasterWidget(QWindow *parent)
    : QWindow(parent), m_backingStore(new QBackingStore(this))
{
}

RasterWidget::~RasterWidget()
{
}

void RasterWidget::render(QPainter *painter)
{
    painter->fillRect(0,0,width(),height(),QGradient::NightFade);//渐变来填充指定区域的背景
    painter->drawText(QRectF(0, 0, width(), height()),//文本将绘制在QRectF中
                      Qt::AlignCenter, QStringLiteral("QWindow"));

}

void RasterWidget::exposeEvent(QExposeEvent *)
{
    if(!isExposed()) return;

    QRect rect(0,0,width(),height());//在0，0绘制一个矩形
    /*开始绘制 双缓冲技术*/
    m_backingStore->beginPaint(rect);//开始在缓冲区内绘制操作，并且只对参数指定的区域进行绘制
    QPaintDevice *device=m_backingStore->paintDevice();//提供一个通用设备的绘制接口
    QPainter painter(device);

    render(&painter);

    painter.end();
    m_backingStore->endPaint();//结束在缓冲区内的绘制
    m_backingStore->flush(rect);//rect 参数指定的区域内的绘图内容刷新到实际的显示设备上，以更新屏幕上的显示
}

void RasterWidget::resizeEvent(QResizeEvent *resizeEvent)
{
    //窗口或部件大小发生改变时，m_backingStore 会随之调整大小，以适应新的窗口尺寸。
      m_backingStore->resize(resizeEvent->size());//将QBackingStore 对象的大小调整为与 resizeEvent 中指定的大小相同。
}

