#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class QTreeWidgetItem;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButtonAddTop_clicked();//添加顶级节点
    void on_pushButtonAddChild_clicked();//添加子节点
    void on_pushButtonDelLeaf_clicked();//删除叶子节点
    void on_pushButtonDelSubtree_clicked();//删除节点子树

private:
    Ui::Widget *ui;
    //递归删除节点子树
    void RemoveSubtree(QTreeWidgetItem *curLevelItem);
};
#endif // WIDGET_H
