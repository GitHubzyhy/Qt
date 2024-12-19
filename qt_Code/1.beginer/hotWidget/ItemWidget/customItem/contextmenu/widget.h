#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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

    //添加槽函数
public slots:
    //弹出右键菜单的槽函数
    void onCustomContextMenuRequested(const QPoint &pos);

    void onAddItemTriggered();//添加条目菜单项的槽函数
    void onEditItemTriggered();//编辑条目菜单项的槽函数
    void onDelItemTriggered();//删除条目菜单项的槽函数
    void onClearAllTriggered();//清空所有条目的菜单项槽函数

private:
    Ui::Widget *ui;

    QMenu *m_menuContext;//保存右键菜单的指针
    void CreateMenu(); //创建菜单并关联信号和槽函数
};
#endif // WIDGET_H
