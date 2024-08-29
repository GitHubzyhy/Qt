#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class QTableWidgetItem;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    //当前选中条目变化信号，新、旧当前选中单元格至少有一个非空才会触发这个信号
    void on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    void on_pushButtonAdd_clicked();//添加
    void on_pushButtonDel_clicked();//删除

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
