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
    void on_tableWidget_itemSelectionChanged();//监视选中条目和选中矩形区域的变化

    void on_pushButtonFind_clicked();//查找
    void on_pushButtonAddLine_clicked();//增加行
    void on_pushButtonDelLines_clicked();//删除选中行
    void on_pushButtonDelSelectedItems_clicked();//删除选中条目

private:
    Ui::Widget *ui;

    //初始化表格函数
    void InitScoresTable();
    //设置某行的行首和四个单元格
    void SetTableRow(int nRow, QString strName,
                     QString strChinese, QString strMath,
                     QString strForeignLanguage, QString strFood);
};
#endif // WIDGET_H
