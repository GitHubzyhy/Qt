#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class QListWidgetItem;//数据条目向前声明
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_pushButtonAdd_clicked();//添加
    void on_pushButtonDel_clicked();//删除
    void on_pushButtonViewMode_clicked();//切换显示模式
    void on_pushButtonLoad_clicked();//加载
    void on_pushButtonSave_clicked();//保存
    void on_pushButtonEditToolTip_clicked();//编辑工具提示

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
