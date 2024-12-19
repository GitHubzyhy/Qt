#ifndef QMYBATTERY_H
#define QMYBATTERY_H

#include <QWidget>

class QmyBattery : public QWidget
{
    Q_OBJECT
private:
    QColor mColorBack = Qt::white; //背景色
    QColor mColorBorder = Qt::black; //电池边框颜色
    QColor mColorPower = Qt::green; //电量柱颜色
    QColor mColorWarning = Qt::red; //电量短缺时的颜色
    int mPowerLevel = 60; //当前电量（0-100）
    int mWarnLevel = 20; //电量低警示阀值

public:
    explicit QmyBattery(QWidget *parent = nullptr);

    void setPowerLevel(int pow); //设置当前电量
    int powerLevel(); //得到当前电量
    void setWarnLevel(int warn); //设置电量低阀值
    int warnLevel(); //得到电量低阀值
    QSize sizeHint(); //返回组件的缺省大小

signals:
    //当电量值改变时发射此信号
    void powerLevelChanged(int);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // QMYBATTERY_H
