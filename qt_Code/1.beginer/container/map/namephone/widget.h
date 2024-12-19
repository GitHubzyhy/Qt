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

private slots:
    void on_pushButtonAdd_clicked();//添加元素
    void on_pushButtonReplace_clicked();//替换元素
    void on_pushButtonDelName_clicked();//删除匹配元素
    void on_pushButtonDelNamePhone_clicked();//删除匹配姓名电话
    void on_pushButtonFindName_clicked();//查询姓名
    void on_pushButtonFindPhone_clicked();//查询电话

private:
    Ui::Widget *ui;

    //多重映射对象，保存姓名电话映射
    QMultiMap<QString, QString> m_mmapNamePhone;
    //枚举映射对象内容，显示到列表控件
    void showNamePhoneMap();
};
#endif // WIDGET_H
