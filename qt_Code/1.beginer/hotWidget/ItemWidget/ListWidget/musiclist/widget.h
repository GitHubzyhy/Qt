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
    void on_pushButtonAdd_clicked();//添加
    void on_pushButtonDel_clicked();//删除
    void on_pushButtonExportM3U_clicked();//导出m3u

    void on_checkBoxAutoSort_clicked(bool checked);//自动排序
    void on_checkBoxReverse_clicked(bool checked);//逆序排序

    void on_pushButtonFind_clicked();//查找

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
