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
    //双色交替行
    void on_pushButtonAlternatingRowColors_clicked();
    //选中条目定制
    void on_pushButtonSelectionCustom_clicked();
    //所有条目定制
    void on_pushButtonItemCustom_clicked();
    //角按钮定制
    void on_pushButtonCornerButtonCustom_clicked();
    //表头定制
    void on_pushButtonHeaderCustom_clicked();
    //清空样式表
    void on_pushButtonClearStyle_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
