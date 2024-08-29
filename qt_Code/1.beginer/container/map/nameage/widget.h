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
    void on_pushButtonDel_clicked();//删除匹配姓名元素
    void on_pushButtonFindName_clicked();//查找匹配姓名元素
    void on_pushButtonFindAge_clicked();//查找匹配年龄元素

private:
    Ui::Widget *ui;

    //映射类对象，保存姓名-年龄映射
    QMap<QString, int> m_mapNameAge;
    //枚举映射对象的内容，显示到列表控件
    void showNameAgeMap();
};
#endif // WIDGET_H
