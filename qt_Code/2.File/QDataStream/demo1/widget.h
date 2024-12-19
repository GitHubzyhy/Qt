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
    void on_pushButtonAdd_clicked();//添加行

    void on_pushButtonDel_clicked();//删除行

    void on_pushButtonSaveDS_clicked();//保存文件

    void on_pushButtonLoadDS_clicked();//加载DS

    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
