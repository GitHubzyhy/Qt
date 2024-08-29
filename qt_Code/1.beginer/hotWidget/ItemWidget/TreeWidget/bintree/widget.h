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
    void on_pushButtonPreorder_clicked();//先序遍历
    void on_pushButtonPostorder_clicked();//后序遍历
    void on_pushButtonMidorder_clicked();//中序遍历
    void on_pushButtonIterator_clicked();//迭代器遍历
    void on_pushButtonLevels_clicked();//按层遍历

private:
    Ui::Widget *ui;

    //先序遍历递归函数，只打印字符，不需要返回值
    void PreorderTraversal(QTreeWidgetItem *curItem);
    //后序遍历递归函数
    void PostorderTraversal(QTreeWidgetItem *curItem);
    //中序遍历递归函数
    void MidorderTraversal(QTreeWidgetItem *curItem);
    //迭代器遍历
    void IteratorTraversal(QTreeWidgetItem *curItem);
    //按层遍历
    void LevelsTraversal(QTreeWidgetItem *curItem);
};
#endif // WIDGET_H
