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

    //初始化填充
    void InitSalary();
    //工资列表变动时，显示到列表控件
    void UpdateSalaryShow();

private slots:
    void on_pushButtonIncrease_clicked();//所有人涨10%
    void on_pushButtonFindZhang3_clicked();//查找张三工资
    void on_pushButtonFindTop3_clicked();//查找工资最高3人
    void on_pushButtonFind8K_clicked();//查找8k以上
    void on_pushButtonDel8K_clicked();//删除8k以上员工

private:
    Ui::Widget *ui;

    //使用哈希映射保存工资表
    QMultiHash<QString, double> m_salary;
};
#endif // WIDGET_H
