#ifndef QWBATERY_H
#define QWBATERY_H

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>
#include <QColor>

class QDESIGNER_WIDGET_EXPORT QwBatery : public QWidget
{
    Q_OBJECT
    //自定义属性
    Q_PROPERTY(int powerLevel READ powerLevel WRITE
               setPowerLevel NOTIFY powerLevelChanged DESIGNABLE true)

private:
    QColor mColorBack = Qt::white; //背景颜色
    QColor mColorBorder = Qt::black; //电池边框颜色
    QColor mColorPower = Qt::green; //电量柱颜色
    QColor mColorWarning = Qt::red; //电量短缺时的颜色

    int mPowerLevel = 60; //电量0-100
    int mWarnLevel = 20; //电量低警示阈值

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

public:
    explicit QwBatery(QWidget *parent = nullptr);

    void setPowerLevel(int pow);//设置当前电量
    int powerLevel();

    void setWarnLevel(int warn);//设置电量低阈值
    int warnLevel();

    QSize sizeHint();//报告缺省大小

signals:
    void powerLevelChanged(int );
};

#endif // QWBATERY_H
