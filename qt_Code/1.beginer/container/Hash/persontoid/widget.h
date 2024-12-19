#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Person;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //显示更新后的数据
    void UpdateDataShow();

private slots:
    void on_pushButtonSaveData_clicked();//保存数据
    void on_pushButtonLoadData_clicked();//加载数据
    void on_pushButtonAdd_clicked();//添加元素
    void on_pushButtonDel_clicked();//删除选中元素
    void on_pushButtonPersonToID_clicked();//Person查ID
    void on_pushButtonIDToPerson_clicked();//ID查Person

private:
    Ui::Widget *ui;

    //定义容器
    QHash<Person, quint64> m_data;
};
#endif // WIDGET_H
