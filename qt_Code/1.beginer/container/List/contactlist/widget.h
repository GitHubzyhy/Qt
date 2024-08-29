#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Contact;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButtonAdd_clicked();//添加
    void on_pushButtonDel_clicked();//删除
    void on_pushButtonFind_clicked();//查询姓名
    void on_pushButtonSort_clicked();//姓名排序
    void on_pushButtonSave_clicked();//保存
    void on_pushButtonOpen_clicked();//打开

private:
    Ui::Widget *ui;
    QList<Contact> m_listContacts;//联系人列表
};
#endif // WIDGET_H
