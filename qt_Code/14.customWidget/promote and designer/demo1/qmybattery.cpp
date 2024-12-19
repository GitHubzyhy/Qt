#include "qmybattery.h"
#include <QPainter>

QmyBattery::QmyBattery(QWidget *parent)
    : QWidget{parent}
{}
//设置当前电量
void QmyBattery::setPowerLevel(int pow)
{
    mPowerLevel = pow;
    emit powerLevelChanged(pow);
    repaint();//立即重新绘制
}
//得到当前电量
int QmyBattery::powerLevel()
{
    return mPowerLevel;
}
//设置电量低阀值
void QmyBattery::setWarnLevel(int warn)
{
    mWarnLevel = warn;
    repaint();
}
//得到电量低阀值
int QmyBattery::warnLevel()
{
    return mWarnLevel;
}
//返回组件的缺省大小
QSize QmyBattery::sizeHint()
{
    int H = this->height();
    int W = H * 12 / 5;
    QSize size(W, H);
    return size;
}

void QmyBattery::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);//在此设备上绘图

    //设置QPainter的绘图区
    QRect rect(0, 0, width(), height());
    painter.setViewport(rect);//视口
    painter.setWindow(0, 0, 120, 50); //窗口 动态适应变化
    painter.setRenderHint(QPainter::Antialiasing);//图片边缘反锯齿
    painter.setRenderHint(QPainter::TextAntialiasing);//文本反锯齿

    //设置画笔
    QPen pen;
    pen.setWidth(2);
    pen.setColor(mColorBorder);
    pen.setStyle(Qt::SolidLine);//线条样式
    pen.setCapStyle(Qt::FlatCap);//端点样式
    pen.setJoinStyle(Qt::BevelJoin);//连接样式

    //设置画刷
    QBrush brush;
    brush.setColor(mColorBack);
    brush.setStyle(Qt::SolidPattern);//单一颜色填充

    //①绘制电池边框
    painter.setPen(pen);
    painter.setBrush(brush);
    rect.setRect(1, 1, 109, 48);//改变rect的区域(左上角，宽高)
    painter.drawRect(rect);

    //②改变画刷颜色，改变rect的区域，绘制电池的正极头
    brush.setColor(mColorBorder);
    painter.setBrush(brush);
    rect.setRect(110, 15, 10, 20);
    painter.drawRect(rect);

    //③画电池柱
    if (mPowerLevel > mWarnLevel) //正常颜色电量柱
    {
        brush.setColor(mColorPower);
        pen.setColor(mColorPower);
    }
    else//电量低时电量柱
    {
        brush.setColor(mColorWarning);
        pen.setColor(mColorWarning);
    }
    painter.setBrush(brush);
    painter.setPen(pen);
    //如果当前有电量，绘制电量柱
    if (mPowerLevel > 0)
    {
        rect.setRect(5, 5, mPowerLevel, 40);
        painter.drawRect(rect);
    }

    QFontMetrics textSize(this->font());
    QString powerStr = QString::asprintf("%d%%", mPowerLevel);
    QRect textRect = textSize.boundingRect(powerStr); //得到字符串的rect
    painter.setFont(this->font());
    pen.setColor(mColorBorder);
    painter.setPen(pen);
    painter.drawText(55 - textRect.width() / 2, 23 + textRect.height() / 2, powerStr);
}
