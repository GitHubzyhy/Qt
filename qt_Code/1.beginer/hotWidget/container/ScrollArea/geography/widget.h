#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class QSignalMapper;//信号映射器
class QLabel;
class QScrollArea;//滚动区域
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void InitControls(); //初始化控件
public slots:
    void showProvince(int index);//信号映射将所有按钮的信号都发给该槽函数

private:
    Ui::Widget *ui;

    QStringList m_listProvinces;//省份名称
    QList<QPoint> m_listPoints; //像素点位置
    QPixmap m_map;//地图
    void LoadData();//加载地图和文本数据，包含省份和像素点位置

    QSignalMapper *m_pSigMapper;//信号映射对象指针
    QLabel *m_labelMap;//标签显示图片

    QScrollArea *m_saLeftMap; //左边滚动区域显示绘图
    QScrollArea *m_saRightButtons; //右边滚动区域显示一大堆按钮
};
#endif // WIDGET_H
