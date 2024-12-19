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
    void on_pushButtonLoad_clicked();//加载表格

    void on_pushButtonSave_clicked();//保存表格

    void on_pushButtonDelRow_clicked();//删除行

    void on_pushButtonAddRow_clicked();//添加行

    void on_listWidget_currentRowChanged(int currentRow);//列表控件选中的行变化时

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
