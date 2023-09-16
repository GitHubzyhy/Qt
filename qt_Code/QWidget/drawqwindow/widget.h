#ifndef WIDGET_H
#define WIDGET_H

#include <QWindow>

class RasterWidget : public QWindow
{
    Q_OBJECT

public:
    RasterWidget(QWindow *parent = nullptr);
    ~RasterWidget();
    virtual void render(QPainter *painter);
    // QWindow interface
protected:
    void exposeEvent(QExposeEvent *);
    void resizeEvent(QResizeEvent *);//窗口或部件大小发生改变时，根据新的大小重新绘制内容，以确保绘制内容适应新的尺寸。
private:
    /*QBackingStore 是 Qt 框架中用于绘制和渲染图形的类。它提供了一个与设备无关的缓冲区，用于在内存中绘制图形，并且可以将这些图形快速地复制到屏幕上*/
    QScopedPointer<QBackingStore> m_backingStore;//是智能指针
};
#endif // WIDGET_H
